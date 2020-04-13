#include <iostream>
#include <string>
#include "queue.hpp"
#include "queue_impl.hpp"

// Note: Export keyword is deprecated, hence the implementation of the
// template functions has been done in queue_impl.hpp file"

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

    return 0;
}
