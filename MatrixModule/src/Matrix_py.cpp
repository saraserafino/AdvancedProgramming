#include "../include/Matrix.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ----------------------------------
// Python interface - trampoline
// ----------------------------------

using namespace matrix;

class PyMatrix : public Matrix {
public:
    // Inherit the constructors
    using Matrix::Matrix;

    // Trampoline (one for each virtual function).
    virtual std::vector<double> solve(std::vector<double> &f) override {
        PYBIND11_OVERRIDE_PURE(
            std::vector<double>, /* Return type. */
            Matrix,      /* Parent class. */
            solve,        /* Name of function in C++ (must match Python name). */
            f      /* Argument(s). */
        );
    }
};


namespace py = pybind11;

// Wrap as Python module

PYBIND11_MODULE(matrix, m) {
    m.doc() = "pybind11 matrix plugin";

    py::class_<Matrix, PyMatrix>(m, "Matrix")
        .def(py::init<unsigned int>(),
            py::arg("dimension"));

    py::class_<TridiagonalMatrix, Matrix>(m, "TridiagonalMatrix")
        .def(py::init<std::vector<double>, std::vector<double>, std::vector<double>>(),
            py::arg("a"), py::arg("b"), py::arg("c"));
        
    py::class_<HeatDiffusion, TridiagonalMatrix>(m, "HeatDiffusion")
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