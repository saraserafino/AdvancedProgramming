# Part 1: Open-ended questions

## Question 1
Describe a specific task you automated using a shell script.<br>
What was the task, and how did your script improve the process? Share the script and explain its functionality.

## Answer
In the first homework for this course, I used a shell script in order to build everything together. The task of the homework was to create a base class SparseMatrix and its two derived classes SparseMatrixCOO and SparseMatrixCSR that allow you to write a sparse matrix with two different methods.
My build.sh improved the process allowing me to build what required faster and in a more efficient way. The build.sh was:
```bash
#!/bin/bash
set -x
mkdir -p build
g++ -std=c++17 -Iinclude/ src/SparseMatrix.cpp -c -o build/SparseMatrix.o
g++ -std=c++17 -Iinclude/ src/SparseMatrixCOO.cpp -c -o build/SparseMatrixCOO.o
g++ -std=c++17 -Iinclude/ src/SparseMatrixCSR.cpp -c -o build/SparseMatrixCSR.o
g++ -std=c++17 -Iinclude/ src/main.cpp -c -o build/main.o
g++ -std=c++17 -Wall -Wpedantic build/SparseMatrix.o build/SparseMatrixCOO.o build/SparseMatrixCSR.o build/main.o -o build/HomeworkSF
set +x
if [ $? -eq 0 ]; then
    echo "Build successful! You can run the program using ./build/HomeworkSF"
else
    echo "Build failed."
fi
```
With this, in the terminal, you first give the permissions with `chmod +x build.sh`, then write `./build.sh`, lastly run it with `./build/HomeworkSF`.
In this way, the procedure of preprocessing and compiling (and eventually linking if there was a library) is automated, you just have to run the build file and then load the program.


---

## Question 2
Design a minimal C++ class hierarchy for a simple game engine that includes entities like `Player`, `Enemy`, and `Item`.<br>
Discuss how polymorphism, inheritance, or other forms of relationship between classes can be used to organize and extend the engine.

## Answer
The design might be:
```cpp
class ActiveObject{
    public:
        virtual void doAction() = 0;
        virtual void render() = 0;
        unsigned long numPolygons;
        virtual ~ActiveObject() = default; 
}
class Item : public ActiveObject{
    public:
        Item() {...};
        void doAction override{...};
        void render() override{...};
}
class Player : public ActiveObject{
    public:
        Player() {};
        void doAction override{...};
        void render() override{...};
}
class Enemy : public ActiveObject{
    public:
        Enemy() {};
        virtual void doAction override{...};
        void render() override{...}
}
```
Where ActiveObject is an abstract base class which represents a rendered object capable of performing an action. All the ohter classes inherit from this base class.
- Polymorphism can be used for example when all the object in a scene must perform their specific action. Every item of an array containing all the ActiveObjects in a scene have just to call .doAction.
- Inheritance can be used when rendering an object. Every ActiveObject must be rendered, but in different ways. For example if the game is a "first person shooter" just the part of the player visible in the screen can be rendered (hands, legs); while an Item must always be rendered.

---

## Question 3
Provide an example of how you've used a functor or lambda function in C++ to simplify your code, especially in the context of STL algorithms.<br>
Explain your choice and its benefits.

## Answer
For example, I used a lambda function in the second assignemnt of the course. In the statistic operations module, when I needed to compute the median of a column of a dataset, I had to sort the column to find the median value. What I did was:
```cpp
// Sorting the data based on the index of the variant
    std::sort(sortedData.begin(), sortedData.end(), [](const auto &a, const auto &b) {
        if (a.index() == 0 && b.index() == 0) {
            return std::get<double>(a) < std::get<double>(b);
        } else if (a.index() == 1 && b.index() == 1) {
            return std::get<std::string>(a) < std::get<std::string>(b);
        } else {
            // If they're different types, sort by index
            return a.index() < b.index();
        }
    });
```
Since the column had either `double` or `std::string` values, I had to create a custom comparator with a lambda function, which checked the type of the values that were compared. If they were `double`, I compared them by their value. If they were `std::string`, I compared them by the < operator of the `std::string` class. Using the STL and lambdas was very convinient, as I did not need to write my sorting algorithm, but just define a custom comparator "on the fly". The code was more readable and I could use a sorting algorithm which has been implemented to be very efficient, which is a great advantage considering that the dataset was quite large.

---

## Question 4
Consider the following C++ code snippet.<br>
Detect as many errors as you can and fix them.

```cpp
class Shape {
public:
    virtual void print() const = 0;
};

class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}
    
    virtual void print() const override {
        std::cout << "A circle with radius " << radius << "." << std::endl;
    }

private:
    double radius;
};

auto s1 = &Shape();
s1->print();

auto s2 = new Circle(0.5);
s2->print();

delete s1;
delete s2;
```

## Answer
```cpp
class Shape {
public:
    virtual void print() const = 0;
    virtual ~Shape() = default; // the virtual constructor was missing
};

class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}
    
    void print() const override {
        std::cout << "A circle with radius " << radius << "." << std::endl; // virtual is not necessary if no class inherits from Circle
    }

private:
    double radius;
};

// You cannot instantiate an object of an abstract class
//auto s1 = &Shape();
//s1->print();

auto s2 = new Circle(0.5);
s2->print();

//delete s1;
delete s2;
```

---

## Question 5
The following C++ code snippet implements the Babylonian method to approximate the square root of a given number at compile time, exploiting template metaprogramming.<br>
However, the method only works for integer square roots. How would you use it to approximate, e.g., $\sqrt{2}$ at compile time?

```cpp
#include <iostream>
#include <type_traits>

template <unsigned int N, unsigned int X, unsigned int NextX = (X + N / X) / 2>
struct BabylonianMethod : BabylonianMethod<N, NextX> {};

// Specialization to stop recursion.
template <unsigned int N, unsigned int X>
struct BabylonianMethod<N, X, X> {
    static constexpr unsigned int value = X;
};

// Helper template to initiate the Babylonian method with a good enough first guess.
template <unsigned int N>
using Sqrt = BabylonianMethod<N, N / 2 + 1>;

int main() {
    // Compute square root of 16 at compile time.
    constexpr unsigned int sqrt16 = Sqrt<16>::value;
    std::cout << "Square root of 16 is " << sqrt16 << std::endl;

    return 0;
}
```

## Answer
I would change the template definitions to accept floating point numbers, in this way
```cpp
#include <iostream>
#include <type_traits>

template <typename T, T N, T X, T NextX = (X + N / X) / 2>
struct BabylonianMethod : BabylonianMethod<T, N, NextX> {};

template <typename T, T N, T X>
struct BabylonianMethod<T, N, X, X> {
    static constexpr T value = X;
};

template <typename T, T N>
using Sqrt = BabylonianMethod<T, N, N / 2 + 1>;

int main() {
    // Compute square root of 2.0 at compile time.
    constexpr double sqrt2 = Sqrt<double, 2>::value;
    std::cout << "Square root of 2 is " << sqrt2 << std::endl;

    return 0;
}
```
Note that there might be problems when the algorithm is converging but cannot reach the same exact value of the floating point solution. A compile-time check with a small epsilon would lead to a more stable and consistent algorithm.

---

## Question 6
Explain how you would convert an existing `Makefile` project to use CMake, highlighting the steps involved in creating a `CMakeLists.txt` file.<br>
Discuss benefits and disadvantages, if any, of this transition.

## Answer
I would firstly create a `CMakeLists.txt` file in the root directory; then in this file I would specify the minimum reuired CMake Version `cmake_minimum_required(VERSION 3.27.1)` and the `project name project(ProjectTitle)`. After this general settings, I would create a CMakeFile.txt file for every submodule that I want to create. In every CMake file I would add executables or libraries to define the targets of my project, link libraries or set compiler flags. After setting all the CMakeLists.txt files, I would create a build directory where the generated MakeFile can be used to build the project.
Using CMake has several advantages: it is platform independent, so the project can be easily ported to different systems; CMake utilizes also a clearer and more concise way to specify build settings, which makes the project more mantainable. Especially the creation of submodules (setting cache variables on/off) gave me a great advantage when developing projects, allowing me to mantain and build seperate modules within the same project with ease.

---

## Question 7
Share your experience with debugging or profiling a performance issue in a C++ or Python application.<br>
Which tools or techniques did you use, and how did you resolve the issue?

## Answer
After the first exam, I tried to do again at home the second part, which involved the implementation of the Gradient Descent algorithm. The class was not working well, it was not converging at all. So I tried to use the gdbc tool in order to debug the `optimize` function. I put a breakpoint in the function and then checked the value of the maximum number of iterations to check if they were correctly set. Using `print maxIterations` gave me value 0, so the algorithm was not executing even one iteration. Thanks to the debugger I narrowed the problem down, and discovered that I did not set correctly the algotithm parameters. After fixing this issue, the algorithm worked as expected.

---

## Question 8
Explain the difference between list comprehensions and generator expressions in Python.<br>
Give an example of a scenario where using a generator would be significantly more memory-efficient than a list comprehension.

## Answer
Both list comprehensions and generator expression could be used to create lists based on some conditions or specific functions to apply to every item. List comprehensions actually creates the whole list, like here:
```python
l = [0,1,2,5,100]
l2 = [x**2 for x in l]
for value in l2:
    print(l2)
```
l2 will contain all the squared values of the original list l.
If a generator expression is used:
```python
l = [0,1,2,5,100]
l2 = (x**2 for x in l)
for value in l2:
    print(l2)
```
l2 would not contain the squared values but it would generate them at every iteration of the for cycle, so just when needed. In this way generator expressions are much more memory efficient than list comprehensions. For example when processing a very large dataset, generator expressions would be the perfect fit, since there would not be necessary to load the entirety of the dataset into memory, but just process its records when needed.

---

## Question 9

Given the following Python code, which uses a custom class decorator to modify or add methods to classes, analyze how the decorator affects both the `BaseClass` and the `ChildClass` with respect to the methods `greet` and `farewell`.<br>
Considered the intricacies of inheritance, method overriding, and dynamic attribute modification introduced by the decorator, explain what happens when instances of these classes call the `greet` and `farewell` methods.

```python
def class_decorator(method_name):
    def wrapper(cls):
        original_method = getattr(cls, method_name, None)
        if original_method:
            def new_method(self, *args, **kwargs):
                return f"Modified behavior: {original_method(self, *args, **kwargs)}"
            setattr(cls, method_name, new_method)
        else:
            def new_method(self):
                return f"New method added to {cls.__name__}"
            setattr(cls, method_name, new_method)
        return cls
    return wrapper

@class_decorator("greet")
class BaseClass:
    def greet(self):
        return "Hello from BaseClass"

@class_decorator("greet")
@class_decorator("farewell")
class ChildClass(BaseClass):
    def farewell(self):
        return "Goodbye from ChildClass"
```

## Answer
The decorator modifies the original method of a class if a method with that name is present in the class. Otherwise, it adds the method to the class.
- When `BaseClass` calls `greet()` it outputs `Modified behavior: Hello from BaseClass` because the method is already present.
- When `ChildClass` calls `greet()` it outputs `Modified behavior: Modified behavior: Hello from BaseClass` because the method has been inherited by the BaseClass and was modified originally by the decorator.
- When `ChildClass` calls `farewell()` it outputs `Modified behavior: Goodbye from ChildClass` because the method is already present but just in the ChildClass.

---

## Question 10
Is it possible to use pybind11 to execute Python code from within C++ code?<br>
What are possible use cases in the field of data science and scientific computing?

## Answer
Yes it is possible, I did it in the homework 3 for implementing the Gauss Legendre integration method since the one I implemented in C++ had some memory leaks. For doing so I defined its class in a slightly different way: instead of just defining the constructor in Python, I added a way to compute nodes and weights using NumPy. The code was the following
```python
from numpy.polynomial import legendre
import numpy as np

# ----------------
# Python interface
# ----------------

# GaussLegendre is better implemented with NumPy
# Note: it can only compute nodes and weights in [-1,1]
class GaussLegendre(Quadrature):
    def __init__(self, a, b, nBins):
        Quadrature.__init__(self)
        # Call numpy.polynomial.legendre.leggauss
        self.nodes,self.weights = np.polynomial.leggauss(nBins - 1)
```
In the main.py, I then defined the function to compute an integral in this way:
```python
# For Gauss-Legendre, the interval is fixed to [-1,1] due to numpy.polynomial.legendre.leggaus's
# definition which was overloaded in the C++ method (see IntegrationMethods.py for the overload)
@execution_time
def test_GaussLegendre_cpp(function, trueValue, nBins):
    GL = moduleC.GaussLegendre(-1, 1, nBins)
    integrationValue = moduleC.IntegrateGaussLegendre(function, GL)
    error = abs(trueValue - integrationValue)
    return integrationValue, error
```
Where moduleC was the module I created for that functions and classes.
As I did with my code, possible use cases in the field of data science and scientific computing can be the implementation of some methods that in C++ require more compilation-time or are more complex. Moreover, Python libraries are made by experts, therefore using them you're less prone to make mistakes.