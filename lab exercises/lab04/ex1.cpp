#include <iostream>
#include <cmath> // to use std::pow

class ADExpression {
public:
    virtual ~ADExpression() = default;
    virtual double evaluate() const = 0;
    // while if you implement it in this other way:
    // virtual double evaluate(const double &x) = 0;
    // by doing f.evaluate(3.0) in the main, you
    // evaluate its value in 3
    virtual double derivative() const = 0; // pure methods
};

class Scalar : public ADExpression {
public:
    Scalar(double val, double der = 0.0)
    : val(val), der(der) {} // Constructor
    double evaluate() const override { return val; }
    double derivative() const override { return der; }
private:
    double val;
    double der;
};

class Sum : public ADExpression {
public:
    Sum(const ADExpression &t1, const ADExpression &t2)
    : term1(t1), term2(t2) {} // Constructor
    double evaluate() const override {
        return term1.evaluate() + term2.evaluate();
    }
    double derivative() const override {
        return term1.derivative() + term2.derivative();
    }
private:
    const ADExpression &term1;
    const ADExpression &term2;
};

class Difference : public ADExpression {
public:
    Difference(const ADExpression &t1, const ADExpression &t2)
    : term1(t1), term2(t2) {} // Constructor
    double evaluate() const override {
        return term1.evaluate() - term2.evaluate();
    }
    double derivative() const override {
        return term1.derivative() - term2.derivative();
    }
private:
    const ADExpression &term1;
    const ADExpression &term2;
};

class Product : public ADExpression {
public:
    Product(const ADExpression &f1, const ADExpression &f2)
    : factor1(f1), factor2(f2) {} // Constructor
    double evaluate() const override {
        return factor1.evaluate() * factor2.evaluate();
    }
    double derivative() const override {
        return  (factor1.derivative() * factor2.evaluate()) +
                (factor1.evaluate() * factor2.derivative());
    }
private:
    const ADExpression &factor1;
    const ADExpression &factor2;
};

class Division : public ADExpression {
public:
    Division(const ADExpression &num, const ADExpression &den)
    : numerator(num), denominator(den) {} // Constructor
    double evaluate() const override {
        return numerator.evaluate() / denominator.evaluate();
    }
    double derivative() const override {
        return  (numerator.derivative() * denominator.evaluate()
                - numerator.evaluate() * denominator.derivative())
                / (denominator.evaluate() * denominator.evaluate());
    }
private:
    const ADExpression &numerator;
    const ADExpression &denominator;
};

class Power : public ADExpression {
public:
    Power(const ADExpression &b, int exp)
    : base(b), exponent(exp) {} // Constructor
    double evaluate() const override {
        return std::pow(base.evaluate(), exponent);
    }
    double derivative() const override {
    return  exponent * base.derivative() *
            std::pow(base.evaluate(), exponent - 1);
    }
private:
    const ADExpression &base;
    int exponent;
};

// if you wanted, you could implement this operator
/*
operator+(const ADExpression &a, const ADExpression &b) {
    double val = a.evaluate() + b.evaluate();
    double der = a.derivative() + b.derivative();
};
*/

int main() {
    // set x = 2.0 and its derivative = 1.0
    Scalar x(2.0, 1.0);
    // Define the following polynomials
    // f(x) = 2 x^3 - 3 x^2 + 4 x - 5
    const auto two = Scalar(2);
    const auto three = Scalar(3);
    const auto four = Scalar(4);
    const auto five = Scalar(5);

    const auto x2 = Power(x,2);
    const auto x3 = Power(x,3);

    const auto _4x = Product(four, x);
    const auto _3x2 = Product(three,x2);
    const auto _2x3 = Product(two, x3);

    const auto f1 = Difference(_2x3,_3x2);
    const auto f2 = Sum(f1,_4x);
    const auto f = Difference(f2,five);
    
    // Compute and print its value and derivative at set x
    std::cout << "f(" << x.evaluate() << ") = " << f.evaluate() << std::endl;
    std::cout << "f'(" << x.evaluate() << ") = " << f.derivative() << std::endl;

    // g(x) = 1 / x^2
    const auto one = Scalar(1.0);
    auto g = Division(one, x2);

    // Compute and print its value and derivative at set x
    std::cout << "g(" << x.evaluate() << ") = " << g.evaluate() << std::endl;
    std::cout << "g'(" << x.evaluate() << ") = " << g.derivative() << std::endl;

    return 0;
}