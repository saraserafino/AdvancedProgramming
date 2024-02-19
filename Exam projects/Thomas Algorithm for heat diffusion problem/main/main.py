# Import the module created with pybind11
import moduleH

from tabulate import tabulate # for a cute table of results
import time # for the wrapper execution_time
import numpy as np
from numpy.linalg import solve # for validating heat solution
import matplotlib.pyplot as plt # for plot
import os

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
    return HDproblem.solveH(f)

# Solve the heat diffusion problem using NumPy
@execution_time
def solveH_py(dimension, L, boundaryCondition1, boundaryCondition2, f):
    # Define matrix A
    A = np.diag(- 2 * np.ones(dimension + 2)) + np.diag(np.ones(dimension + 1), 1) + np.diag(np.ones(dimension + 1), -1)
    # subdiagonal
    A[-1, -2] = 0
    # diagonal
    A[0, 0] = 1
    A[-1, -1] = 1
    # superdiagonal
    A[0, 1] = 0

    # Calculate number of spatial steps
    h = L / (dimension + 1)
    # Compute points of the domain
    x = np.arange(0, dimension + 2) * h

    # Construct right-hand side vector f
    f_vec = np.zeros(dimension + 2)
    f_vec[0] = boundaryCondition1
    f_vec[1:-1] = f(x[1:-1]) * h**2
    f_vec[-1] = boundaryCondition2

    # Solve the system using NumPy
    return np.linalg.solve(A, f_vec)

# Validate its solution against the exact solution
def validate_solution_py(solution, exactSol):
    # Compute the difference between the two vectors
    difference = np.array(solution) - np.array(exactSol)
    # Compute the Euclidean norm = sqrt( (x_1)^2 + ... + (x_n)^2 )
    return np.sqrt(np.sum(difference**2))

# Create a folder in which to store plot images
if not os.path.exists("images"):
    os.mkdir("images")

# ----------------
# main
# ----------------

# Initial data of the heat diffusion problem
dimension = 10
L = 1
boundaryCondition = 0 # both alpha and beta are 0

# Create instance of the heat diffusion problem
HDproblem = moduleH.HeatDiffusion(dimension + 2, L, boundaryCondition, boundaryCondition)

# Define the heat source term and the exact analytical solution (muParseX is used in the C++ code)
f_cpp = "-sin(pi*x)"
exactf_cpp = "(sin(pi*x))/(pi*pi)"

# Compute solution with C++
solution_cpp, timesol_cpp = solveH_cpp(HDproblem, f_cpp)
# Validate it against the exact solution
error_cpp = HDproblem.validate_solution(solution_cpp, exactf_cpp)
#print(f"Solution computed with C++: {solution_cpp}, error: {error_cpp}.")


# Validate results against the solve function from numpy.linalg

# Define the heat source term and the exact analytical solution
def f_py(x):
    return -np.sin(np.pi * x)

def exactf_py(x):
    return np.sin(np.pi * x) / np.pi**2

# Compute solution with Python
solution_py, timesol_py = solveH_py(dimension, L, boundaryCondition, boundaryCondition, f_py)

# Compute exact solution

# Calculate number of spatial steps for the domain (i.e. x)
h = L / (dimension + 1)

# Evaluate the exact solution in each point of the domain (which is i*h equally spaced)
exact_solution = [exactf_py(i * h) for i in range(dimension + 2)]
#print(f"The exact solution is {exact_solution}")

# Validate the solution of Python with the exact one
error_py = validate_solution_py(solution_py, exact_solution)
#print(f"Solution computed with Python: {solution_py}, error: {error_py}.")

# Prepare the results to be printed in a more uniform way with tabulate
header = ["", "Exact", "C++", "Python"]
data = [
        ["Solution[0]", exact_solution[0], solution_cpp[0], solution_py[0]],
        ["Solution[1]", exact_solution[1], solution_cpp[1], solution_py[1]],
        ["Solution[2]", exact_solution[2], solution_cpp[2], solution_py[2]],
        ["Solution[3]", exact_solution[3], solution_cpp[3], solution_py[3]],
        ["Solution[4]", exact_solution[4], solution_cpp[4], solution_py[4]],
        ["Solution[n]", round(exact_solution[-1], 3), solution_cpp[-1], solution_py[-1]],
        ["Error against exact solution", None, round(error_cpp, 5), round(error_py, 5)],
        ["Execution time (s)", None, round(timesol_cpp, 5), round(timesol_py, 5)]
        ]
print(f"Solution of the heat diffusion problem with heat source term {f_cpp} and exact solution {exactf_cpp}:")
print(tabulate(data, header, tablefmt = "fancy_grid"))


# Plot the numerical and exact solutions vs x for visual comparison

# Generate x values
x_values = [i * h for i in range(dimension + 2)]

# Plot exact solution
plt.plot(x_values, exact_solution, label = 'Exact Solution', color = 'blue')

# Plot solution computed with C++
plt.plot(x_values, solution_cpp, label = 'C++ Solution', linestyle = '--', marker = 'o', color = 'red')

# Plot solution computed with Python
plt.plot(x_values, solution_py, label = 'Python Solution', linestyle = ':', marker = 's', color = 'green')

plt.xlabel('x')
plt.ylabel('Temperature')
plt.title('Numerical Solutions VS Exact Solution')
plt.legend()
plt.grid(True)
# Save the plot
plt.savefig('images/NumericalVSExactSolution.png')
plt.show()