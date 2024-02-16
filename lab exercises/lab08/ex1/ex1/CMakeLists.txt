cmake_minimum_required(VERSION 3.12)

project(example_muparser VERSION 1.0
    DESCRIPTION "some project description"
    LANGUAGES CXX)

set(MUPARSERX_ROOT "" CACHE STRING "Path to muparserx installation.")

add_executable(ex_mup ex1.cpp)
# first target name, then source files to compile for generating the executable target
target_include_directories(ex_mup
    PRIVATE
    ${MUPARSERX_ROOT}/include)

target_link_directories(ex_mup
    PRIVATE
    ${MUPARSERX_ROOT}/lib) # like writing -L/opt/muparserx/lib

target_link_libraries(ex_mup muparserx) # like writing -lmuparserx