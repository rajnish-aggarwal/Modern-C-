#include <iostream>

// Auto plays the role of T in item 1. (See item 1 example)
// Type specifier for the variable is ParamType

// Auto assumes the type initialization in {} to be a
// initializer_list, however template type doesn't
// and this is the only difference between type inference
// between templates and auto


// In C++14, passing function types and returning auto is legal
// as well. However in those cases, auto type deduction works like
// templates


// The return type for the below function cannot be deduced!
/**
 ** auto createInitList() {
 **     return {1, 2, 3};
 ** }
*/

// Similarly, type deduction for auto keywords in lambda doesn't work
/** std::vector<int> v;
 ** ...
 ** auto resetV = [&v](const auto& newValue) { v = newValue; }
 ** ...
 ** resetV({1, 2, 3});      // error, can't deduce type for {1, 2, 3}
 **
 */

template<typename T>
void f_wrong(T param) {
    std::cout << "Type " << typeid(param).name() << std::endl;
}


template<typename T>
void f_correct(std::initializer_list<T> param) {
    std::cout << "Tyep " << typeid(param).name() << std::endl;
}


int main() {
    auto x = 27;        // type of T and paramtype are int
                        // corresponds to case 3 in item 1
    const auto cx = x;  // corresponds to case 3 in item 1
    const auto& rx = x; // corresponds to case 1 in item 1 (non-universal reference)

    // case 2 works similarly.
    auto&& uref1 = x;   // lvalue so paramtype is int&
    auto&& uref2 = cx;  // lvalue so paramtype is int&
    auto&& uref3 = 27;  // rvalue so paramtype is int&&

    // C++ generally has the following four methods of initializing an int
    // All these initialize a[i] to an int of value 27
    int a1 = 27;
    int a2(27);
    int a3 = {27};      // C++ 11
    int a4{27};         // C++ 11

    // These below are initializer lists rather than integers of value 27
    // That is everything enclosed in {} is of type std::initializer_list
    auto x3 = {27};     // std::initializer_list<int>
    auto x4 {27};       // std::initializer_list<int>

    // The following however is an error since a uniform type cannot
    // be deduced
    // Error: std::initializer_list<T>, T cannot be determined
    // auto x5 = {1, 2, 3.0};

    // The below behavior happens because we need to infer two types
    // here, one is std::initializer_list<T> and other is the type for
    // T which is int in this case.
    // f_wrong({ 11, 23, 9});      // can't deduce types
    f_correct({11, 23, 9});     // ok: initializer_list<int>
}
