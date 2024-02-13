cmake_minimum_required(VERSION 3.12)

project(project VERSION 1.0
    DESCRIPTION "exam_project_Serafino"
    )

add_compile_options(-std=c++17)

# Search for Boost
#find_package(Boost 1.83 REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

# Search for Pybind
find_package(pybind11 REQUIRED)
include_directories(SYSTEM ${pybind11_INCLUDE_DIRS})

# Add the Python modules
pybind11_add_module(matrix
    OptimisationModule/src/Matrix.cpp
    OptimisationModule/src/Matrix_py.cpp
    )

target_include_directories(matrix PRIVATE MatrixModule/include)