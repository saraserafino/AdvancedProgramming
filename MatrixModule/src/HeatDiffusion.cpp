#include "../include/Matrix.hpp"
#include "../include/HeatDiffusion.hpp"

namespace matrix {

HeatDiffusion::HeatDiffusion(unsigned int &dimension, const double &initialTemperature,
                            const double &boundaryCondition1, const double &boundaryCondition2, const std::vector<double>& forcingTerm)
          : dimension(dimension), initialTemperature(initialTemperature),
          boundaryCondition1(boundaryCondition1), boundaryCondition2(boundaryCondition2),
          forcingTerm(forcingTerm) {
    // Fill the vector domain with the equally spaced temperatures
    std::vector<double> domain(dimension + 1);
    double h = initialTemperature / (dimension + 1);
    for (unsigned int i = 0; i < dimension + 1; ++i) {
        domain[i] = i * h;
    }

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
    c[dimension - 1] = 0;
    };

std::vector<double> HeatDiffusion::solveH(std::vector<double> &f) {
    TridiagonalMatrix heatmatrix(a, b, c);
};

} // end of namespace