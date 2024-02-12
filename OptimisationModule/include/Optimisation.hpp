#ifndef OPTIMISATION_HPP_
#define OPTIMISATION_HPP_

#include <iostream>
#include <vector>
#include <random> // for generating random numbers

namespace optimization {

// Abstract class
class OptimizationProblem {
public:
    OptimizationProblem(const unsigned int dimension); // Constructor

    // Method for evaluating the objective function
    virtual double evaluate(const std::vector<double> &theta) const = 0;
    // Method for evaluating its gradient
    virtual std::vector<double> evaluate_gradient(const std::vector<double> &theta) const = 0;
    virtual ~OptimizationProblem() {}; // Virtual destructor

protected:
    const unsigned int dimension; // dimension of the problem
};

// Derived classes from OptimizationProblem

class QuadraticOptimizationProblem : public OptimizationProblem {
public:
    // Hereditates the constructor
    using OptimizationProblem::OptimizationProblem;
};

class LinearRegressionProblem : public OptimizationProblem {
public:
    LinearRegressionProblem(const unsigned int dimension, const unsigned int num_points);
    double evaluate(const std::vector<double> &theta) const override;
    std::vector<double> evaluate_gradient(const std::vector<double> &theta) const override;
    void generate_random_points(unsigned int num_points);
    ~LinearRegressionProblem() {}; // Default destructor

private:
std::vector<double> x;
std::vector<double> y;
std::vector<double> yhat;
unsigned int num_points; // number of points to be generated
};

} // end of namespace
#endif // OPTIMISATION_HPP_
