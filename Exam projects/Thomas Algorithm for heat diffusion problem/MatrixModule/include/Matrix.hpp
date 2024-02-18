#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <iostream>
#include <vector>

namespace moduleH {

// Abstract class
class Matrix {
public:
    // Constructor
    Matrix(int dimension);

    double operator()(unsigned int input_row_idx, unsigned int input_col_idx) const;
    void print_matrix(const Matrix& mat) const;

    // Method that solves a linear system given a right hand side f and returns its solution
    virtual std::vector<double> solve(std::vector<double> &f);
    
    unsigned int get_num_rows() const;
    unsigned int get_num_columns() const;
    virtual ~Matrix() {}; // Virtual destructor

protected:
int dimension;
std::vector<double> data;
};


// Derived class from Matrix

class TridiagonalMatrix : public Matrix {
public:
    TridiagonalMatrix(std::vector<double> a, std::vector<double> b, std::vector<double> c);

    // Override it to implement the Thomas algorithm
    std::vector<double> solve(std::vector<double> &f) override;

    ~TridiagonalMatrix() {}; // Default destructor

protected:
std::vector<double> a; // subdiagonal
std::vector<double> b; // diagonal
std::vector<double> c; // superdiagonal
};

} // end of namespace
#endif // MATRIX_HPP_
