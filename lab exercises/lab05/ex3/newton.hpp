#ifndef NEWTON_HPP__
#define NEWTON_HPP__

#include <functional> // for using function
// T is whichever type of function
template <typename T> class NewtonSolver {
public:
  NewtonSolver(const std::function<T(const T &)> &f,
               const std::function<T(const T &)> &df, const T &x0,
               const double &tolerance = 1e-12,
               const unsigned int &max_iterations = 100);

  T solve();

private:
  // f is the function we're searching the root of
  const std::function<T(const T &)> f;
  // its derivative
  const std::function<T(const T &)> df;
  const T x0; // initial value
  const double tolerance;
  const unsigned int max_iterations;
};

#endif
