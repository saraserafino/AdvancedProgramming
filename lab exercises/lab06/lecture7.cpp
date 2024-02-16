#include <iostream>

void f(int &a) {
    std::cout << "f(int &a)" << std::endl; }

void f(const int &a) {
    std::cout << "f(const int &a)" << std::endl; }

int main() {
    int x = 10;
    f(x); // 1st void
    f(10); // 2nd void

    int y = std::move(x); // forcing the fact that x is moved
    std::vector<double> x(10000);
    std::vector<double> y = std::move(x); // after this x will be empty
    // why?
    int &a = x; // 1st void used; is allowed and has priority
    const int &a = x; // 2nd void used; is allowed;
    int &a = 10; // 1st void; is not allowed
    const int &a = 10; // 2nd void; is allowed;
    return 0;
}