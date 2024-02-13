# part2_Serafino_Sara_SM3400292

Il readme non è stato modificato, è ancora il prototipo. Setup.py e cmake funzionano, il problema è che avevo errori con pybind

## Code organization
For each module there is a folder which separates source files from header files; the main file is in its folder called main; a cmake and a setup.py are provided and will be explained later on. When executing the main, a text file with the results and a folder `images` containing the plots is created.

## Main
The `main.cpp` 

## Statistics module
`DataHandler_py.cpp` provides a Python interface and binding with Pybind11, creating a module called moduleA.
Before showing every plot, the user is asked to press enter, in this way they don't get suddenly overwhelmed by datas and plots.

### Analysis and observations

  <p align="center">
  <img src="StatisticsModule/images/CatplotAge.png" /><br>
  title
</p>

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