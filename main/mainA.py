# Import the module created with pybind11
import optimization

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
        result = func(*args, **kwargs)
        executionTime = time.time() - start
        return result, executionTime
    return wrapper

# Definitions of the statistics methods both in C++ and in Python

@execution_time
def test_calculateMean_cpp(StatOpInstance, data):
    return StatOpInstance.calculateMean(data)

@execution_time
def test_calculateMean_py(data):
    # If there's even a string
    if any(isinstance(value, str) for value in data):
        raise TypeError("Cannot calculate mean for a string.")
    # Otherwise compute it with NumPy
    return np.mean(data)

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
    
QuadraticOptimizationProblem = optimization.QuadraticOptimizationProblem
LinearRegressionProblem = optimization.LinearRegressionProblem
quadraticSolver.setLearningRate(0.1)
quadraticSolver.setMaxIterations(1000)
quadraticSolver.setConvergenceThreshold(1e-6)
