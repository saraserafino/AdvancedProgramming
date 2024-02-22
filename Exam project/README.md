# Gradient Descent
The instructions for this exam project can be found in this same folder. This project was further developed at home in order to better prepare for the subsequent session (since I refused the grade, not considering it good enough); however it is not complete since it lacks of correctness for the Quadratic Optimisation Problem.<br>
The second one, which allowed me to reach the highest grade, can be found in its own [repository on my GitHub page](https://github.com/saraserafino/ThomasAlgorithm-HeatDiffusionProblem) and its about [Thomas Algorithm for heat diffusion problem](https://github.com/pcafrica/advanced_programming_2023-2024/blob/main/exams/2024-02-13/part2.md).

## Code organization
For each module there is a folder which separates source files from header files; the main file is in its folder called main; a CMake and a setup.py are provided. Gradient Descent does not have a complete readme since it was not fully developed.

## CMake and libraries
A CMake for the creation of the modules is provided. Also a setup.py is provided, creating a Python package easily installable via pip.
Some Python packages were used: SciPy, tabulate. They can be installed with `pip install [names] --user`.<br>
SciPy is used for mathematical operations; tabulate to create a table of some results.

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
