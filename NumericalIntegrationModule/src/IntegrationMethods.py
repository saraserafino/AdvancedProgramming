from numpy.polynomial import legendre
import numpy as np

# ----------------
# Python interface
# ----------------

class Quadrature:
    def __init__(self, a, b, nBins):
        self.weights = [0.0] * (nBins + 1)
        self.nodes = [0.0] * (nBins + 1)
        self.a = a
        self.b = b
        self.nBins = nBins

# When defining a custom constructor in a derived Python class,
# you must explicitly call the bound C++ constructor using __init__

class Midpoint(Quadrature):
    def __init__(self, a, b, nBins):
        Quadrature.__init__(self) # Without this, a TypeError is raised

# This is when changing something
# GaussLegendre is better implemented with NumPy
class GaussLegendre(Quadrature):
    def __init__(self, a, b, nBins):
        Quadrature.__init__(self)
        # Call numpy.polynomial.legendre.leggauss
        self.nodes,self.weights = np.polynomial.leggauss(nBins - 1)