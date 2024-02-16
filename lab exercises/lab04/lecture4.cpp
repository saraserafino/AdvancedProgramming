#include <iostream>
/*
// Inheritance
class Base {
public:
    Base() { std::cout << "Constructing base class" << std::endl; }
    ~Base() { std::cout << "Destroying base class" << std::endl; }
};

class Derived: public Base {
public:
    Derived() { std::cout << "Constructing derived class" << std::endl; }
    ~Derived() { std::cout << "Destroying derived class" << std::endl; }
};

int main () {
    Derived d;
    return 0;
}
*/

/*
// Polymorphism pt 1 in this way it's better
class Polygon {
public:
    Polygon(unsigned int n) : n_sides(n) {} //implement a constructor
    unsigned int n_sides;
};

class Rectangle: public Polygon {
public:
    Rectangle() : Polygon(4) {}
};

class Triangle: public Polygon {
public:
    Triangle() : Polygon(3) {}
};

double area(Polygon* p) {
    double a;
    // Compute a
    return a;
}

int main () {
    Polygon *p = new Rectangle(); // il * sta per pointer
    const double a = p->area();
    return 0;
}
*/

// Polymorphism pt 2 let's implement it with abstract class
class Polygon {
public:
    Polygon(unsigned int n) : n_sides(n) {} //implement a constructor
    unsigned int n_sides;
    virtual double area() = 0;
    virtual ~Polygon() = default; // the destructor is implemented by default
    // it's really important to mark the destructor as virtual when using polymorphisms
};

class Rectangle: public Polygon {
public:
    Rectangle() : Polygon(4) {}
    double area() override { return width * height; }
private:
    double width;
    double height;
};

class Triangle: public Polygon {
public:
    Triangle() : Polygon(3) {}
    double area() override { return 0.5 * base * height; }
private:
    double base;
    double height;
};

int main () {
    /*
    Rectangle r;
    Polygon *p = new Rectangle(); // il * sta per pointer
    const double a = p->area();
    // whenever there's a new you have to delete. delete p isn't enough, due to
    // the structure of the polygon it doesn't destruct stuff in rectangle.
    // You have to say that the destructor in the base class is virtual.
    */
    // Before having the abstract class, thanks to polymorphisms we could write
    /* Polygon &p = r;
    const double a = p.area();
    */
    // Now this is illegal, you can instead write:
    Polygon *ptr;
    ptr = new Rectangle();
    ptr->area();
    return 0;
}