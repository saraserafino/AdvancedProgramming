# Numerical Integration module
# Import the module created with pybind11
import moduleC

import numpy as np
import math
import scipy.integrate as integrate
from scipy.integrate import trapezoid, simpson, quad, fixed_quad
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import time # for the wrapper execution_time
import os
from tabulate import tabulate # for a cute table of results

# Decorator for computing the execution time
def execution_time(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        executionTime = time.time() - start
        return result, executionTime
    return wrapper

# Definitions of the integration methods both in C++ and in Python

# Neither in SciPy nor in NumPy there's a midpoint integration method, so just compute it as in C++
@execution_time
def Midpoint_cpp(function, trueValue, a, b, nBins):
    M = moduleC.Midpoint(a, b, nBins)
    integrationValue = moduleC.IntegrateMidpoint(function, M)
    error = abs(trueValue - integrationValue)
    return integrationValue, error

# Methods for computing the convergence order in C++ and in Python, decorated with execution time.
# They return the errors and the orders of convergence, so that a plot with Matplotlib can be made

@execution_time
def computeConvergenceOrderMidpoint_cpp(function, exactIntegral):
    errors, orders = moduleC.computeConvergenceOrderMidpoint(function, exactIntegral)
    return errors, orders

# Plot a nested barplot by method and language to compare execution times
def catplotCompare(results):
    # Create a dataframe for seaborn
    results_df = pd.DataFrame(results)
    # Use catplot by seaborn. The pairs are made based on the language (C++ or Python)
    g = sns.catplot(data = results_df, kind = 'bar', x = 'Method', y = 'ExecutionTime', hue = 'Language', height = 6, aspect = 1.5)
    g.set_axis_labels('', 'Execution Time (s)')
    g.legend.set_title('')
    # Save the plot
    plt.savefig('NumericalIntegrationModule/images/CatplotIntegrationMethods.png')
    plt.show()

# ----------------
# main of module C
# ----------------

# Create a folder in which to store plot images
if not os.path.exists("NumericalIntegrationModule/images"):
    os.mkdir("NumericalIntegrationModule/images")
# Create the output path for the results outside the loop, otherwise it gets cleaned every time
output_file_path = "NumericalIntegrationModule/results.txt"

# Check if the file already exists, if so, overwrite it
if os.path.exists(output_file_path):
    with open(output_file_path, 'w') as file:
        file.write('TITLE\n\n')

            # Create a dictionary for each of the results computed in the for-cycle. Lastly we'll compute their average
            methods = ['Midpoint', 'Trapezoidal', 'PyTrapezoidal', 'Simpson', 'PySimpson', 'Gauss-Legendre', 'PyGauss-Legendre']
            results = {method: {'avg_errors': [], 'avg_orders': [], 'avg_time': []} for method in methods}

# The execution time given by the decorator will be used to plot the speeds, thus the actual result must be written between []

# Neither in SciPy nor in NumPy there's a midpoint integration method, so just compute it as in C++
[errors_mid_cpp, orders_mid_cpp], time_mid_cpp = computeConvergenceOrderMidpoint_cpp("cos(x)", 1.0)

# Append each result
results['Midpoint']['avg_errors'].append(errors_mid_cpp)
results['Midpoint']['avg_orders'].append(orders_mid_cpp)
results['Midpoint']['avg_time'].append(time_mid_cpp)

            # Compute their averages
averages = {method: {'avg_errors': np.mean(results[method]['avg_errors'], axis = 0),
            'avg_orders': np.mean(results[method]['avg_orders'], axis = 0),
            'avg_time': np.mean(results[method]['avg_time'])} for method in methods}

            # Recreate the subintervals of the above results (2, 4, 8, 16, 32, 64, ..., 1024)
            subintervals = [int(math.pow(2, i)) for i in range(int(math.log2(2)), int(math.log2(1024)) + 1)]

            # Plot convergence for each compared method
            plt.plot(subintervals, averages['Midpoint']['avg_errors'], label = 'Midpoint Rule with C++', color = 'purple')
            plt.plot(subintervals, averages['Trapezoidal']['avg_errors'], label = 'Trapezoidal Rule with C++', color = 'aquamarine')
            plt.plot(subintervals, averages['PyTrapezoidal']['avg_errors'], label = 'Trapezoidal Rule with Python', color = 'orchid')
            plt.plot(subintervals, averages['Simpson']['avg_errors'], label = 'Simpson\'s Rule with C++', color = 'orange')
            plt.plot(subintervals, averages['PySimpson']['avg_errors'], label = 'Simpson\'s Rule with Python', color = 'mediumseagreen')
            plt.plot(subintervals, averages['Gauss-Legendre']['avg_errors'], label = 'Gauss-Legendre Quadrature with a mixture', color = 'red')
            plt.plot(subintervals, averages['PyGauss-Legendre']['avg_errors'], label = 'Gauss-Legendre Quadrature with Python', color = 'fuchsia')
            # Use logarithmic scale for a better visibility
            plt.xscale('log')
            plt.yscale('log')
            # Name the axis, give a title and show the legend
            plt.xlabel('Subintervals')
            plt.ylabel('Error')
            plt.title('Average Convergence Order of Numerical Integration Methods')
            plt.legend()
            # Show a grid and the actual plot
            plt.grid(True)
            input("\nPress enter to visualize a plot of the convergence order for each compared method.")
            # Save the plot
            plt.savefig('NumericalIntegrationModule/images/AverageConvergenceOrder.png')
            plt.show()

            # Plot execution times for each compared method
            ExecutionTimes = {averages[method]['avg_time'] for method in methods}
            plt.bar(methods, ExecutionTimes, color = ['purple', 'aquamarine', 'orchid', 'orange', 'mediumseagreen', 'red', 'fuchsia'])
            plt.xlabel('Integration Method')
            plt.ylabel('Execution Time (s)')
            plt.title('Average Execution Time of Numerical Integration Methods')
            # Rotate x-axis labels for better readability
            plt.xticks(rotation = 45, ha = 'right')
            # Annotate each bar with its execution time
            for idx, times in enumerate(ExecutionTimes):
                plt.text(idx, times, f'{times:.4f}', ha = 'center', va = 'bottom')
            input("\nPress enter to visualize a plot of the execution times for each compared method.")
            # Save the plot
            plt.savefig('NumericalIntegrationModule/images/AverageExecutionTime.png')
            plt.show()

            # Prepare the results to be printed
            # Convert sets to lists
            averageErrors = {method : averages[method]['avg_errors'] for method in methods}
            averageOrders = {method : averages[method]['avg_orders'] for method in methods}
            averageTimes = {method : averages[method]['avg_time'] for method in methods}
            result = ''
            for method in methods:
                result += f"Average Convergence for {method}:\n"
                for i, subint in enumerate(subintervals):
                    result += f"  Subintervals: {subint:4d}  Error: {averageErrors[method][i]:.6e}  Order: {averageOrders[method][i]:.2f}\n"
                result += f"\nExecuted in {averageTimes[method]:.4f} s.\n\n\n"
            

            # Prepare the results to be printed in a more uniform way with tabulate
            header = ["", "C++", "Python"]
            data_trap = [
                    ["Result", res_trap_cpp, res_trap_py],
                    ["Error", err_trap_cpp, err_trap_py],
                    ["Absolute relative error (%)", abserr_trap_cpp, abserr_trap_py],
                    ["Execution time (s)", time_trap_cpp, time_trap_py]
                ]
            result += tabulate(data_trap, header, tablefmt = "fancy_grid")

    # Open the output file in append mode (so it doesn't overwrite)
    with open(output_file_path, 'a') as file:
        file.write(description + result + '\n\n')

    print(f"{description}Analysis completed:\n{result}")
    continueChoice = input("Do you want to perform another analysis? (1 for Yes): ")

print(f"All analyses completed. Results written to {output_file_path}")