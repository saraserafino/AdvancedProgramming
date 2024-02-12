#include "GradientDescent.hpp"

#include <iostream>
#include <random>

//using namespace optimization;
namespace optimization {

template <typename T> GradientDescent<T>::GradientDescent(const T& problem)
    : problem(problem), learningRate(0.001), iterations(10000), convergenceThreshold(1e-5) {};


template <typename T>
std::vector<double> GradientDescent<T>::optimize(const T& problem) { 
    return current_solution;
};

template <typename T>
void GradientDescent<T>::set_learningRate(double learningRate) {
    this->learningRate = learningRate;
};

template <typename T>
std::pair<std::vector<double>, double> GradientDescent<T>::get_solutions() {
    std::vector<double> solution = optimize(problem);
    const double constfunction = problem.evaluate(solution);
    return std::make_pair(solution, constfunction);
};
} // end namespace