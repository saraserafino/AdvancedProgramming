# Import the module created with pybind11
import moduleH

from tabulate import tabulate # for a cute table of results
import random # for epsilon
import time # for the wrapper execution_time
import numpy as np
from numpy.linalg import solve # for validating heat solution

# Decorator for computing the execution time
def execution_time(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        executionTime = time.time() - start
        return result, executionTime
    return wrapper

# Solve the heat diffusion problem usign the implementation in C++
@execution_time
def solveH_cpp(HDproblem, f):
    return HDproblem.solveH(f_cpp)

# Solve the heat diffusion problem using NumPy
@execution_time
def solveH_py(dimension, initialTemperature, boundaryCondition1, boundaryCondition2, f):
    # Define matrix A
    A = np.diag(- 2 * np.ones(dimension + 2)) + np.diag(np.ones(dimension + 1), 1) + np.diag(np.ones(dimension + 1), -1)
    # subdiagonal
    A[dimension, dimension - 2] = 0
    # diagonal
    A[0, 0] = 1
    A[-1, -1] = 1
    # superdiagonal
    A[0, 1] = 0

    # Calculate number of spatial steps
    h = initialTemperature / (dimension + 1)
    # Compute points of the domain
    x = np.arange(0, dimension + 2) * h

    # Construct right-hand side vector f
    f_vec = np.zeros(dimension + 2)
    f_vec[0] = boundaryCondition1
    f_vec[1:-1] = f(x[1:-1]) * h**2
    f_vec[-1] = boundaryCondition2

    # Solve the system using NumPy
    u = np.linalg.solve(A, f_vec)
    return u

def validate_solution_py(solution, exactSol):
    # Compute the difference between the two vectors
    difference = np.array(solution) - np.array(exactSol)
    # Compute the Euclidean norm = sqrt( (x_1)^2 + ... + (x_n)^2 )
    return np.sqrt(np.sum(difference**2))

# ----------------
# main
# ----------------

# Initial data of the heat diffusion problem
dimension = 4
initialTemperature = 1 # L = 1
boundaryCondition = 0 # both alpha and beta are 0

# Create instance of the heat diffusion problem
HDproblem = moduleH.HeatDiffusion(dimension, initialTemperature, boundaryCondition, boundaryCondition)

# Define the heat source term and the exact analytical solution
f_cpp = "-sin(pi*x)"
exactf_cpp = "(sin(pi*x))/(pi*pi)"
# Compute solution with C++
solution_cpp, timesol_cpp = solveH_cpp(HDproblem, f_cpp)
# Validate it against the exact solution
error_cpp = HDproblem.validate_solution(solution_cpp, exactf_cpp)
print(f"The solution is {solution_cpp}, the error is {error_cpp}.")


# Validate results against the solve function from numpy.linalg

# Define the heat source term and the exact analytical solution
def f_py(x):
    return -np.sin(np.pi * x)

def exactf_py(x):
    return np.sin(np.pi * x) / np.pi**2

# Compute solution with Python
solution_py, timesol_py = solveH_py(dimension, initialTemperature, boundaryCondition, boundaryCondition, f_py)

# Compute exact solution
# Calculate number of spatial steps for the domain (i.e. x)
h = initialTemperature / (dimension + 1)
# Evaluate the exact solution in each point of the domain (which is i*h equally spaced)
exact_solution = [exactf_py(i * h) for i in range(dimension + 2)]

# Validate the solution with Python with the exact one
error_py = validate_solution_py(solution_py, exact_solution)
print(f"The solution is {solution_py}, the error is {error_py}.")

# Prepare the results to be printed in a more uniform way with tabulate
header = ["", "Exact", "C++", "Python"]
data = [
        ["Solution", exact_solution, round(solution_cpp, 4), round(solution_py, 4)],
        ["Error against exact solution", None, round(error_cpp, 4), round(error_py, 4)],
        ["Execution time (s)", None, round(timesol_cpp, 4), round(timesol_py, 4)]
        ]
print(tabulate(data, header, tablefmt = "fancy_grid"))

# Plot the numerical and exact solutions vs x for visual comparison