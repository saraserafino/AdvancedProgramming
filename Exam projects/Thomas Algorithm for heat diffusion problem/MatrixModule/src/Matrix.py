# ----------------
# Python interface
# ----------------

class Matrix:
    def __init__(self, dimension):
        self.dimension = dimension

# When defining a custom constructor in a derived Python class,
# you must explicitly call the bound C++ constructor using __init__

class TridiagonalMatrix(Matrix):
    def __init__(self, a, b, c):
        Matrix.__init__(self) # Without this, a TypeError is raised
        self.a = a
        self.b = b
        self.c = c

class HeatDiffusion:
    def __init__(self, dimension, initialTemperature, boundaryCondition1, boundaryCondition2):
        self.dimension = dimension
        self.initialTemperature = initialTemperature
        self.boundaryCondition1 = boundaryCondition1
        self.boundaryCondition2 = boundaryCondition2