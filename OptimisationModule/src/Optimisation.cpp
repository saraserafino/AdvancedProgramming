#include "../include/IntegrationMethods.hpp"
#include <iostream>


namespace optimization {

// Constructor of the abstract class
OptimizationProblem::OptimizationProblem(const T& problem);

// Derived classes from OptimizationProblem

QuadraticOptimizationProblem::QuadraticOptimizationProblem ();
double QuadraticOptimizationProblem::evaluate(const std::vector<double> &input) override;
std::vector<double> QuadraticOptimizationProblem::evaluate_gradient(const std::vector<double> &input) override;



LinearRegressionProblem::LinearRegressionProblem ();
double LinearRegressionProblem::evaluate(const std::vector<double> &input) override;
std::vector<double> LinearRegressionProblem::evaluate_gradient(const std::vector<double> &input) override;


template <typename T> GradientDescent::GradientDescent(const T& problem) : OptimizationProblem(problem);

std::vector<double> optimize(std::vector<double> initialGuess, double learningRate, int numIterations) {
    for (int i = 0; i < numIterations; ++i) {
    // Compute the gradient of the optimization problem at the current parameters
        std::vector<double> gradient = problem.evaluate_gradient(initialGuess);

        // Update parameters using gradient descent
        for (size_t j = 0; j < initialGuess.size(); ++j) {
            initialGuess[j] -= learningRate * gradient[j];
        }

        // Print intermediate results (optional)
        std::cout << "Iteration " << i + 1 << ": Objective Value = " << problem.evaluate(initialGuess) << std::endl;
    }

    return initialGuess;
}

} // end of namespace