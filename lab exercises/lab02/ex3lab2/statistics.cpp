#include "statistics.hpp"
#include <algorithm> // we need it for sort
#include <cmath> // we need it for sqrt

namespace stat {
// Function to calculate the mean of a set of numbers.
double calculate_mean(const std::vector<double> &numbers) {
  double sum = 0.0;
  for (const double &num : numbers) {
    sum += num; // aka sum=sum+num
  }
  return sum / numbers.size();
}

// Function to calculate the median of a set of numbers
double calculate_median(const std::vector<double> &numbers) {
  std::vector<double> sorted_numbers = numbers;
  // std::vector encapsulates dynamic size arrays
  std::sort(sorted_numbers.begin(), sorted_numbers.end());
  // std::sort sorts the elements in the range (first,last)
  size_t size = sorted_numbers.size();
  // size_t stores the maximum size of the object "size"
  if (size % 2 == 0) {
    // If the number of elements is even, average the middle two numbers.
    size_t mid = size / 2;
    return (sorted_numbers[mid - 1] + sorted_numbers[mid]) / 2.0;
  } else {
    // If the number of elements is odd, return the middle number.
    return sorted_numbers[size / 2];
  }
}

// Function to calculate the standard deviation of a set of numbers.
double calculate_standard_deviation(const std::vector<double> &numbers) {
  double mean = calculate_mean(numbers);
  double variance = 0.0;
  for (const double &num : numbers) {
    variance += (num - mean) * (num - mean);
  }
  return std::sqrt(variance / numbers.size());
}
} // closing namespace stat