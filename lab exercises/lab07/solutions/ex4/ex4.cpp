#include <dlfcn.h> // dynamic library
#include <iostream>
#include <string>
/*
void check_error(int error_code) {
  auto error = dlerror();
  if (error != nullptr) {
    std::cerr << "Error: " << error << std::endl;
    std::exit(error_code);
  }
}
*/
int main() {
    // Load libfunctions.so.
  void *handle = dlopen("./libfunctions.so", RTLD_LAZY);
  // RTLD_LAZY does it at runtime
  char* error = dlerror();
  if (error != nullptr)
    std::cerr << error << std::endl;

  // Prompt the user for the function to evaluate.
  std::string answer;
  std::cout << "cube, square or square_root: ";
  std::cin >> answer;

  // Load the proper symbol from libfunctions.so
  auto fun = reinterpret_cast<double (*)(const double &)>(
      dlsym(lib_handle, answer.c_str()));
  // .c:str() converts a string into an array of characters
  // dlsym returns a pointer to void
  // reinterpret_cast interprets it as a function pointer
  
  char* error = dlerror();
  if (error != nullptr)
    std::cerr << error << std::endl;

  // Prompt the user for the value to evaluate the function at.
  double value;
  std::cout << "x = ";
  std::cin >> value;

  // Evaluate function and print result.
  const double result = fun(value);
  std::cout << answer << "(" << value << ") = " << result << std::endl;

  // Close libfunctions.so.
  dlclose(lib_handle);

  return 0;
}
