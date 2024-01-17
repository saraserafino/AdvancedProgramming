#ifndef OPTIMIZATION_HPP_
#define OPTIMIZATION_HPP_

#include <iostream>
#include <vector>

namespace optimization {

// Abstract class
class OptimizationProblem {
public:
    OptimizationProblem(const T& problem); // Constructor

    // Method for evaluating the objective function
    virtual double evaluate(const std::vector<double> &input) = 0;
    // Method for evaluating its gradient
    virtual std::vector<double> evaluate_gradient(const std::vector<double> &input) = 0;

    virtual ~OptimizationProblem() {}; // Virtual destructor

protected:

};

// Derived classes from OptimizationProblem

class QuadraticOptimizationProblem : public OptimizationProblem {
public:
    QuadraticOptimizationProblem ();
    double evaluate(const std::vector<double> &input) override;
    std::vector<double> evaluate_gradient(const std::vector<double> &input) override;
    ~QuadraticOptimizationProblem() {}; // Default destructor
};

class LinearRegressionProblem : public OptimizationProblem {
public:
    LinearRegressionProblem ();
    double evaluate(const std::vector<double> &input) override;
    std::vector<double> evaluate_gradient(const std::vector<double> &input) override;
    ~LinearRegressionProblem() {}; // Default destructor
};

template <typename T>
class GradientDescent {
public:
    GradientDescent(const T& problem);



    ~GradientDescent() {}; // Default destructor

private:

};

} // end of namespace
#endif // OPTIMIZATION_HPP_
