#include "../include/Matrix.hpp"
#include "../include/HeatDiffusion.hpp"

namespace matrix {

HeatDiffusion::HeatDiffusion(double length, double time, double dx, double dt, double alpha,
                  const std::vector<double>& initialTemperature,
                  const std::vector<double>& boundaryConditions,
                  const std::vector<double>& forcingTerm)
        : length(length), time(time), dx(dx), dt(dt), alpha(alpha),
          initialTemperature(initialTemperature),
          boundaryConditions(boundaryConditions),
          forcingTerm(forcingTerm) {};

HeatDiffusion::HeatDiffusion(unsigned int &dimension) : dimension(dimension) {
    // subdiagonal
    std::vector<double> a(dimension, 1);
    a[dimension - 1] = 0;
    // diagonal
    std::vector<double> b(dimension, -2);
    b[0] = 1;
    b[dimension - 1] = 1;
    // superdiagonal
    std::vector<double> c(dimension, 1);
    c[0] = 0;
    c[dimension - 2] = 0;
    TridiagonalMatrix heatmatrix(a, b, c);
    };



} // end of namespace