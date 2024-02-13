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
        .def(py::init<int>(),
            py::arg("dimension"))
        .def("operator()", &Matrix::operator())
        .def("print_matrix", &Matrix::print_matrix)
        .def("get_num_rows", &Matrix::get_num_rows)
        .def("get_num_columns", &Matrix::get_num_columns);

    py::class_<TridiagonalMatrix, Matrix>(m, "TridiagonalMatrix")
        .def(py::init<std::vector<double>, std::vector<double>, std::vector<double>>(),
            py::arg("a"), py::arg("b"), py::arg("c"));
        
    py::class_<HeatDiffusion>(m, "HeatDiffusion")
        .def(py::init<int, double, const double, const double>(),
            py::arg("dimension"), py::arg("initialTemperature"),
            py::arg("boundaryCondition1"), py::arg("boundaryCondition2"))
        .def("solveH", &HeatDiffusion::solveH, py::arg("f"));
}