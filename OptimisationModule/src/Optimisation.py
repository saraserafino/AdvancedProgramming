# ----------------
# Python interface
# ----------------

class OptimizationProblem:
    def __init__(self, theta):
        self.theta = theta

# When defining a custom constructor in a derived Python class,
# you must explicitly call the bound C++ constructor using __init__

class QuadraticOptimizationProblem(OptimizationProblem):
    def __init__(self):
        OptimizationProblem.__init__(self) # Without this, a TypeError is raised

class QuadraticOptimizationProblem(OptimizationProblem):
    def __init__(self):
        OptimizationProblem.__init__(self)

class GradientDescent:
    def __init__(self, problem):
        self.problem = problem