#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// a regular lambda function that captures nothing
// any lambda expression has the syntax [] (args) -> return type { body }
// where the angular brackets [] denote the capture list
// for the lambda function.
void fcn1() {
    int i = 42;
    auto f = []() { return 42; };
    auto j = f();
    std::cout << "Printing value from fcn1 " << j << std::endl;
}

// This function finds all the strings which have size >= sz
// and prints them. By definition, lambda's can infer their
// return type from the return statement in the function.
// This is however only applicable when there is only one
// return type in the function.
void biggies(std::vector<std::string> &words,
        std::vector<std::string>::size_type sz,
        std::ostream &os = std::cout, char delim = ' ') {
    std::sort(words.begin(), words.end(),
        [](const std::string &w1, const std::string &w2) {
            return w1.length() < w2.length();
        });

    // now find the first word whose size is greater than
    // the given size. This function captures the sz parameter
    // by value.
    auto wc = std::find_if(words.begin(), words.end(),
            [sz](const std::string &word) {
                return word.length() >= sz;
            });

    std::cout << "Total number of words greater than length " << sz <<
        " are " << words.end() - wc << std::endl;

    // Print all the words. This lambda captures os by reference and
    // delim by value
    std::for_each(wc, words.end(),
            [&os, delim] (const std::string &word) {
                os << word << delim;
            });
    std::cout << std::endl;
}

// This function demonstrates implicit captures for lambda functions
void fcn2() {
    auto i = 42;
    auto f = [=]() { return i; };
    i = 0;
    auto j = f();
    std::cout << "Result of implicit capture by value in fcn2 " << j << std::endl;
}

// This function demonstrates implicit capture by reference
void fcn3() {
    int i = 42;
    auto f = [&]() { return i; };
    i = 0;
    auto j = f();
    std::cout << "Result of implicit capture by reference in fcn3 " << j << std::endl;
}

// Mutable lambda's. These are lambda's which can change the value of the variable they
// capture. By default lambda's are not mutable.
void fcn4() {
    int i = 42;
    auto f = [i] () mutable { return ++i; };
    i = 0;
    auto j = f();
    std::cout << "Result of mutable lambda from fcn4 is " << j << std::endl;
}

// Mutable lambda with a capture by value
void fcn5() {
    int i = 42;
    auto f = [&i] () mutable { return ++i; };
    i = 0;
    auto j = f();
    std::cout << "Result of mutable lambda capturing by reference " << j << std::endl;
}

// When a lambda has complicated return type i.e. more than one return statement,
// we need to explicitly state the return type of the lambda function. In this case the lambda
// must use the trailing return type!
void abs(std::vector<int> &v) {
    std::transform(v.begin(), v.end(), v.begin(),
            [](int i) -> int {
                if (i < 0) {
                    return -i;
                } else {
                    return i;
                }
    });
    std::for_each(v.begin(), v.end(),
            [] (const int i) { std::cout << i << " "; });
    std::cout << std::endl;
}


int main() {
    fcn1();
    fcn2();
    fcn3();
    fcn4();
    fcn5();
    std::vector<std::string> words{"my", "name", "is", "rajnish", "aggarwal"};
    std::vector<int> vals{1, 2, -1, -2, 3, -4, -10};
    biggies(words, words[1].length());
    abs(vals);

    return 0;
}
