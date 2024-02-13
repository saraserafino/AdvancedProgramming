#include "../include/Matrix.hpp"
#include <iostream>
#include <cmath>


namespace matrix {

// Constructor of the abstract class
Matrix::Matrix(std::vector<double>& values, std::vector<unsigned int>& columns, std::vector<unsigned int>& rows) : dimension(dimension) {};

// returns the number of columns of the matrix. For the way it's saved, the number
// of columns is the maximum index of column of the non-zero values + 1
unsigned int Matrix::get_num_columns() const {
    return values.empty() ? 0 : (*std::max_element(columns.begin(), columns.end()) + 1);
}

// Returns the number of rows of the matrix. For the way it's saved,
// the number of rows is the maximum index of row of the the non-zero values + 1
unsigned int Matrix::get_num_rows() const {
  return values.empty() ? 0 : (*std::max_element(rows.begin(), rows.end()) + 1);
}

// Since it's const, it doesn't return the reference but the value
double Matrix::operator()(unsigned int input_row_idx, unsigned int input_col_idx) const {
  if(input_row_idx >= this->get_num_rows() || input_col_idx >= this->get_num_columns()) {
    throw std::out_of_range ("Indexes out of range");
  }

  for(int i = 0; i < values.size(); ++i)
    if(rows[i] == input_row_idx && columns[i] == input_col_idx)
      return values[i];

  return 0.0;
}

// Derived classes from OptimizationProblem

// Constructor for setting also the number of points
LinearRegressionProblem::LinearRegressionProblem(const unsigned int dimension, const unsigned int num_points)
    : OptimizationProblem(dimension), num_points(num_points) {
        generate_random_points(num_points);
    };

double LinearRegressionProblem::evaluate(const std::vector<double> &theta) const {

};

std::vector<double> LinearRegressionProblem::evaluate_gradient(const std::vector<double> &theta) const {
    
};

// Method for generating random points x between -50 and 50
void LinearRegressionProblem::generate_random_points(unsigned int num_points) {
    x.resize(num_points);
    y.resize(num_points, 4.0);

    // Generate random numbers
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> dis(-10, 10);

    // Generate random noise
    std::normal_distribution<double> noise_dis(0.0, 0.1);

    // Generate random point x, y = 4 + x/2 + epsilon
    for (int i = 0; i < num_points; ++i) {
        x[i] = dis(gen);
        y[i] += ( x[i]/2.0 + noise_dis(gen));
    }
};

} // end of namespace