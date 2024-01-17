#ifndef OPTIMIZATION_HPP_
#define OPTIMIZATION_HPP_

#include <iostream>
#include <vector>

namespace optimization {

// Abstract class
class OptimizationProblem {
public:
    OptimizationProblem(const std::vector<double> &input); // Constructor

    // Method for evaluating the objective function
    virtual double evaluate(const std::vector<double> &input) = 0;
    // Method for evaluating its gradient
    virtual std::vector<double> evaluate_gradient(const std::vector<double> &input) = 0;

    virtual ~OptimizationProblem() {}; // Virtual destructor

protected:
    const std::vector<double> &input;
};

// Derived classes from OptimizationProblem

class QuadraticOptimizationProblem : public OptimizationProblem {
public:
    QuadraticOptimizationProblem ();
    // The input is theta
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

    void set_learningRate(double learningRate);
    void set_maxIterations(int iterations);


    std::vector<double> optimize(std::vector<double> initialGuess, double learningRate, int iterations);

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
