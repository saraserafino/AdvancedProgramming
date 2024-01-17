#include "../include/Optimisation.hpp"
#include <iostream>
#include <vector>

int main() {
    QuadraticOptimizationProblem quadraticProblem;
    GradientDescent quadraticSolver(quadraticProblem);
    quadraticSolver.setLearningRate(0.1);
    quadraticSolver.setMaxIterations(1000);
    quadraticSolver.setConvergenceThreshold(1e-6);

    try {
        std::vector<double> solution = quadraticSolver.solve();
        double finalCost = quadraticSolver.getFinalCost(solution);

        std::cout << "Quadratic Optimization Result:" << std::endl;
        std::cout << "Solution: [" << solution[0] << ", " << solution[1] << "]" << std::endl;
        std::cout << "Final Cost: " << finalCost << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}