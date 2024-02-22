# Import the module created with pybind11
import optimization

from scipy.optimize import minimize_scalar # for comparing problem 1
from scipy.stats import linregress # for comparing problem 2
from tabulate import tabulate # for a cute table of results
import random # for epsilon
import time # for the wrapper execution_time

# Decorator for computing the execution time
def execution_time(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result1, result2 = func(*args, **kwargs)
        executionTime = time.time() - start
        return result1, result2, executionTime
    return wrapper

# ----------------
# main
# ----------------

print("Problem 1 requires to minimize the scalar quadratic function f(x)=(x-1)^2 with learning rate 0.1")
exact_solution = 1
exact_function = (exact_solution - 1)**2

# Compute solution and the value of the function in that solution with C++
@execution_time
def QO_cpp():
    # Create instances of the quadratic optimisation problem and its gradient descent
    QOproblem = optimization.QuadraticOptimizationProblem(1) # dimension
    QOGradDesc = optimization.GradientDescentQuadraticOptimization(QOproblem)

    # Change the learning rate to the required one
    QOGradDesc.set_learningRateQuadraticOptimizationProblem(0.1)
    solution_cpp, constfunction_cpp = QOGradDesc.get_solutionsQuadraticOptimizationProblem()
    return solution_cpp, constfunction_cpp

# Results of C++
solution, constfunction_cpp, timeQO_cpp = QO_cpp()
solution_cpp = solution[0]

# Compute the error with respect to the exact solution
error_cpp = abs((solution_cpp - exact_solution))

# Validate and compare the results of Problem 1 against the minimize_scalar function of scipy.optimize
@execution_time
def QO_py():
    f = lambda x: (x - 1)**2 # define the function to minimize
    res = minimize_scalar(f)
    solution_py = res.x
    constfunction_py = res.fun
    return solution_py, constfunction_py

# Results of Python
solution_py, constfunction_py, timeQO_py = QO_py()

# Compute the error with respect to the exact solution
error_py = abs((solution_py - exact_solution))

# Prepare the results to be printed in a more uniform way with tabulate
header = ["", "Exact", "C++", "Python"]
data = [
        ["Solution", exact_solution, round(solution_cpp, 4), round(solution_py, 4)],
        ["Value of the function", round(exact_function, 4), round(constfunction_cpp, 4), round(constfunction_py, 4)],
        ["Error", None, round(error_cpp, 4), round(error_py, 4)],
        ["Execution time (s)", None, round(timeQO_cpp, 4), round(timeQO_py, 4)]
        ]
print(tabulate(data, header, tablefmt = "fancy_grid"))



print("Problem 2 requires to minimize the model y_hat = theta0 + theta1 * x with learning rate 0.01 or 0.001")

# Set number of random points x,y to be generated
num_points = 10
# Compute solution and the value of the function in that solution with C++

# Create instances of the quadratic optimisation problem and its gradient descent
LRproblem = optimization.LinearRegressionProblem(2, num_points) # dimension (i.e. number of theta)
LRGradDesc = optimization.GradientDescentLinearRegression(LRproblem)

# Change the learning rate to 0.01 if you don't want the standard 0.001
#LRGradDesc.set_learningRateLinearRegressionProblem(0.01)

# Compute the solution with C++
solution_cpp, constfunction_cpp = LRGradDesc.get_solutionsLinearRegressionProblem()
theta0 = solution_cpp[0]
theta1 = solution_cpp[1]
print(f"theta0 = {theta0}")
print(f"theta1 = {theta1}")
print(f"MSE cost function at the optimal value = {constfunction_cpp}")

# Validate and compare the results of Problem 2 against the linregress function of scipy.stats

# Generate x with random numbers from -50 to 50
x = [random.uniform(-50, 50) for _ in range(num_points)]
# Generate the noise and compute y
epsilon = random.normalvariate(0.0, 0.1)
y = [4 + (x_i/2.0) + epsilon for x_i in x]

# Compute the result with Python
slope, intercept, r_value, p_value, std_err = linregress(x, y)
print("Intercept i.e. theta0:", intercept)
print("Slope i.e. theta1:", slope)
constfunction_py = [intercept + slope * x_i for x_i in x]

# Plot the Python solution since it's the right one
#plt.plot(x, y, 'o', label = 'original data')
#plt.plot(x, constfunction_py, 'r', label = 'fitted line')
#plt.legend()
#plt.show()

# Plot the cost function vs. the Gradient Descent iterations
