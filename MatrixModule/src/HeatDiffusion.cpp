#include "../include/Matrix.hpp"
#include "../include/HeatDiffusion.hpp"

namespace matrix {

HeatDiffusion::HeatDiffusion(unsigned int &dimension, double &initialTemperature,
                            const double &boundaryCondition1, const double &boundaryCondition2)
          : TridiagonalMatrix(a,b,c), dimension(dimension), initialTemperature(initialTemperature),
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

        // Initialize matrices and vectors
        std::vector<double> a(numSteps - 1, -alpha / (dx * dx));
        std::vector<double> b(numSteps, 1 + 2 * alpha / (dx * dx));
        std::vector<double> c(numSteps - 1, -alpha / (dx * dx));
        std::vector<double> f(numSteps);

    // Initialize temperature vector with initial conditions
    std::vector<double> temperature;
    temperature[0] = initialTemperature;

    // Time-stepping loop
    for (double t = 0; t < time; t += dt) {
            // Apply boundary conditions
            temperature.front() = boundaryConditions.front();
            temperature.back() = boundaryConditions.back();

            // Calculate forcing term
            for (int i = 0; i < numSteps; ++i) {
                f[i] = forcingTerm[i] * dt + temperature[i];
            }

            // Solve the tridiagonal linear system
            TridiagonalMatrix heatmatrix(a, b, c);
            temperature = heatmatrix.solve(f);
        }
    return temperature;
};

} // end of namespace