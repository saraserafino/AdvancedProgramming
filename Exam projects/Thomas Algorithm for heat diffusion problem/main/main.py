# Import the module created with pybind11
import moduleH

from tabulate import tabulate # for a cute table of results
import random # for epsilon
import time # for the wrapper execution_time

# Decorator for computing the execution time
def execution_time(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        executionTime = time.time() - start
        return result, executionTime
    return wrapper

# ----------------
# main
# ----------------

# Create instance of the heat diffusion problem with these given parameters
dimension = 4
initialTemperature = 1 # L = 1
boundaryCondition = 0 # both alpha and beta = 0
HDproblem = moduleH.HeatDiffusion(dimension, initialTemperature, boundaryCondition, boundaryCondition)

f = "-sin(pi*x)" # heat source term
exactf = "(sin(pi*x))/(pi*pi)" # exact analytical solution
solution_cpp = HDproblem.solveH(f)
error_cpp = HDproblem.validate_solution(f, exactf)
print(f"The solution is {solution_cpp}, the error is {error_cpp}.")

# Prepare the results to be printed in a more uniform way with tabulate
header = ["", "Exact", "C++", "Python"]
data = [
        ["Solution", exact_solution, round(solution_cpp, 4), round(solution_py, 4)],
        ["Value of the function", round(exact_function, 4), round(constfunction_cpp, 4), round(constfunction_py, 4)],
        ["Error", None, round(error_cpp, 4), round(error_py, 4)],
        ["Execution time (s)", None, round(timeQO_cpp, 4), round(timeQO_py, 4)]
        ]
print(tabulate(data, header, tablefmt = "fancy_grid"))