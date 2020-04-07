#include <iostream>
#include <deque>

// NOTE: Function and classes are just stubs. You can fill them if need
// be.

class Widget {
public:
    Widget() {
    }
};

bool f(const Widget& w) {
}

template<typename T>
class Vector{
public:
    T& operator[] (std::size_t index) {
    }
};


void authenticateUser() {
}

// The most important use of decltype in C++ is for
// specifying the function return template which depends on
// it's argument tyeps
// In C++ 11 fashion, specifying the return type based on arguments
// The return type cannot be determined unless we know the types of
// c and i and hence we cannot directly expand the auto keyword.
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i) -> decltype(c[i])
{
    authenticateUser();
    return c[i];
}

// The catch is the fact that auto in function retrn types implies template
// type deduction for return type. Hence where we want to return a reference to
// the object, we will end up returning a copy object.

// To get authAndAccess to work, we use decltype as its type deduction in C++14
template<typename Container, typename Index>
decltype(auto) authAndAccessMod(Container &c, Index i) {
    authenticateUser();
    return c[i];
}

// Last but not the least, we did not pass container as a const reference to the
// function because we want to be able to modify the values. This however restricts
// us from sending rvalue references to the function.
// To overcome this, we use global references for declaring the final function
template<typename Container, typename Index>
decltype(auto) authAndAccessFinal(Container&& c, Index i) {
    authenticateUser();
    std::forward<Container>(c)[i];      // to be explained in item 24
}

// For C++ 11
/**
 * template<typename Container, typename Index>
 * auto authAndAccessFinal(Container&& c, Index i)
 * -> decltype(std::forward<Container>(c)[i]) {
 *   authenticateUser();
 *   std::forward<Container>(c)[i];
 * }
 */

// One last thing to consider is when we write the return statement as
// return (retVal); In case of decltype, this will return a reference to
// the retVal, which will be incorrect behavior! decltype(auto) return value
// will return a reference to any object passed to it!
//
// For solution to this problem, refer to item 4

// decltype is primarily used to return the type of a given value or operand
// It does what one would expect
int main() {
    // All below declarations and their decltype is what one
    // would expect
    const int i = 0;            // decltype(i) is const int
    bool f(const Widget& w);    // decltype(w) is Widget&
                                // decltype(f) is bool (*) (const Widget&)
    struct Point {
        int x, y;               // decltype(Point::x) is int
    };                           // decltype(Point::y) is int

    Widget w;                   // decltype(w) is Widget

    if(f(w)) {                  // decltype(f(w)) is bool
    }

    Vector<int> v;              // decltype(v) is Vector<int>
    if (v[0] == 0) {            // decltype(v[0]) is int&
    }

    std::deque<int> d;
    d.push_back(0);
    // Here we are not actually modifying the queue, but a copy element!
    // Also the returned int is an rvalue and we cannot assign it anything!
    // authAndAccess(d, 0) = 10;


    // This works fine now because we return a reference to d from
    // authAndAccessMod
    authAndAccessMod(d, 0) = 10;

    // This can also be used in declaration of variables
    const Widget& cw = w;
    auto myWidget1 = cw;        // strips off the const and reference part
    decltype(auto) myWidget2 = cw;  // myWidget2 is of type const Widget&

    return 0;
}
