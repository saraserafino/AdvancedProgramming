#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

template <typename Container>
void print(const std::string &string, const Container &cont) {
  std::cout << string << ":" << std::endl;
  for (const auto &v : cont) {
    std::cout << v << " ";
  }
  std::cout << std::endl << std::endl;
}

int main() {
  // Initialize random number generator.
  std::default_random_engine gen(42);
  std::uniform_int_distribution<unsigned int> distribution(0, 9);

  // Generate vector of 100 random integers between 0 and 9.
  std::vector<unsigned int> random_numbers(100);
  for (unsigned int &num : random_numbers) {
    num = distribution(gen);
  }
  print("Original vector", random_numbers);

  // Or you could have doeìne it in this other way
  /*
  std::vector<int> random_numbers;
  random_numbers.reserve(100); // capacity = 100, size = 0
  for (size_t i = 0; i < random_numbers.capacity(); ++i)
    random_numbers.push_back(distribution(gen));
  */

  // or in this other way
  /*
  std::vector<int> random_numbers;
  for (size_t i = 0; i < random_numbers.size(); ++i)
    random_numbers[i] = distribution(gen);
  */
  
  // Sort the vector.
  std::vector<unsigned int> sorted_numbers(random_numbers);
  std::sort(sorted_numbers.begin(), sorted_numbers.end());
  print("Sorted numbers", sorted_numbers);

  // Remove duplicates while sorting.
  std::vector<unsigned int> sorted_unique_numbers(random_numbers);
  std::sort(sorted_unique_numbers.begin(), sorted_unique_numbers.end());
  auto unique_end =
      std::unique(sorted_unique_numbers.begin(), sorted_unique_numbers.end());
  sorted_unique_numbers.erase(unique_end, sorted_unique_numbers.end());
  print("Sorted unique numbers", sorted_unique_numbers);

  // Remove duplicates without sorting.
  std::vector<unsigned int> unsorted_unique_numbers;
  std::unordered_set<unsigned int> unique_numbers(random_numbers.begin(),
                                                  random_numbers.end());

  for (const unsigned int &element : random_numbers) {
    if (unique_numbers.find(element) != unique_numbers.end()) {
      unique_numbers.erase(element);
      unsorted_unique_numbers.push_back(element);
    }
  }
  // or it could have been done in this way
  /*
  for (auto v : random_numbers) {
    if (unique_numbers.count(v)) {
      unsorted_unique_numbers.push_back(v);
      unique_numbers.erase(v);
    }
  }
  */
  print("Unsorted unique numbers", unsorted_unique_numbers);
  return 0;
}