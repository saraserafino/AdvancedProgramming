#include <iostream>
#include <string>
class Car {
public:
    std::string model;
    unsigned int year;
// The thing about objects is that you can
// implement functions that act on an object.
    void print_info() {
        std::cout << "Car model: " << model
        << ", year" << year;
    }
};
int main () {
    Car c; //creating an object c of the class Car
    c.year = 2020; //object_name.member_or_variable_name
    c.model = "BMW series 1";
    c.print_info(); //invoke a method
    return 0;
}