#include "GradientDescent.hpp"

#include <iostream>
#include <random>

//using namespace optimization;
namespace optimization {

template <typename T> GradientDescent<T>::GradientDescent(const T& problem)
    : problem(problem), learningRate(0.001), iterations(10000), convergenceThreshold(1e-5) {};


template <typename T>
std::vector<double> GradientDescent<T>::optimize(const T& problem) {
    // Obtain the dimension of the problem
    const unsigned int dimension = problem.get_dimension();
    // Initial guess of the solution
    std::vector<double> initialGuess(dimension);
    // Generate random numbers for it
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> dis(-50, 50);
    for (int i = 0; i < dimension; ++i) {
        initialGuess[i] = dis(gen);
    }

    // The initial solution is the initial guess
    std::vector<double> current_solution = initialGuess;

    for (int iteration = 0; iteration < this->iterations; ++iteration) {
        std::vector<double> gradient = problem.evaluate_gradient(current_solution);
        // Update solution using gradient descent
        for (size_t i = 0; i < current_solution.size(); ++i) {
            current_solution[i] -= (learningRate * gradient[i]);
        }

        // Check for convergence i.e. until ||f(current_solution)|| is below a certain threshold
        if (std::abs(problem.evaluate(current_solution)) < convergenceThreshold) {
            return current_solution;
        }
    }
    // If convergence wasn't reached but the max number of iterations was reached, return the solution anyway
    std::cout << "Gradient Descent computed with C++ failed to converge within the specified iterations.";   
    return current_solution;
};

template <typename T>
void GradientDescent<T>::set_learningRate(double learningRate) {
    this->learningRate = learningRate;
};

template <typename T>
void GradientDescent<T>::set_maxIterations(int maxIterations) {
    this->iterations = maxIterations;
};

template <typename T>
void GradientDescent<T>::set_convergenceThreshold(double convergenceThreshold) {
    this->convergenceThreshold = convergenceThreshold;
};

template <typename T>
std::pair<std::vector<double>, double> GradientDescent<T>::get_solutions() {
    std::vector<double> solution = optimize(problem);
    const double constfunction = problem.evaluate(solution);
    return std::make_pair(solution, constfunction);
};
} // end namespace