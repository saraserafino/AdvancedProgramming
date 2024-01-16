# Statistics module

# Import the module created with pybind11
import moduleA

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
# main of module A
# ----------------

# Create an instance for CSVHandler and StatOp in order to use their methods
csvFile = moduleA.CSVHandler("data/player_data_03_22.csv")
StatOpInstance = moduleA.StatOp(csvFile)

# Read data from CSV file using pandas
df = pd.read_csv('data/player_data_03_22.csv', delimiter=',')
# Store the header i.e. the names of the columns
header = df.columns

# Create a folder in which to store plot images
if not os.path.exists("StatisticsModule/images"):
    os.mkdir("StatisticsModule/images")

print("Some statistics about the age of the players:\n")
# Save the datas in order to compute df['name of the column'] just once
Age = df['Age']

# Compute the statistics to compare between C++ and Python
print("Mean of Age:")
res_mean_cpp, time_mean_cpp = test_calculateMean_cpp(StatOpInstance, Age)
res_mean_cpp = float(res_mean_cpp) # same type needed for computing the absolute value
res_mean_py, time_mean_py = test_calculateMean_py(Age)
delta_mean_age = abs(res_mean_cpp - res_mean_py)
if delta_mean_age < math.pow(10,-4):
    print(f"Both C++ and Python have result: {res_mean_py:.4f}")
else:
    print(f"C++ result: {res_mean_cpp:.4f} \nPython result: {res_mean_py:.4f}\n")   
print(f"C++ execution time: {time_mean_cpp:.4f} s, Python: {time_mean_py:.4f} s.\n")

# Create a list with the deltas between the statistics of C++ and Python
# For the frequency it's not computed because it would make no sense
deltas_age = [delta_mean_age, delta_sd_age]
# Create the base for a DataFrame with the results
resultsAge = {
                'Language': ['C++', 'Python', 'C++', 'Python', 'C++', 'Python'],
                'Operation': ['Mean', 'Mean', 'StandardDeviation', 'StandardDeviation', 'Frequency', 'Frequency'],
                'Result': [res_mean_cpp, res_mean_py, res_sd_cpp, res_sd_py, res_f_cpp, res_f_py],
                'ExecutionTime': [time_mean_cpp, time_mean_py, time_sd_cpp, time_sd_py, time_f_cpp, time_f_py]
            }

input("\nPress enter to visualize a catplot to compare execution times and deltas between the statistics of C++ and Python (deltas are written over the bars) for Age.")
# With this input you don't get suddenly overwhelmed by datas and plots
catplotCompare(resultsAge, deltas_age, 'Age')

input("\nPress enter to visualize a bar plot of its frequency count.")
barplotFrequency(res_f_py, 'Age')

# Print the header so the user can see the options
print(f"\nThe names of the columns are {header[1:]}")
# Without [1:], it prints '0' as first value because the column 0 is the enumeration of rows

# Create the output path outside the loop, otherwise it gets cleaned every time
output_file_path = "StatisticsModule/results.txt"
# Check if the file already exists, if so, overwrite it
if os.path.exists(output_file_path):
    with open(output_file_path, 'w') as file:
        file.write('TITLE\n\n')


    # Open the output file in append mode (so it doesn't overwrite)
    with open(output_file_path, 'a') as file:
        file.write(description + result + timeExecution + '\n')

    print(f"Analysis completed:\n{result}{timeExecution}")
    continueChoice = input("\nDo you want to perform another analysis? (1 for Yes): ")

print(f"All analyses completed. Results written to {output_file_path}")