#ifndef GRADIENT_DESCENT_HPP_
#define GRADIENT_DESCENT_HPP_

namespace optimization {

template <typename T>
class GradientDescent {
public:
    GradientDescent(const T& problem);

    void set_learningRate(double learningRate);
    void set_maxIterations(int iterations);
    void set_convergenceThreshold(double convergenceThreshold);

    std::vector<double> optimize(const T& problem);

    // Method that returns the final solution and the const function evaluated at that solution
    std::pair<std::vector<double>, double> get_solutions();

    ~GradientDescent() {}; // Default destructor

private:
    // For the input polymorphic OptimizationProblem object
    const T& problem;
    double learningRate;
    int iterations;
    double convergenceThreshold;
};
} // end namespace

#include "GradientDescent.tpl.hpp"

#endif // GRADIENT_DESCENT_HPP_