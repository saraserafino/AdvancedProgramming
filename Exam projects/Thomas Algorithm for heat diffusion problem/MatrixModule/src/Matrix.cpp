#include "../include/Matrix.hpp"
#include "../include/ThomasSolver.hpp"
#include <iostream>
#include <cmath>
#include <Eigen/Sparse>

namespace moduleH {

// Constructor of the abstract class
Matrix::Matrix(int dimension) : dimension(dimension) {
    // The matrix is supposed to be a square matrix
    data.resize(dimension * dimension);
};

unsigned int Matrix::get_dimension() const {
    return dimension;
};

// Derived class from Matrix

TridiagonalMatrix::TridiagonalMatrix(std::vector<double> a, std::vector<double> b, std::vector<double> c)
    : Matrix(a.size()), a(a), b(b), c(c) {};

double TridiagonalMatrix::operator()(unsigned int input_row_idx, unsigned int input_col_idx) const {
    if(input_row_idx >= this->get_dimension() || input_col_idx >= this->get_dimension() || input_row_idx < 0 || input_col_idx < 0) {
        throw std::out_of_range ("Indexes out of range");
    }
    // It returns the value of the element in row = input_row_idx and column = input_col_idx
    return data[input_row_idx * dimension + input_col_idx];
};

void TridiagonalMatrix::printMatrix() const {
    for (unsigned int i = 0; i < dimension; ++i) {
        for (unsigned int j = 0; j < dimension; ++j) {
            if (i == j) // print diagonal value
                std::cout << b[i] << "\t";
            else if (i == j + 1) // print subdiagonal value
                std::cout << a[j] << "\t";
            else if (i == j - 1) // print superdiagonal value
                std::cout << c[i] << "\t";
            else // if there's nothing, print 0
                std::cout << "0\t";
        }
        // At the end of the row, break line
        std::cout << std::endl;
    }
};

std::vector<double> TridiagonalMatrix::get_a() const {
    return a;
};

std::vector<double> TridiagonalMatrix::get_b() const {
    return b;
};

std::vector<double> TridiagonalMatrix::get_c() const {
    return c;
};

std::vector<double> TridiagonalMatrix::solve(std::vector<double> &f) {
    TridiagonalMatrix matrix(a, b, c);
    // Create a ThomasSolver instance for solving it
    ThomasSolver<TridiagonalMatrix> thomasSolver(matrix);
    std::vector<double> solution = thomasSolver.ThomasAlgorithm(f);
    return solution;
};

EigenMatrix::EigenMatrix(std::vector<double> a, std::vector<double> b, std::vector<double> c)
    : Matrix(a.size()), a(a), b(b), c(c)
    {
        Eigen::SparseMatrix<double> sparseMatrix(a.size(), a.size());
        // forse qua dovrei inserire i valori a,b,c perché li uso in ThomasSolver ma non riempio
        // mai effetticvamente né questa né Tridiagonal
        this->sparseMatrix = sparseMatrix;
    };

double EigenMatrix::operator()(unsigned int input_row_idx, unsigned int input_col_idx) const {
    // Implement access to the elements of the sparse matrix using an already existent method
    return sparseMatrix.coeff(input_row_idx, input_col_idx);
};

void EigenMatrix::printMatrix() const {
   /* for (int i = 0; i < dimension; ++i) {
        // Insert diagonal value
        sparseMatrix.insert(i, i) = b[i];

        if (i > 0) // Insert subdiagonal value
            sparseMatrix.insert(i, i - 1) = a[i];

        if (i < dimension - 1) // Insert superdiagonal value
            sparseMatrix.insert(i, i + 1) = c[i];
    }*/
    std::cout << sparseMatrix << std::endl;
};

std::vector<double> EigenMatrix::get_a() const {
    return a;
};

std::vector<double> EigenMatrix::get_b() const {
    return b;
};

std::vector<double> EigenMatrix::get_c() const {
    return c;
};

std::vector<double> EigenMatrix::solve(std::vector<double> &f) {
    EigenMatrix matrix(a, b, c);
    // Create a ThomasSolver instance for solving it
    ThomasSolver<EigenMatrix> thomasSolver(matrix);
    return thomasSolver.ThomasAlgorithm(f);
};
} // end of namespace