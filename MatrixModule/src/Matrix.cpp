#include "../include/Matrix.hpp"
#include <iostream>
#include <cmath>


namespace matrix {

// Constructor of the abstract class
Matrix::Matrix(int dimension) : dimension(dimension) {
    data.resize(dimension*dimension);
};

unsigned int Matrix::get_num_columns() const {
    return dimension;
}

unsigned int Matrix::get_num_rows() const {
  return dimension;
}

// It returns the value of the element in row = input_row_idx and column = input_col_idx
double Matrix::operator()(unsigned int input_row_idx, unsigned int input_col_idx) const {
    if(input_row_idx >= this->get_num_rows() || input_col_idx >= this->get_num_columns() || input_row_idx < 0 || input_col_idx < 0) {
    throw std::out_of_range ("Indexes out of range");
    }
    return data[input_row_idx * dimension + input_col_idx];
}

void Matrix::print_matrix(const Matrix& mat) const {
    for (unsigned int i = 0; i < mat.get_num_rows(); ++i) {
        for (unsigned int j = 0; j < mat.get_num_columns(); ++j) {
            std::cout << mat(i, j) << " ";
        }
        std::cout << std::endl;
    }
};

// Derived class from Matrix

TridiagonalMatrix::TridiagonalMatrix(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c)
        : Matrix(a.size()), a(a), b(b), c(c) {};
// Assuming a, b, c have same size


std::vector<double> TridiagonalMatrix::solve(std::vector<double> &f) {
    // Check size compatibility via exception handling
    if (f.size() != dimension) {
        throw std::invalid_argument("Right-hand side vector size f does not match matrix dimensions.");
    }
    // Create the unknown vector
    std::vector<double> u(dimension);
    // Step 1
    for (unsigned int i = 1; i < dimension; ++i) {
        double m = a[i] / b[i - 1];
        b[i] = b[i] - m * c[i - 1];
        f[i] = f[i] - m * f[i - 1];
    }
    // Step 2
    u[dimension - 1] = f[dimension - 1] / b[dimension - 1];
    unsigned int i = dimension - 1;
    while (i > 1) {
        u[i - 1] = ( f[i - 1] - c[i - 1] * u[i] ) / b[i - 1];
        i -= 1;
    }
};

} // end of namespace