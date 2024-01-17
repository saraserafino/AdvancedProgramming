#include "../include/Optimisation.hpp"
#include <iostream>
#include <cmath>


namespace optimization {

// Constructor of the abstract class
OptimizationProblem::OptimizationProblem(const std::vector<double> &input) : input(input) {};


// Derived classes from OptimizationProblem

QuadraticOptimizationProblem::QuadraticOptimizationProblem ();

double QuadraticOptimizationProblem::evaluate(const std::vector<double> &input) {
    return input[0] * input[0] + input[1] * input[1];
};

std::vector<double> QuadraticOptimizationProblem::evaluate_gradient(const std::vector<double> &input) {
    return {2 * input[0], 2 * input[1]};
};



LinearRegressionProblem::LinearRegressionProblem ();

double LinearRegressionProblem::evaluate(const std::vector<double> &input) {
    return (input[0] - 2) * (input[0] - 2) + (input[1] + 3) * (input[1] + 3);
};

std::vector<double> LinearRegressionProblem::evaluate_gradient(const std::vector<double> &input) {
    return {2 * (input[0] - 2), 2 * (input[1] + 3)};
};


template <typename T> GradientDescent::GradientDescent(const T& problem)
    : problem(problem), learningRate(0.01), iterations(1000), convergenceThreshold(1e-5) {};


std::vector<double> GradientDescent::optimize() const {
    double learningRate = this->learningRate;
    int iterations = this->iterations;
    double convergenceThreshold = this->convergenceThreshold;
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
    this.learningRate = learningRate;
};

void GradientDescent::set_maxIterations(int maxIterations) {
    this.iterations = maxIterations;
};

void GradientDescent::set_convergenceThreshold(double convergenceThreshold) {
    this.convergenceThreshold = convergenceThreshold;
};

double GradientDescent::getSolution(const std::vector<double>& solution) const {
    return problem.evaluate(solution);
}

} // end of namespace