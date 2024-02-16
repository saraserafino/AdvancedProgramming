# Import the module created with pybind11
import optimization

from scipy.optimize import minimize_scalar # for comparing problem 1
from scipy.stats import linregress # for comparing problem 2
from tabulate import tabulate # for a cute table of results
import random # for epsilon

import numpy as np
import math
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import time # for the wrapper execution_time
import os
from typing import List, Optional, Union

# Decorator for computing the execution time
def execution_time(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result1, result2 = func(*args, **kwargs)
        executionTime = time.time() - start
        return result1, result2, executionTime
    return wrapper

# Plot the frequency with a bar plot
def barplotFrequency(frequency, name):
    # Create a DataFrame for Seaborn
    df_sns = pd.DataFrame({'Values': frequency.index, 'Counts': frequency.values})
    # Sort the DataFrame by 'Values' in ascending order
    df_sns = df_sns.sort_values(by = 'Values')
    
    # Use Seaborn to create a bar plot with rainbow colors
    plt.figure(figsize=(10, 6))
    sns.barplot(x = 'Values', y = 'Counts', hue = 'Values', data = df_sns, palette = 'rainbow', legend = False)
    plt.xlabel(name)
    plt.ylabel('Frequency counts')
    plt.title(f'Frequency counts of {name}')
    # Rotate x-axis labels for better readability in case some values are longer
    plt.xticks(rotation = 45, ha = 'right')

    # Annotate each bar with its count
    for idx, count in enumerate(df_sns['Counts']):
        plt.text(idx, count, f'{count}', ha = 'center', va = 'bottom')
    # Save the plot
    filename = 'StatisticsModule/images/Frequency' + name
    plt.savefig(filename)
    plt.show()

# Plot the distribution of the frequency with a pie chart
def pieplotFrequency(frequency, name):
    # Use Seaborn to create a pie chart with pastel colors
    plt.figure(figsize = (8, 8))  # make it bigger
    sns.set_palette('pastel')
    plt.title(f'Distribution of {name} frequency counts')
    plt.pie(frequency, labels = frequency.index, autopct = '%1.1f%%', startangle = 90)
    # Save the plot
    filename = 'StatisticsModule/images/FrequencyDistribution' + name
    plt.savefig(filename)
    plt.show()

# Plot a nested barplot by operation and language to compare execution times and deltas between the statistics of C++ and Python
def catplotCompare(results, deltas, name):
    # Create a dataframe for seaborn
    results_df = pd.DataFrame(results)
    # Use catplot by seaborn. The pairs are made based on the language (C++ or Python)
    g = sns.catplot(data = results_df, kind = 'bar', x = 'Operation', y = 'ExecutionTime', hue = 'Language', height = 6, aspect = 1.5)
    g.set_axis_labels('', 'Execution Time (s)')
    g.legend.set_title('')
    # Annotate each couple of bars with the deltas between the statistics of C++ and Python (if present)
    for idx, err in enumerate(deltas):
        plt.text(idx, err, f'{err}', ha = 'center', va = 'bottom', fontsize = 'medium', weight = 'bold')
    # Save the plot
    filename = 'StatisticsModule/images/Catplot' + name
    plt.savefig(filename)
    plt.show()


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