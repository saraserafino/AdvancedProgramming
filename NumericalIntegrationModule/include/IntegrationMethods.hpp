#ifndef INTEGRATION_METHODS_HPP_
#define INTEGRATION_METHODS_HPP_

#include <iostream>
#include <vector>

namespace MODULEC {

// Abstract class to initializing quadrature methods and returning weights and nodes
class Quadrature {
public:
    Quadrature(double a, double b, unsigned int nBins); // Constructor
    virtual ~Quadrature() {}; // Virtual destructor

protected:

};

// Derived class

class Midpoint : public Quadrature {
public:
    Midpoint (double a, double b, unsigned int nBins);
    ~Midpoint() {}; // Default destructor
};

} // end of namespace
#endif // INTEGRATION_METHODS_HPP_
