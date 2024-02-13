#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <iostream>
#include <vector>
#include <random> // for generating random numbers

namespace matrix {

// Abstract class
class Matrix {
public:
    // Constructor
    Matrix(std::vector<double>& values, std::vector<unsigned int>& columns, std::vector<unsigned int>& rows);

    virtual double& operator()(unsigned int input_row_idx, unsigned int input_col_idx) = 0;
    virtual double operator()(unsigned int input_row_idx, unsigned int input_col_idx) const = 0;
    virtual std::vector<double> operator* (const std::vector<double>& vect) const = 0;
    virtual void print_matrix() const = 0;
    // Method that solves a linear system given a right hand side f and returns its solution
    virtual std::vector<double> solve(const std::vector<double> &f);
    
    unsigned int get_num_rows() const;
    unsigned int get_num_columns() const;
    unsigned int get_num_nnz() const;
    virtual ~Matrix() {}; // Virtual destructor

protected:
// the vector values contains all the values
std::vector<double> values;
std::vector<unsigned int> columns;
std::vector<unsigned int> rows;
};


// Derived classes from Matrix

class TridiagonalMatrix : public Matrix {
    TridiagonalMatrix(const unsigned int dimension, const unsigned int num_points);
    // Override it to implement the Thomas algorithm
    std::vector<double> solve(const std::vector<double> &f) override;
    ~TridiagonalMatrix() {}; // Default destructor

private:



std::vector<double> x;
std::vector<double> y;
std::vector<double> yhat;
unsigned int num_points; // number of points to be generated
};

} // end of namespace
#endif // MATRIX_HPP_
