#ifndef HEAT_DIFFUSION_HPP_
#define HEAT_DIFFUSION_HPP_

#include "../include/Matrix.hpp"
#include <iostream>
#include <vector>

namespace matrix {

class HeatDiffusion {
public:
    // Constructor
    HeatDiffusion(int dimension, double &initialTemperature, const double &boundaryCondition1, const double &boundaryCondition2);
    std::vector<double> solveH(std::vector<double> &f);
    ~HeatDiffusion() {}; // Virtual destructor

protected:
int dimension;
std::vector<double> a; // subdiagonal
std::vector<double> b; // diagonal
std::vector<double> c; // superdiagonal
double dx;     // Spatial step size
double initialTemperature; // Initial temperature
const double boundaryCondition1; // Boundary condition for u(0)
const double boundaryCondition2; // Boundary condition for u(L)
std::vector<double> forcingTerm; // Forcing term i.e. f(x)
};

} // end of namespace
#endif // HEAT_DIFFUSION_HPP_