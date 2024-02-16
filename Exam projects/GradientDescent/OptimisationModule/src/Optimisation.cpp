#include "../include/Optimisation.hpp"
#include <iostream>
#include <cmath>


namespace optimization {

// Constructor of the abstract class
OptimizationProblem::OptimizationProblem(const unsigned int dimension) : dimension(dimension) {};

const unsigned int OptimizationProblem::get_dimension () const {
    return dimension;
};

// Derived classes from OptimizationProblem

double QuadraticOptimizationProblem::evaluate(const std::vector<double> &theta) const {
    double value = 0;
    for (int i = 0; i < theta.size(); ++i)
        value += (theta[i] - 1) * (theta[i] - 1);
    return value;
};

std::vector<double> QuadraticOptimizationProblem::evaluate_gradient(const std::vector<double> &theta) const {
    std::vector<double> gradient(theta.size()); // it's the derivate
    for (int i = 0; i < theta.size(); ++i)
        gradient[i] = 2 * theta[i] - 2;
    return gradient;
};

// Constructor for setting also the number of points
LinearRegressionProblem::LinearRegressionProblem(const unsigned int dimension, const unsigned int num_points)
    : OptimizationProblem(dimension), num_points(num_points) {
        generate_random_points(num_points);
    };

// Function for computing y hat
std::vector<double> LinearRegressionProblem::compute_yhat(const std::vector<double> &theta) const {
    std::vector<double> yhat(theta.size(), theta[0]);
    for (int i = 0; i < num_points; ++i) {
        for (int j = 1; j < theta.size(); ++j) {
            yhat[i] += theta[j] * x[j];
        }
    }
    return yhat;
};

double LinearRegressionProblem::evaluate(const std::vector<double> &theta) const {
    // Compute y hat
    std::vector<double> yhat = compute_yhat(theta);
    // J(theta)
    double sum = 0;
    for (int i = 0; i < num_points; ++i) {
        sum += ( ((yhat[i]) - (y[i])) * ((yhat[i]) - (y[i])) );
    }
    return sum / (2 * num_points);
};

std::vector<double> LinearRegressionProblem::evaluate_gradient(const std::vector<double> &theta) const {
    std::vector<double> gradient(theta.size());
    std::vector<double> yhat = compute_yhat(theta);
    for (int j = 0; j < theta.size(); ++j) {
        // dJ/dthetaj
        double sum = 0;
        for (int i = 0; i < num_points; ++i) {
            // if theta=0 x=1, else =x[i]
            double x_j = j == 0 ? 1 : x[i];
            sum += ( ((yhat[i]) - (y[i])) * x_j );   
        }
        gradient[j] = sum / num_points;
    }
    return gradient;
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