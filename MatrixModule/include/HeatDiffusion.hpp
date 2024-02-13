#ifndef HEAT_DIFFUSION_HPP_
#define HEAT_DIFFUSION_HPP_

#include "../include/Matrix.hpp"
#include <iostream>
#include <vector>

namespace matrix {

class HeatDiffusion: public TridiagonalMatrix {
public:
    // Constructor
    HeatDiffusion(unsigned int &dimension);
    virtual ~HeatDiffusion() {}; // Virtual destructor

protected:
unsigned int &dimension;
double length; // Length of the domain
double time;   // Total simulation time
double dx;     // Spatial step size
double dt;     // Time step size
double alpha;  // Thermal diffusivity
std::vector<double> initialTemperature; // Initial temperature distribution
std::vector<double> boundaryConditions; // Boundary conditions
std::vector<double> forcingTerm;        // Forcing term
};

} // end of namespace
#endif // HEAT_DIFFUSION_HPP_