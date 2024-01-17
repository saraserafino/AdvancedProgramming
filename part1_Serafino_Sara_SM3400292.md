# Part 1: Open-ended questions

## Question 1
In Object Oriented Programming, what is *polymorphism*? In C++, what is the difference between dynamic and static polymorphism?<br>
Provide a real-world example for at least one of the two techniques.

## Answer
Polymorphism allows objects of different classes to be treated as objects of a common base class, promoting code flexibility and working with objects at a higher level of abstraction.
The difference between dynamic and static is that dynamic is done at runtime (so it can call method based on the type of object), while static is at compile time.
An example of dynamic polymorphism is when using abstract and derived classes:
```cpp
class Polygon {
public:
    virtual double area() { //something;
    }
};
class Square : public Polygon {
public:
    double area() override { return side * side; }
private:
    double side;
};
void f(const Polygon &p) {
    const double a = p.area();
    // ...
}

int main (){
Square s;
f(s); // Polymorphism converts 'const Square &' to 'const Polygon &'
return 0;
}
```

---

## Question 2
Using template metaprogramming, write a C++ code that, without any use of `for` or `while` loops, prints the first 100 integer numbers.

## Answer
```cpp
template <unsigned int n>
class printInt {
public:
    static void print() {
        printInt<n - 1>::print(); // Recursive call
        std::cout << n << ' ';
    }
};

// Base case where to stop
template <>
class printInt<1> {
public:
    static void print() {
        std::cout << 1 << ' '; // Print the last int i.e. 1
    }
};

int main() {
    printInt<100>::print();
    std::cout << std::endl;
    return 0;
}
```

---

## Question 3
What is *move semantics* in C++? What is the meaning of *lvalue* and *rvalue* expressions, and how are they related to move semantics?<br>
Provide an example where move semantics might be beneficial.

## Answer
Move semantics means transferring ownership of some resource to another object.
An lvalue is an expression that may appear on the left (that's why the name) and on the right-hand side of an assignment. It refers to a memory location and allows us to take its address via the & operator. Examples of it are the value held in a variable, the returned value reference of a function.
An rvalue is an expression that can only appear on the right-hand side of an assignment. Examples of it are the returned value of a function.
They're related to move semantics because they are move operators.
Move semantics might be beneficial when swapping may be costly, so instead of doing
```cpp
void swap(Matrix& a, Matrix& b) {
Matrix tmp{a}; // Make a copy of a.
a = b; // Copy assign b to a.
b = tmp; // Copy assign tmp to b.
}
```
We can do
```cpp
void swap_
with
_
move(Matrix& a, Matrix& b) {
// Swap number of rows and columns.
double* tmp = a.data; // Save the pointer.
a.data = b.data; // Copy the pointer.
b.data = tmp; // Copy the saved pointer.
}
```
In this way we just swap the pointers, saving memory and operations, but only for this specific
situation since we can't write a function template (we don't know how data is stored in T).


---

## Question 4
Given the following C++ code, which *unit tests* would you perform and why?

```cpp
class Geometry {
public:
    double calculate_circle_area(double radius) {
        if (radius < 0) {
            throw std::invalid_argument("Radius cannot be negative.");
        }
        return 3.14159 * radius * radius;
    }

    double calculate_rectangle_area(double length, double width) {
        if (length < 0 || width < 0) {
            throw std::invalid_argument("Length and width cannot be negative.");
        }
        return length * width;
    }
};
```

## Answer
I would do the following unit tests:
Call calculate_circle_area with a negative value and check that I get std::invalid_argument exception, to assess that a negative radius is correctly handled.
Call calculate_circle_area with some positive radius values and assess that the method returns the correct area. To be sure, I would also check that the absolute difference between the actual value and the expected value is less than a small threshold (for example 10 to the power of -9). 
```cpp
std::vector<double> radiuses {0,1,2,4,8,55};
std::vector<double> expected {0, 3.14159, 12.56636, 50.26544, 201.06176, 9503.30975};
Geometry g;
const double threshold = 1e-9;
unsigned int i = 0;
for(double& radius : radiuses){
	double actual = g.calculate_circle_area(radius);
	assertLess(std::abs(expected[radius] - actual), threshold);
}
```
I would then call calculate_rectangle_area with a negative value for height, then call it with a negative value for width, and finally call it with both negative values for height and width. Every time it must throw `std::invalid_argument exception` to assess that negative rectangle sides are correctly handled.
Repeat what done for calculate_circle_area with calculate_rectangle_area, with an array of pairs of height and width and an array of expected areas. Every time the difference between the actual area and the expected area must be lower than a small threshold.


---

## Question 5
What is the difference between local variables and cache variables in CMake? What are shell environment variables and how to access them from a CMake script?<br>
Provide some examples.

## Answer
As the name says, local variables have a limited scope and are not visible outside of their definition, while cache variables store their values, so they can be used to interact with the command line setting options on or off (for example when using a module like the request for the homework2: `option(USE_MODULEC "Use the Numerical Integration Module" ON)`). An example of local variable in the CMake is `set(localvariable "Local Variable")`.
Shell environment variables are set in the environment of the shell from which CMake is invoked and they are accessible using the $ENV keyword (`message("This is a shell environment variable: $ENV{ENV_VARIABLE}")`)


---

## Question 6
Compare the two following Python functions. Which one is more *Pythonic*? Which one is more efficient and why?

```python
def square1(lst):
    result = []
    for i in lst:
        result.append(i * i)
    return result

def square2(lst):
    return [i * i for i in lst]
```

## Answer
The second one is more "pythonic" because list comprehensions are a particularity of Python. It's also more efficient because it's just one line of code instead of 4, you don't need to define another variable (like result in square1) but you just use the one given as input argument.

---

## Question 7
In Python, what is the difference between positional and keyword arguments?<br>
How to enforce that a function receives an input parameter of a _given_ type (e.g., an integer or a string)?

## Answer
A positional argument is an argument of a function which is passed via the position of it in the function call. For example 
```python
def function(arg, arg2):
	pass
function(12,”arg”)
```
12 and “arg” will be positional arguments


---

## Question 8
What is *context management* in Python and which methods should a class expose in order to be able to use it?

## Answer
A context management, used with the magic methods __enter__ and __exit__, is used for resource acquisition and release in a `with` statement, when some resources need to be properly managed, for example when you want to open a file.

---

## Question 9
Vectorize the following Python function that calculates the square of each element in a list, so that it can efficiently work with NumPy arrays.<br>
What are some advantages and disadvantages of the vectorized function?

```python
def square_elements(my_list):
    squared_list = []
    for item in my_list:
        squared_list.append(item ** 2)
    return squared_list
```

## Answer
It is enough to write np.square(my_list) and the function np.square will return a numpy array containing the squared elements of the list.
Vectorizing functions using numpy leads to a faster code because numpy is highly optimised. Moreover, the output is a numpy array, which can be concatenated with other numpy operations.
Some disadvantages might be the fact that it is more difficult to debug vectorized code.


---

## Question 10
Given the following compilation command, what is the meaning of each line/flag and what are they used for?

```bash
g++ \
    -std=c++11 \
    -O3 \
    -shared \
    -fPIC \
    $(python3 -m pybind11 --includes) \
    $(python3-config --cflags --ldflags --libs) \
    example.cpp \
    -o example$(python3-config --extension-suffix)
```

## Answer
```bash
g++ \ # indicates the compiler to use
    -std=c++11 \ # tells the compiler to use C++ 11
    -O3 \ # tells the debugger to perform the highest level of optimizations
    -shared \ # tells it's a shared library
    -fPIC \ # compiler flag to use for shared libraries (PIC stands for Position Independent Code)
    $(python3 -m pybind11 --includes) \ # includes the modules written with pybind11
    $(python3-config --cflags --ldflags --libs) \ #must include respectively compiler flags, linker flags, libraries
    example.cpp \ # is the source file to compile
    -o example$(python3-config --extension-suffix) # -o example tells that the output will have name example
```
This whole command takes a source file example.cpp and compiles it with c++11, adding a module created with pybind11 and a shared library.