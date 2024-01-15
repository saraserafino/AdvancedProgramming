#include "../include/IntegrationMethods.hpp"
#include <iostream>


namespace MODULEC {
// Constructor of the abstract class
Quadrature::Quadrature(double a, double b, unsigned int nBins) : weights(nBins + 1), nodes(nBins + 1), a(a), b(b), nBins(nBins) {}

Midpoint::Midpoint (double a, double b, unsigned int nBins) : Quadrature(a, b, nBins) {
    
}

} // end of namespace