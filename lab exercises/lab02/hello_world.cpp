#include <iostream>

int main ()
{
    // int a = 10; // direct inizialization
    // int a(10); // constructor-style inizialization
    int a{10}; // uniform inizialization; this is the best way to write it
    
    std::cout << "Hello, world!"
              << a << std::endl;
    return 204;
}
