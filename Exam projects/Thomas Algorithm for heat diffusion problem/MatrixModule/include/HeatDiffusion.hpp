#ifndef HEAT_DIFFUSION_HPP_
#define HEAT_DIFFUSION_HPP_

#include "Matrix.hpp"
#include "mpParser.h" // for using muParserX
#include <iostream>
#include <vector>

namespace moduleH {

class HeatDiffusion {
public:
    // Constructor
    HeatDiffusion(int dimension, double L, const double boundaryCondition1, const double boundaryCondition2);

    // Declare ThomasSolver as a friend so that it can access necessary operations
    //template<typename MatrixType>
    //friend class ThomasSolver;

    // Function to evaluate in point y
    mup::Value evaluate(double y, mup::ParserX& parser);

    // Solve the heat diffusion problem using the Thomas Algorithm
    template<typename MatrixType>
    std::vector<double> solveHeatProblem(const std::string &function);

    // Validate the solution against the exact solution
    double validate_solution(const std::vector<double> solution, const std::string &exactSol);

    ~HeatDiffusion() {}; // Default destructor

protected:
int dimension;
std::vector<double> a; // subdiagonal
std::vector<double> b; // diagonal
std::vector<double> c; // superdiagonal
double L; // Upper boundary of domain
const double boundaryCondition1; // Boundary condition for u(0)
const double boundaryCondition2; // Boundary condition for u(L)
std::vector<double> forcingTerm; // Forcing term i.e. f(x)
};
} // end of namespace
#include "HeatDiffusion.tpl.hpp"
#endif // HEAT_DIFFUSION_HPP_