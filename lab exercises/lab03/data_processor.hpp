#ifndef DATA_PROCESSOR_HPP__
#define DATA_PROCESSOR_HPP__

#include <algorithm> // to use min_element and max_element
#include <cassert> // to use assert
#include <numeric> // to use accumulate
#include <ostream> // to use ostream

class DataProcessor {
public:
  // Constructor
  DataProcessor(const double *input_data, const unsigned int &input_size);

  // Copy constructor
  DataProcessor(const DataProcessor &other);

  // Copy assignment operator
  DataProcessor &operator=(const DataProcessor &other);

  // Destructor. It is fully written in the .hpp and
  // not mentioned in the .cpp
  ~DataProcessor() {
    --n_instances;
    delete[] data;
    data = nullptr;
  }

  // Sum operator
  DataProcessor operator+(const DataProcessor &other) const;

  // Write access operator
  double &operator[](const unsigned int &index) {
    assert(index >= 0 && index < size);
    return data[index];
  }

  // Read access operator.
  const double &operator[](const unsigned int &index) const {
    assert(index >= 0 && index < size);
    return data[index];
  }

  unsigned int n_elements() const { return size; }

  double min() const { return *std::min_element(data, data + size); };
  // returns the smallest element in range [data, data + size)
  double max() const { return *std::max_element(data, data + size); };
  // returns the largest element in range [data, data + size)
  double compute_mean() const {
    const double sum = std::accumulate(data, data + size, 0.0);
    // accumulate values in range [data, data + size) giving
    // as initial value for the accumulator 0.0
    return sum / size;
  }

  double compute_std_dev() const;

  static unsigned int get_n_instances() { return n_instances; }
//a friend function can access private and protected data of a class
  friend std::ostream &operator<<(std::ostream &os, const DataProcessor &dp);
//std::ostream is needed because you may don't want to overload
//the operator << for all individual stream types, but only for
//the common base class of them which has the << functionality
private:
  static unsigned int n_instances;
  unsigned int size;
  double *data;
};

double compute_correlation(const DataProcessor &dp1, const DataProcessor &dp2);

#endif /* DATA_PROCESSOR_HPP__ */
