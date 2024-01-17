#include "../include/Optimisation.hpp"
#include <iostream>
#include <cmath>


namespace optimization {

// Constructor of the abstract class
OptimizationProblem::OptimizationProblem(const std::vector<double> &theta) : theta(theta) {};


// Derived classes from OptimizationProblem

double QuadraticOptimizationProblem::evaluate(const std::vector<double> &theta) {
    return (theta[0] - 1) * (theta[0] - 1);
};

std::vector<double> QuadraticOptimizationProblem::evaluate_gradient(const std::vector<double> &theta) {
    return {2 * theta[0] - 2}; // derivate
};


std::vector<double> LinearRegressionProblem::compute_yhat(const std::vector<double> &theta);
    // Compute y hat
    std::vector<double> yhat;
    yhat[0] = theta[0];
    for (int i = 1; i < x.size(); ++i) {
        yhat[i] = theta[i] * x[i];
    }
    return yhat;

double LinearRegressionProblem::evaluate(const std::vector<double> &theta) {
    int m = theta.size();
    // Compute y hat
    std::vector<double> yhat = compute_yhat(theta);
    // J(theta)
    double sum = 0;
    for (int i = 0; i < m; ++i) {
        sum += ( ((yhat[i]) - (y[i])) * ((yhat[i]) - (y[i])) );
    }
    return sum / (2 * m);
};

std::vector<double> LinearRegressionProblem::evaluate_gradient(const std::vector<double> &theta) {
    std::vector<double> yhat = compute_yhat(theta);
    // dJ(theta)
    int m = theta.size();
    double sum = 0;
    for (int i = 0; i < m; ++i) {
        sum += ( ((yhat[i]) - (y[i])) * x[i] );
    }
    return sum / m;
};


template <typename T> GradientDescent::GradientDescent(const T& problem)
    : problem(problem), learningRate(0.01), iterations(1000), convergenceThreshold(1e-5) {};


std::vector<double> GradientDescent::optimize() const {
    // Initialize the solution to 0
    std::vector<double> current_solution(problem.evaluate_gradient(std::vector<double>(0)));
    for (int iteration = 0; iteration < iterations; ++iteration) {
        std::vector<double> gradient = problem.evaluate_gradient(current_solution);

        // Update solution using gradient descent
        for (size_t i = 0; i < current_solution.size(); ++i) {
            current_solution[i] -= learningRate * gradient[i];
        }

        // Check for convergence
        if (std::sqrt(std::inner_product(gradient.begin(), gradient.end(), gradient.begin(), 0.0)) < convergenceThreshold) {
            return current_solution;
        }
    }

    // Throw an exception if the algorithm fails to converge
    throw std::runtime_error("Gradient Descent failed to converge within the specified iterations.");
};

void GradientDescent::set_learningRate(double learningRate) {
    this->learningRate = learningRate;
};

void GradientDescent::set_maxIterations(int maxIterations) {
    this->iterations = maxIterations;
};

void GradientDescent::set_convergenceThreshold(double convergenceThreshold) {
    this->convergenceThreshold = convergenceThreshold;
};

double GradientDescent::getSolution(const std::vector<double>& solution) const {
    return problem.optimize(solution);
}

} // end of namespace