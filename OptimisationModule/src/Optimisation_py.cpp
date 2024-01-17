#include "../include/IntegrationMethods.hpp"
#include "../include/moduleCfunctions.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ----------------------------------
// Python interface - fake trampoline
// ----------------------------------

class PyQuadrature : public MODULEC::Quadrature {
public:
    // Inherit the constructors
    using MODULEC::Quadrature::Quadrature;

    // Each virtual function needs a trampoline, but there isn't any
};

namespace py = pybind11;
using namespace MODULEC;

// Wrap as Python module

PYBIND11_MODULE(moduleC, m) {
    m.doc() = "pybind11 moduleC plugin";

    py::class_<Quadrature, PyQuadrature>(m, "Quadrature")
        .def(py::init<double, double, unsigned int>(),
            py::arg("a"), py::arg("b"), py::arg("nBins"))
        .def("get_weights", &Quadrature::get_weights, "Get the weights of the function to integrate")
        .def("get_nodes", &Quadrature::get_nodes, "Get the nodes of the function to integrate");

    py::class_<Midpoint, Quadrature>(m, "Midpoint")
        .def(py::init<double, double, unsigned int>(),
            py::arg("a"), py::arg("b"), py::arg("nBins"));
        
    py::class_<GaussLegendre, Quadrature>(m, "GaussLegendre")
        .def(py::init<double, double, unsigned int>(),
            py::arg("a"), py::arg("b"), py::arg("nBins"))
        .def("get_a", &GaussLegendre::get_a, "Get the lower bound of the function to integrate")
        .def("get_b", &GaussLegendre::get_b, "Get the upper bound of the function to integrate");

    m.def("evaluate", &evaluate, py::arg("y"), py::arg("parser"));
    
    // Explicit instantion of the template methods for each derived class
    m.def("IntegrateMidpoint", &Integrate<Midpoint>,
        py::arg("function"), py::arg("method"));
    m.def("IntegrateTrapezoidal", &Integrate<Trapezoidal>,
        py::arg("function"), py::arg("method"));
}
