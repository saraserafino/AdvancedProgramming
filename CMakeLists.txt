cmake_minimum_required(VERSION 3.12)

project(project VERSION 1.0
    DESCRIPTION "exam_project_Serafino"
    )

add_compile_options(-std=c++17)

# Search for Boost
find_package(Boost 1.83 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Search for muparserx
find_package(muparserx 4.0 REQUIRED)
include_directories(${muparserx_INCLUDE_DIRS})

# Search for Pybind
find_package(pybind11 REQUIRED)
include_directories(SYSTEM ${pybind11_INCLUDE_DIRS})

# Add the Python modules
pybind11_add_module(optimization
OptimisationModule/src/Optimisation.cpp
OptimisationModule/include/Optimisation.hpp
OptimisationModule/src/Optimisation_py.cpp
    )

target_link_libraries(optimization PRIVATE ${MUPARSERX_LIBRARY})
target_include_directories(optimization PRIVATE OptimisationModule/include)
#endif()