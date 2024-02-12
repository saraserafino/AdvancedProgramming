#include "../include/Optimisation.hpp"
#include "../include/GradientDescent.hpp"

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
    virtual double evaluate(const std::vector<double> &theta) const override {
        PYBIND11_OVERRIDE_PURE(
            double, /* Return type. */
            OptimizationProblem,      /* Parent class. */
            evaluate,        /* Name of function in C++ (must match Python name). */
            theta      /* Argument(s). */
        );
    }

  virtual std::vector<double> evaluate_gradient(const std::vector<double> &theta) const override {
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
        .def(py::init<const unsigned int>(),
            py::arg("dimension"));

    py::class_<QuadraticOptimizationProblem, OptimizationProblem>(m, "QuadraticOptimizationProblem")
        .def(py::init<const unsigned int>(),
            py::arg("dimension"));
        
    py::class_<LinearRegressionProblem, OptimizationProblem>(m, "LinearRegressionProblem")
        .def(py::init<const unsigned int, const unsigned int>(),
            py::arg("dimension"), py::arg("num_points"))
        .def("generate_random_points", &LinearRegressionProblem::generate_random_points, py::arg("num_points"));
    
    py::class_<GradientDescent<LinearRegressionProblem>>(m, "GradientDescentLinearRegression")
        .def(py::init<const LinearRegressionProblem&>(), py::arg("LinearRegressionProblem"))
        .def("set_learningRateLinearRegressionProblem", &GradientDescent<LinearRegressionProblem>::set_learningRate, py::arg("learningRate"))
        .def("set_maxIterationsLinearRegressionProblem", &GradientDescent<LinearRegressionProblem>::set_maxIterations, py::arg("iterations"))
        .def("set_convergenceThresholdLinearRegressionProblem", &GradientDescent<LinearRegressionProblem>::set_convergenceThreshold, py::arg("convergenceThreshold"))
        .def("optimizeLinearRegressionProblem", &GradientDescent<LinearRegressionProblem>::optimize, py::arg("problem"))
        .def("get_solutionsLinearRegressionProblem", &GradientDescent<LinearRegressionProblem>::get_solutions);
}