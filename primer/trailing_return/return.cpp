#include <iostream>

// In this example, we look at how we can use the trailing return type
// for denoting complex type returns

int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};
// A function that returns a pointer to an array
// Here fcn1(int i) says we are declaring a function that
// takes an integer.
// *fcn1(int i) says that we can dereference the result of the call.
// *fcn1(int i) [] says that dereferencing the call returns a pointer
// to 10 ints.
// Finally int (*fcn1(int i)) [] says that the dereference type is int.
int (*fcn1(int i)) [5] {
    return i % 2 == 0 ?  &even : &odd;
}

// The above definition is highly complex. We can simplify it by
// using the trailing return type!
auto fcn2(int i) -> int (*) [5] {
    return i % 2 == 0 ?  &even : &odd;
}

// Finally we can also use decltype for the same. But we need to
// tell decltype that our return is a pointer because by default
// decltype returns the int
decltype(odd) *fcn3(int i) {
    return i % 2 == 0 ?  &even : &odd;
}

int main() {
    auto ret1 = fcn1(10);
    auto ret2 = fcn2(10);
    auto ret3 = fcn3(10);

    return 0;
}
