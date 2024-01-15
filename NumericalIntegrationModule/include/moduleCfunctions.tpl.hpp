#include "IntegrationMethods.hpp"
#include "moduleCfunctions.hpp"
#include <iostream>

using namespace MODULEC;

// Define the function to evaluate in point y
mup::Value evaluate(double y, mup::ParserX& parser) {
    // Remove any existing variable x to ensure a clean slate
    parser.RemoveVar("x");
    // Create variable x with value a
	mup::Value x(y);
    parser.DefineVar("x", mup::Variable(&x));
    // Evaluate the expression
    return parser.Eval();
};

// Function to integrate for whichever method
template<typename T>
double Integrate(const std::string& function, const T& method) {
    static_assert(std::is_base_of<Quadrature, T>::value, "T must be derived from Quadrature.");

    // Create the parser instance
    mup::ParserX parser;
    // Set the expression
    parser.SetExpr(function);

    double sum = 0;
    // Get nodes and weights of the used Numerical Integration method
    const std::vector<double> weights = method.get_weights();
    const std::vector<double> nodes = method.get_nodes();
    // Evaluate the expression at the current node
    for (unsigned int i = 0; i < weights.size(); ++i) {
        double ev = evaluate(nodes[i], parser);
        sum += ev * weights[i];
    }
    return sum;
};

// When T is GaussLegendre, this version is invoked
template<>
double Integrate<GaussLegendre>(const std::string& function, const GaussLegendre& method) {
    // Create the parser instance
    mup::ParserX parser;
    // Set the expression
    parser.SetExpr(function);

    double sum = 0;
    // Evaluate the expression at the current node until the number
    // of subintervals nodes.size() = weights.size() = n
    for(unsigned int i = 0; i <= weights.size(); i++) {
        double ev = evaluate(width * nodes[i] + mean, parser);
        sum += weights[i] * ev;
    }
    return sum * width;
}
    
template <typename QuadratureMethod>
std::tuple<std::vector<double>, std::vector<double>> computeConvergenceOrder(const std::string& function, const double exactIntegral) {
    static_assert(std::is_base_of<Quadrature, QuadratureMethod>::value, "QuadratureMethod must be derived from Quadrature.");

    // Create the parser instance
    mup::ParserX parser;
    // Set the expression
    parser.SetExpr(function);
    double previousError = 1.0;

    for (unsigned int nBins = 2; nBins <= 1024; nBins *= 2) {
        QuadratureMethod method(a, b, nBins);
    }
    return std::make_tuple(errors, orders);
};