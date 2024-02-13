#ifndef HEAT_DIFFUSION_HPP_
#define HEAT_DIFFUSION_HPP_

#include "../include/Matrix.hpp"
#include <iostream>
#include <vector>

namespace matrix {

class HeatDiffusion: public TridiagonalMatrix {
public:
    // Constructor
    HeatDiffusion(unsigned int &dimension, const double &initialTemperature,
                  const double &boundaryCondition1, const double &boundaryCondition2,
                  const std::vector<double>& forcingTerm);
    std::vector<double> solveH(std::vector<double> &f);
    virtual ~HeatDiffusion() {}; // Virtual destructor

protected:
unsigned int &dimension;
double dx;     // Spatial step size
const double initialTemperature; // Initial temperature
const double boundaryCondition1; // Boundary condition for u(0)
const double boundaryCondition2; // Boundary condition for u(L)
std::vector<double> forcingTerm; // Forcing term i.e. f(x)
};

} // end of namespace
#endif // HEAT_DIFFUSION_HPP_