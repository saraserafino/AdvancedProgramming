# Exam projects
The first one is [Gradient Descent](https://github.com/pcafrica/advanced_programming_2023-2024/blob/main/exams/2024-01-17/part2.md) and was almost finished in order to better prepare for the subsequent session (since I refused the grade, not considering it good enough); it lacks of correctness for the Quadratic Optimisation Problem.<br>
The second one is [Thomas Algorithm for the heat diffusion problem](https://github.com/pcafrica/advanced_programming_2023-2024/blob/main/exams/2024-02-13/part2.md); the installation of its module via pip is incomplete due to errors, the main.py was not even written. However I accepted the grade and didn't further develop it outside the exam.

## Code organization
For each module there is a folder which separates source files from header files; the main file is in its folder called main; a cmake and a setup.py are provided and will be explained later on. Since both project are incomplete, the main.py contains some functions that were not used, such as plotting functions.

## CMake and libraries
A CMake for the creation of the modules is provided. Also a setup.py is provided, creating a Python package easily installable via pip.
Some Python packages were used: NumPy, SciPy MatPlotLib, seaborn, pandas, tabulate. They can be installed with `pip install [names] --user`.<br>
NumPy and SciPy are used for mathematical operations; pandas for creating dataframes and reading a CSV file; matplotlib and seaborn for plotting; tabulate to create a table of some results.

## How to compile
A CMake and a setup.py are provided in the main directory. Setup.py implicitly calls CMake, thus everything is ready writing:
```bash
python setup.py install --user
```
Or even better just using pip
```bash
pip install --user .
```
Lastly, to compile the main:
```bash
python main/main.py
```
