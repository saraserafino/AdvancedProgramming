#include "../include/Optimisation.hpp"
#include <iostream>
#include <cmath>


namespace optimization {

// Constructor of the abstract class
OptimizationProblem::OptimizationProblem(const unsigned int dimension) : dimension(dimension) {};

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