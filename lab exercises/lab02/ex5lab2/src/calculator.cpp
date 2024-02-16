#include "calculator.hpp"
#include <iostream>
namespace Calculator {
double add(const double &a, const double &b) { return a + b; }
double subtract(const double &a, const double &b) { return a - b; }
double multiply(const double &a, const double &b) { return a * b; }
double divide(const double &a, const double &b) {
  if (b == 0) {
    std::cerr << "Division by zero is not allowed." << std::endl;
    // cerr stands for character error stream
    std::exit(1); // terminates immediately the whole program execution
    // while return would have returned only from this current function
  }
  return a / b;
}
} // namespace Calculator