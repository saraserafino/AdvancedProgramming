#include "../include/Matrix.hpp"
#include "../include/HeatDiffusion.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ----------------------------------
// Python interface - trampoline
// ----------------------------------

using namespace moduleH;

class PyMatrix : public Matrix {
public:
    // Inherit the constructors
    using Matrix::Matrix;

    // Trampoline (one for each virtual function).
    virtual double operator()(unsigned int input_row_idx, unsigned int input_col_idx) const override {
        PYBIND11_OVERRIDE_PURE(
            double, /* Return type. */
            Matrix,      /* Parent class. */
            operator(),        /* Name of function in C++ (must match Python name). */
            input_row_idx,      /* Argument(s). */
            input_col_idx
        );
    }

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

PYBIND11_MODULE(moduleH, m) {
    m.doc() = "pybind11 moduleH plugin";

    py::class_<Matrix, PyMatrix>(m, "Matrix")
        .def(py::init<int>(),
            py::arg("dimension"))
        .def("print_matrix", &Matrix::print_matrix, py::arg("mat"))
        .def("get_num_rows", &Matrix::get_num_rows)
        .def("get_num_columns", &Matrix::get_num_columns);

    py::class_<TridiagonalMatrix, Matrix>(m, "TridiagonalMatrix")
        .def(py::init<std::vector<double>, std::vector<double>, std::vector<double>>(),
            py::arg("a"), py::arg("b"), py::arg("c"))
        .def("operator()", &Matrix::operator(), py::arg("input_row_idx"), py::arg("input_col_idx"));
        
    py::class_<HeatDiffusion>(m, "HeatDiffusion")
        .def(py::init<int, double, const double, const double>(),
            py::arg("dimension"), py::arg("L"),
            py::arg("boundaryCondition1"), py::arg("boundaryCondition2"))
        .def("evaluate", &HeatDiffusion::evaluate, py::arg("y"), py::arg("parser"))
        .def("solveH", &HeatDiffusion::solveH, py::arg("function"))
        .def("validate_solution", &HeatDiffusion::validate_solution, py::arg("solution"), py::arg("exactSol"));
}