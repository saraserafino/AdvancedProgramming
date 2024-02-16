# Part 1 simulation 1: Open-ended questions

## Question 1
What is a preprocessor and what is it used for?<br>
Given a C++ source file `code.cpp`, which shell command can be used to export the output of the preprocessor to a file `code_preprocessed.cpp`?

## Answer
A preprocessor is a program or set of directives which is part of the build process and performs preliminary operations on the source code before passing it to the compiler. It has the role of handling directives (like including header files with `#include`, conditional compilation `#ifdef #ifndef #else #endif`, compiler-specific directives `#pragma`) and macros (defining them with `#define`). It's used for code reusability and organization.<br>
The shell command to export the output of the preprocessor is:
```bash
g++ code.cpp -o code_preprocessed.cpp
```

---

## Question 2
Describe what is meant by *undefined behavior* in C++.<br>
Give examples of common programming mistake in C++ that can lead to undefined behavior.

## Answer
It means that there is a situation for which the language doesn't prescribe a specific outcome, generating any result.<br>
Some examples can be:
```cpp
// Trying to access memory beyond the allocated one
std::vector<int> v;
v.resize(2, 5);
std::cout << v[6];

// Using uninitialized variables
int x;
int y = x + 2;

// Modifying a const object
const int pi = 3.1415926;
pi = 3.14

// Type mismatch
int x = 5;
std::string saluto = "ciao";
double sum = x + saluto;
```

---

## Question 3
Compare and contrast `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.<br>
When should each be used? Provide some prototypical examples of use.

## Answer
Smart pointers control the lifespan of the resource they point to. `std::unique_ptr` means that the owned resource gets destroyed when the pointer goes out of scope; while for `std::shared_ptr` it happens when the last pointer owning that resource is destroyed. In fact in this last one, you have several objects that refer to the same resource. `std::weak_ptr` is a non-owning (thus weak) pointer to a shared resource; to access the referenced object it must be converted to a shared pointer; it's used to safely observe the shared object without affecting the ownership.<br>
An example of the use of `std::unique_ptr` is:
```cpp
class Polygon {};
class Triangle : public Polygon {};
class Square : public Polygon {};

int main () {
  std::unique_ptr<Polygon> polygon;
  std::string t;
  std::cin >> t;
  switch (t[0]) {
    case "T": // as in Triangle
      polygon = std::make_unique<Triangle>(...);
      break;
    case "S": // as in Square
      polygon = std::make_unique<Square>(...);
      break;
  }
  // Create another unique_ptr for swapping
  std::unique_ptr<Polygon> polygon2 = std::make_unique<Triangle>();
  // You can swap ownership
  std::swap(polygon, polygon2);
return 0;
}
```

An example of use of `std::shared_ptr` is (part of my StatisticsModule of Homework2):
```cpp
class CSVHandler {
public:
  // Declare StatOp as a friend class of CSVHandler in order to access its private members
  friend class StatOp;
protected:
  // Shared pointer between the two classes
  const std::shared_ptr<CSVHandler> CSVfile;
}

class StatOp {
public:
    // Constructor
    StatOp(const std::shared_ptr<CSVHandler> CSVfile);
}

int main () {
    // Create shared pointer
    const std::shared_ptr<CSVHandler> CSVfile = std::make_shared<CSVHandler>(input_file_path);
    return 0;
}
```

An example of use of `std::weak_ptr` is:
```cpp
std::shared_ptr<int> sptr = std::make_shared<int>(5);
std::weak_ptr<int> weak = sptr; // Get pointer to new data without taking ownership
if (sptr = weak.lock()) {
  // Use the locked sptr to access the shared data
} else { 
  // The shared data is out of scope
}
```

---

## Question 4
What's the difference between *Aggregation* and *Inheritance* in object-oriented programming?<br>
Provide some conceptual example for each of the two types of relationship.

## Answer
Aggregation is a "has-a" relationship where one class contains the other as a part, but the contained object can exist independently; while inheritance is a "is-a" relationship where the derived class inherits properties and behaviours from the base class, therefore it can't exist without the base class and it's stronger.<br>
An example of aggregation is the University class that may aggregate Department classes:
```cpp
class Department {
public:
  Department(std::string name) : name(name) {}
private:
  std::string name;
};
class University {
public:
  void addDepartment(const Department& department) {
    departments.push_back(department);
  }
private:
  std::vector<Department> departments;
};
```
An example of inheritance is (part of my Homework1):
```cpp
class SparseMatrix { // abstract class
public:
    // Constructor
    SparseMatrix(std::vector<double>& values, std::vector<unsigned int>& columns);

    // Define the common method of COO and CSR as virtual
    virtual unsigned int get_num_rows() const = 0;
protected:
// the vector values contains all the nonzero values
std::vector<double> values;
// the vector columns contains their corresponding columns indices
std::vector<unsigned int> columns;
};

class SparseMatrixCOO : public SparseMatrix {
public:
    // Constructor
    SparseMatrixCOO(std::vector<double>& values, std::vector<unsigned int>& rows, std::vector<unsigned int>& columns);
    
    // Overriding the pure virtual method
    unsigned int get_num_rows() const override;

private:
// the vector rows contains the row indices
std::vector<unsigned int> rows;
};

class SparseMatrixCSR : public SparseMatrix {
public:
   // Constructor
   SparseMatrixCSR(std::vector<double>& values, std::vector<unsigned int>& row_idx, std::vector<unsigned int>& columns);
   
   unsigned int get_num_rows() const override;

private:
// the vector row_idx contains the cumulative number of nonzero entries up to the i-th row excluded
std::vector<unsigned int> row_idx;
};
```

---

## Question 5
Explain the concept of dynamic memory management in C++.<br>
Discuss the differences between `new`/`delete` and `malloc`/`free`. Which scenarios are appropriate for each?

## Answer
It's the allocation and deallocation of memory at runtime using pointers. It's more flexible than static memory allocation (i.e. at compile time) because the program can adapt to varying data sizes and structures during execution.<br>
`new`/`delete` is type safe, while `malloc`/`free` is not and it doesn't even invoke constructors and destructors. The first automatically determines the size, while the second requires that information. For this reason `malloc`/`free` is more appropriate when dealing with simple memory allocations where constructors are not invoked. When it isn't so, it's better to use `new`/`delete`, or even better smart pointers.


---

## Question 6
What are lambda functions in C++ and Python?<br>
How do they differ between the two languages and how are they used?

## Answer
Lambda functions are similar to the MatLab anonymous functions and they are used to create short inlined functions quickly, thus only when the function takes up one line (for Python) or a few (for C++) of code.
In both languages we don't need to specify the return type, with the difference that in Python we don't write anything, while in C++ we write `auto` before the definition and we can also specify with `->` (example later).
In Python they are created with the keyword lambda, for example `add_one = lambda x: x + 1`.
In C++ the square brackets are used to capture specification, which allows to use variables in the enclosing scope inside the lambda either by value or by reference. For example, for doing the same thing done with Python, we can write:
```cpp
auto f = [] (double x) { return x + 1; };
```
Which can be also specified with
```cpp
auto f = [] (double x) -> double { return x + 1; };
```
If we want to capture all the variables by making a copy we can write:
```cpp
auto g = [=] (float x, float y) { return x * y; };
```
And so on with other symbols inside [].


---

## Question 7
What are the advantages of using NumPy arrays over standard Python lists for scientific computing?<br>
Demonstrate with an example how to perform element-wise operations on NumPy arrays.

## Answer
NumPy arrays offer an efficient way to store and manipulate numerical data, offering advantages over the traditional Python lists in terms of less memory, more speed and convenience. It also provides support for multidimensional arrays, allowing an easy representation of matrices.
An element-wise multiplication between two random matrices 3x3, can be simply done with:
```python
import numpy as np
A = np.random.randint(1, 11, size=(3,3))
B = np.random.randint(1, 11, size=(3,3))
multiplication = A * B
```

---

## Question 8
Discuss the capabilities of the Matplotlib library in Python.<br>
Provide an example of how to create a line plot and a scatter plot using Matplotlib.

## Answer
Matplotlib is a library for data visualization that offers a wide range of plotting tools with various types of plots like scatter plots, bar plots, histograms; it provides a high-level interface for drawing attractive statistical graphics.<br>
A line plot can be:
```python
import matplotlib.pyplot as plt
import numpy as np
x_values = np.linspace(0, 10, 100)
# Sine function for line plot
y_values_line = np.sin(x_values)
# Cosine function for scatter plot
y_values_scatter = np.cos(x_values)

# Creating Line plot
plt.figure(figsize=(8, 4))
plt.plot(x_values, y_values_line, label='Line Plot', color='blue', linestyle='-', linewidth=2)
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Line plot example')
plt.legend()
plt.show()

# Creating Scatter plot
plt.figure(figsize=(8, 4))
plt.scatter(x_values, y_values_scatter, label='Scatter Plot', color='red', marker='o')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Scatter plot example')
plt.legend()
plt.show()
```

---

## Question 9
What are list comprehensions in Python and how do they work?<br>
Rewrite a for loop that filters and transforms a list into an equivalent list comprehension.

## Answer
List comprehensions are a convenient and compact way to build lists, tuples, sets and dictionaries in just one line. For example instead of writing:
```python
message = ["The", "cat", "is", "purring"]
first_letters = []
for word in message:
    first_letters.appen(word[0])
print(first_letters)
```
We can just write
```python
letters = [word[0] for word in message]
print(letters)
```

---

## Question 10
How does pybind11 handle type conversions between Python and C++?<br>
Provide an example of passing complex data types (like a list or a dictionary) from Python to C++ using pybind11.

## Answer
The conversions are handled through a PYBIND11_MODULE macro that, once defined, creates a function that will be called when an import statement is issued from within Python. For example:
```cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ----------------
// Regular C++ code
// ----------------

void do_something(const std::vector<int> &list) {
  // ...
}

// Wrap as Python module.
PYBIND11_MODULE(example, m) {
  m.doc() = "pybind11 example plugin";

  m.def("do_something", &do_something, "Do something");
}

// In test.py:
import example
list = [1, 2, 3, 4]
example.do_something(list)
```

# Part 1 simulation 2: Open-ended questions

## Question 1
In a UNIX shell, what is the difference between the single pipe (`command1 | command2`) and the double pipe (`command1 || command2`) operators?<br>
Provide a minimal working example for each of the two.

## Answer
The single pipe is like the composition of a function: the output of the command1 gets forwarded as input for the command2. For example `cut -f 3 -d ',' file.csv | sort | wc -l` uses cut to subdividing a file (with some flags for how to do it), then its output gets sorted, lastly it applies a word count (actually a line count due to the flag) to the sorted values.
The double pipe is the logical "or" operation. For example to verify if a file exists and create it if it does not: `[ -e file.txt ] || touch file.txt`.


---

## Question 2
Which types of constructor can be defined for a C++ class?<br>
Provide some examples for a class representing a 3D tensor.

## Answer
Default constructor: takes no arguments; if no constructor is provided, C++ generates a default one automatically using default values (such as empty for strings, zero for numbers).
Parametrized constructor: takes one or more parameters to initialize member variables based on the provided values.
Copy constructor: creates a new object as a copy of an existing object of the same class, taking a reference to an object of the same class as a parameter. It is invoked when objects are copied, passed by value or initialized with other objects.
Copy assignment operator: constructor used for copy assignment
Move constructor: it allows to transfer the resources from one object to another
Destructor: special member function used (and automatically called) to clean up resources held by an object before it goes out of scope or is explicitly deleted. If it's done inside an abstract class, it must be virtual.

```cpp
class Tensor3D {
private:
    int x_size, y_size, z_size;
    std::vector<std::vector<std::vector<double>>> data;

public:
    // Default Constructor
    Tensor3D() : x_size(0), y_size(0), z_size(0) {}

    // Parameterized Constructor
    Tensor3D(int x, int y, int z) : x_size(x), y_size(y), z_size(z) {
        data.resize(x, std::vector<std::vector<double>>(y, std::vector<double>(z, 0.0)));
    }

    // Copy Constructor
    Tensor3D(const Tensor3D& other) : x_size(other.x_size), y_size(other.y_size), z_size(other.z_size), data(other.data) {}

    // Move Constructor
    Tensor3D(Tensor3D&& other) noexcept : x_size(0), y_size(0), z_size(0), data() {
        swap(*this, other);
    }

    // Copy Assignment Operator
    Tensor3D& operator=(const Tensor3D& other) {
      if (this != &other) {
        Tensor3D temp(other);
        swap(*this, temp);
      }
      return *this;
    }

    // Destructor
    ~Tensor3D() {}
};
```


---

## Question 3
Write a C++ function template called sum that accepts a half-open range $[begin, end)$ (as iterators) of int objects and returns the sum of the sequence.

## Answer
```cpp
int sum(Iterator begin, Iterator end) {
  int result = 0;
  for (Iterator i = begin; it != end; ++it) 
    result += *it;
  return result;
}
```

---

## Question 4
What is the meaning of the following C++ code?

```cpp
template <typename T, template <typename> class Container>
class ContainerWrapper {
private:
    Container<T> data;
};
```

How to instantiate a `ContainerWrapper` object?

## Answer
This code defines a template classContainerWrapper with two template parameters: the type of the elements T and another template class called Container. It contains a private member data of type Container. Thanks to these templates, the ContainerWrapper can contain whichever type of Container.
A ContainerWrapper object can be instantiated as:

```cpp
ContainerWrapper<type1, container> wrapper;
```

where type1 and type2 are two types (like int, double, std::string, std::vector etc), in particular type2 is the same type of Container.

---

## Question 5
In C++, what are the key differences in behavior and usage when functions return values by direct value, by pointer, and by reference?

## Answer
When returning by value, it returns a copy of the value, so it's better to use it for small, non-mutable data.
When returning by pointer, it returns the pointer to that value, so it's usually used for dynamically allocated data.
When returning by reference, it returns the reference to that value, so it's used for efficiency and direct modification of data.


---

## Question 6
What are the similarities and differences in object-oriented features between C++ and Python?<br>
How does the implementation of concepts like inheritance and polymorphism vary in these two languages?

## Answer
* A main difference is the lack of pointers in Python, because it automatically manages the memory, contrary to C++.
* Python offers also magic methods, which are special methods automatically invoked in response to certain events or operations, like __add__, __eq__, __getitem__ etc.
* In Python all class members are public and all methods are virtual, which means they can be overloaded anytime. In C++ members can also be private or protected, which is also why you can declare a class as friends of another one (to access its protected members).
* In the class methods, Python requires a first name that refers to the object itself and it's called self; it's the equivalent of the this pointer in C++.
* What said above is also for the constructor in Python, which must take self as first argument and initializes every member with self.nameofmember.
* They both support multiple inheritance.
* While in C++ it is specified with `class DerivateClass : public BaseClass`, in Python it's `class DerivateClass(BaseClass)`.
* If there isn't a constructor for the derived class, the one of the abstract is automatically called in Python.
* When calling a function of the BaseClass, Python can either use its name or the function super().functionToCall.


---

## Question 7
How does Boolean indexing work in NumPy for vectorized data selection?<br>
Give an example of filtering data in an array based on a condition.

## Answer
With NumPy an array of boolean values can be used as an index of another array, where each element of the boolean array indicates whether or not to select the elements from the array (respectively True and False).

```python
a = np.arange(1,100)
b = a % 2 == 0 # When printed returns [True, False, True, False,...]
c = a[b] # When printed returns odd numbers
```

---

## Question 8
How to handle an exception in Python?<br>
Illustrate the syntax of raising and catching exceptions with an example.

## Answer
You can raise an error when something bad is being done, and when executing that operation, you can use a try-except block to handle the exception.

```python
def division(x, y):
  if y == 0:
    raise ValueError("Can't divide by zero.")
  return x/y

try:
  result = division(10,8)
except ValueError as e:
  print("Error: ", str(e))
```

---

## Question 9
The following Python code snippet is meant to create a list named `another_list` with elements 1 and 2.<br>
Find the error and fix it.

```python
def append_to_list(element, target_list=[]):
    target_list.append(element)
    return target_list

my_list = append_to_list(1)
another_list = append_to_list(2)
```

## Answer
The target_list in the argument should not be instantiated as [] but as None, otherwise when a list is given, it overwrites it (in the main here it doesn't happen because it's used this default value).
Furthermore the request was to append 1 and 2 to the same list, here it is not done. So the code should be:

```python
def append_to_list(element, target_list=None):
    if target_list is None:
      target_list = []
    target_list.append(element)
    return target_list

another_list = append_to_list(1)
another_list = append_to_list(2, another_list)
```

---

## Question 10
How does pybind11 handle default arguments in C++ functions when exposed to Python?

## Answer
It allows it, specifying the default value when defining the C++ function in the pybind11 module, for example writing:
```cpp
PYBIND11_MODULE(module, m) {
  m.def("function", &function, py::arg("a"), py::arg("b") = 42);
}
```