#ifndef OPTIMIZATION_HPP_
#define OPTIMIZATION_HPP_

#include <iostream>
#include <vector>

namespace optimization {

// Abstract class
class OptimizationProblem {
public:
    OptimizationProblem(const std::vector<double> &theta); // Constructor

    // Method for evaluating the objective function
    virtual double evaluate(const std::vector<double> &theta) = 0;
    // Method for evaluating its gradient
    virtual std::vector<double> evaluate_gradient(const std::vector<double> &theta) = 0;

    virtual ~OptimizationProblem() {}; // Virtual destructor

protected:
    const std::vector<double> &theta;
};

// Derived classes from OptimizationProblem

class QuadraticOptimizationProblem : public OptimizationProblem {
public:
    // Hereditates the constructor
    using OptimizationProblem::OptimizationProblem;
    // The input is theta
    double evaluate(const std::vector<double> &theta) override;
    std::vector<double> evaluate_gradient(const std::vector<double> &theta) override;
    ~QuadraticOptimizationProblem() {}; // Default destructor
};

class LinearRegressionProblem : public OptimizationProblem {
public:
    using OptimizationProblem::OptimizationProblem;
    std::vector<double> compute_yhat(const std::vector<double> &theta);
    double evaluate(const std::vector<double> &theta) override;
    std::vector<double> evaluate_gradient(const std::vector<double> &theta) override;
    ~LinearRegressionProblem() {}; // Default destructor

private:
std::vector<double> x;
std::vector<double> y;
std::vector<double> yhat;
};

template <typename T>
class GradientDescent {
public:
    GradientDescent(const T& problem);

    void set_learningRate(double learningRate);
    void set_maxIterations(int iterations);
    void set_convergenceThreshold(double convergenceThreshold);

    std::vector<double> optimize();

    double getSolution(const std::vector<double>& solution) const;

    ~GradientDescent() {}; // Default destructor

private:
    // For the input polymorphic OptimizationProblem object
    const T& problem;
    double learningRate;
    int iterations;
    double convergenceThreshold;
};

} // end of namespace
#endif // OPTIMIZATION_HPP_
