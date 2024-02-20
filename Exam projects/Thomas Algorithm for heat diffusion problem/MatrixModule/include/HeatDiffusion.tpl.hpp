#include "HeatDiffusion.hpp"
#include "ThomasSolver.hpp"
#include "Matrix.hpp"

namespace moduleH {

// Solve the heat diffusion problem using the Thomas Algorithm
template<typename MatrixType>
std::vector<double> HeatDiffusion::solveHeatProblem(const std::string &function) {
    // Fill the vector domain (i.e. x) with the equally spaced temperatures
    std::vector<double> domain(dimension);
    // Calculate number of spatial steps
    double h = L / (dimension + 1);
    for (unsigned int i = 0; i < dimension; ++i) {
        domain[i] = i * h;
    }

    // subdiagonal
    a.resize(dimension, 1);
    a[dimension - 1] = 0;
    // diagonal
    b.resize(dimension, -2);
    b[0] = 1;
    b[dimension - 1] = 1;
    // superdiagonal
    c.resize(dimension, 1);
    c[0] = 0;

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

    // Create a MatrixType with such a, b, c
    const MatrixType matrix(a, b, c);
    // Create a ThomasSolver instance for it
    ThomasSolver<MatrixType> thomasSolver(matrix);
    // Return the solution which is the temperature vector
    return thomasSolver.ThomasAlgorithm(forcingTerm);
};
} // end of namespace