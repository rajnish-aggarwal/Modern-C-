#include <iostream>
#include <string>
#include <vector>
#include "queue.hpp"
#include "queue_impl.hpp"

// Note: Export keyword is deprecated, hence the implementation of the
// template functions has been done in queue_impl.hpp file"
// If the queue holds user defined types then the user needs
// to ensure that the ostream<< is overloaded for that user
// defined type

int main() {
    // class templates need to explicitly specify the type argument
    // as it is not deduced by the compiler
    // On the other hand, implicit type conversions are allowed on class
    // templates but not function templates
    Queue<int> qi;
    qi.push(42);
    short s = 42;
    qi.push(s);     // implicit cast from short to int

    // However, if we call a templatized function with int 42 and s,
    // there will be 2 functions generated for us.

    // Memeber functions for a class template are instantiated
    // only if we use them!

    Queue<std::string> qs;
    qs.push("hello");

    std::cout << qi << std::endl;
    std::cout << qs << std::endl;

    short a[4] = {0, 1, 2, 3};
    Queue<int> qi_copy(a, a + 4);
    std::cout << qi_copy << std::endl;
    std::vector<int> vi(a, a + 4);
    qi_copy.assign(vi.begin(), vi.end());
    std::cout << qi_copy << std::endl;

    std::cout << "Vector :" << std::endl;
    for (auto i : vi) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}
