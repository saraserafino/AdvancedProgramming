#include <algorithm>

int main() {
    // regular variables
    auto f = [] (double x) { return x * x * x; };
    int i = 3; // if we want to use i inside f but don't
    // want to change its value, we capture it by copy with [i]
    auto f = [i] (double x) { return x * i; };
    // actually the compiler has converted this function to a functor
    auto f = [&i] (double x) {
        i = 2; //doesn't change the i outside
        return x * i;
    };
    std::for_each(v.begin(), v.end(), f) {
        for(a = v.begin(); a = v.end() - 1)
            f(a);
    };
    return 0;
}