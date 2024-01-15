#ifndef MODULE_C_FUNCTIONS_HPP_
#define MODULE_C_FUNCTIONS_HPP_

#include "mpParser.h"
#include "IntegrationMethods.hpp"
#include <iostream>

using namespace MODULEC;

// Function to evaluate in point a
mup::Value evaluate(double y, mup::ParserX& parser);

// Function to integrate for whichever method
template<typename T>
double Integrate(const std::string& function, const T& method);

// When T is GaussLegendre, this version is invoked
template<>
double Integrate<GaussLegendre>(const std::string& function, const GaussLegendre& method);

template <typename QuadratureMethod>
std::tuple<std::vector<double>, std::vector<double>> computeConvergenceOrder(const std::string& function, const double exactIntegral);

#include "moduleCfunctions.tpl.hpp"

#endif // MODULE_C_FUNCTIONS_HPP_