#include "../include/Optimisation.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ----------------------------------
// Python interface - trampoline
// ----------------------------------

using namespace optimization;

class PyOptimizationProblem : public OptimizationProblem {
public:
    // Inherit the constructors
    using OptimizationProblem::OptimizationProblem;

  // Trampoline (one for each virtual function).
  virtual double evaluate(const std::vector<double> &theta) override {
    PYBIND11_OVERRIDE_PURE(
        const std::vector<double>, /* Return type. */
        OptimizationProblem,      /* Parent class. */
        evaluate,        /* Name of function in C++ (must match Python name). */
        theta      /* Argument(s). */
    );
  }

  virtual std::vector<double> evaluate_gradient(const std::vector<double> &theta) override {
    PYBIND11_OVERRIDE_PURE(
        std::vector<double>, /* Return type. */
        OptimizationProblem,      /* Parent class. */
        evaluate_gradient,        /* Name of function in C++ (must match Python name). */
        theta      /* Argument(s). */
    );
  }
};


namespace py = pybind11;

// Wrap as Python module

PYBIND11_MODULE(optimization, m) {
    m.doc() = "pybind11 optimization plugin";

    py::class_<OptimizationProblem, PyOptimizationProblem>(m, "OptimizationProblem")
        .def(py::init<const std::vector<double>>(),
            py::arg("theta"));

    py::class_<QuadraticOptimizationProblem, OptimizationProblem>(m, "QuadraticOptimizationProblem")
        .def(py::init<const std::vector<double>>(),
            py::arg("theta"));
        
    py::class_<LinearRegressionProblem, OptimizationProblem>(m, "LinearRegressionProblem")
        .def(py::init<const std::vector<double>>(),
            py::arg("theta"))
        .def("compute_yhat", &compute_yhat, py::arg("theta"));
    
    py::class_<GradientDescent>(m, "GradientDescent")
        .def(py::init<const T&>(),
            py::arg("problem"))
        .def("set_learningRate", &set_learningRate, py::arg("learningRate"))
        .def("set_maxIterations", &set_maxIterations, py::arg("iterations"))
        .def("set_convergenceThreshold", &set_convergenceThreshold, py::arg("convergenceThreshold"))
        .def("optimize", &optimize)
        .def("getSolution", &getSolution, py::arg("solution"));
}
