#include "../include/Matrix.hpp"
#include "../include/HeatDiffusion.hpp"

#include <numeric> // for std::inner_product

namespace moduleH {

HeatDiffusion::HeatDiffusion(int dimension, double initialTemperature, const double boundaryCondition1, const double boundaryCondition2)
    : dimension(dimension), initialTemperature(initialTemperature),
    boundaryCondition1(boundaryCondition1), boundaryCondition2(boundaryCondition2) {};

// Define the function to evaluate in point y
mup::Value HeatDiffusion::evaluate(double y, mup::ParserX& parser) {
    // Remove any existing variable x to ensure a clean slate
    parser.RemoveVar("x");
    // Create variable x with value a
	mup::Value x(y);
    parser.DefineVar("x", mup::Variable(&x));
    // Evaluate the expression
    return parser.Eval();
};

// Solve the heat diffusion problem using the Thomas Algorithm
std::vector<double> HeatDiffusion::solveH(const std::string &function) {
    // Fill the vector domain (i.e. x) with the equally spaced temperatures
    std::vector<double> domain(dimension); // prima c'era dimension+1
    // Calculate number of spatial steps
    double h = initialTemperature / (dimension + 1);
    for (unsigned int i = 0; i < dimension; ++i) {// prima c'era dimension+1
        domain[i] = i * h;
    }

    // subdiagonal
    a.resize(dimension - 1, 1); // before I put dimension instead of dimension-1
    a[dimension - 1] = 0;
    // diagonal
    b.resize(dimension, -2);
    b[0] = 1;
    b[dimension - 1] = 1;
    // superdiagonal
    c.resize(dimension - 1, 1); // before I put dimension instead of dimension-1
    c[0] = 0;
    //c[dimension - 1] = 0;

    // Compute the forcing term i.e. f
    forcingTerm.resize(dimension, h * h);
    forcingTerm[0] = boundaryCondition1;
    forcingTerm[dimension - 1] = boundaryCondition2;

    // Create the parser instance for the function
    mup::ParserX parser;
    // Set the expression of the function
    parser.SetExpr(function);

    for (unsigned int i = 1; i < dimension - 1; ++i) {
        // Evaluate the function in each point of the domain
        double ev = evaluate(domain[i], parser);
        forcingTerm[i] *= ev;
    }

    // Define temperature vector which is the solution u
    std::vector<double> temperature(dimension);

    // Define the heat matrix which is a tridiagonal matrix
    TridiagonalMatrix heatmatrix(a, b, c);
    temperature = heatmatrix.solve(forcingTerm);
    return temperature;
};

// Validate the solution against the exact solution computi the error ||solution - exactSolution||
// in Euclidean norm to assess the correctness of the implementation
double HeatDiffusion::validate_solution(const std::vector<double> solution, const std::string &exactf) {
    // Create the parser instance for the exact solution exactf
    mup::ParserX parser;
    // Set the expression of the exact solution exactf
    parser.SetExpr(exactf);

    // Calculate number of spatial steps for the domain (i.e. x)
    double h = initialTemperature / (dimension + 1);
    std::vector<double> exactSol(dimension);
    for (unsigned int i = 0; i < dimension; ++i) {
        // Evaluate the exact solution in each point of the domain (which is i*h equally spaced)
        exactSol[i] = evaluate(i * h, parser);
    }

    // Compute the difference between the two vectors
    std::vector<double> difference(dimension);
    std::transform(solution.begin(), solution.end(), exactSol.begin(), difference.begin(),
                   [](double x, double y) { return x - y; });
    // Compute the Euclidean norm doing the square root of std::inner_product(first1, last1, first2, init)
    // where first1 and first2 coincide because Euclidean norm = sqrt( (x_1)^2 + ... + (x_n)^2 )
    // so you have to multiply the vector difference for itself. 0.0 is the initial value of this sum
    return std::sqrt(std::inner_product(difference.begin(), difference.end(), difference.begin(), 0.0));
};
} // end of namespace