#include "../include/Matrix.hpp"
#include "../include/HeatDiffusion.hpp"

namespace matrix {

HeatDiffusion::HeatDiffusion(int dimension, double &initialTemperature, const double &boundaryCondition1, const double &boundaryCondition2)
    : dimension(dimension), initialTemperature(initialTemperature),
    boundaryCondition1(boundaryCondition1), boundaryCondition2(boundaryCondition2) {};

std::vector<double> HeatDiffusion::solveH(std::vector<double> &f) {
    // Fill the vector domain with the equally spaced temperatures
    std::vector<double> domain(dimension + 1);
    // Calculate number of spatial steps
    double h = initialTemperature / (dimension + 1);
    for (unsigned int i = 0; i < dimension + 1; ++i) {
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
    c[dimension - 1] = 0;

    // Compute f
    forcingTerm.resize(dimension, h * h);
    forcingTerm[0] = boundaryCondition1;
    forcingTerm[dimension - 1] = boundaryCondition2;

    for (unsigned int i = 1; i < dimension - 1; ++i) {
        forcingTerm[i] *= f[i];
    }

    // Initialize temperature vector with initial conditions
    std::vector<double> temperature;
    temperature[0] = initialTemperature;

    TridiagonalMatrix heatmatrix(a, b, c);
    temperature = heatmatrix.solve(forcingTerm);
    return temperature;
};

} // end of namespace