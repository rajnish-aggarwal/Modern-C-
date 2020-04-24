#include "strblob.hpp"
#include <iostream>

// Given the construction of our strblob class, we can
// create, destroy and assign it without the need to worry about
// memory allocation!

// Shared pointer handles memory based on reference count!

int main() {
    // use initializer list constructor
    StrBlob blob1 {"Hello", "Rajnish", "Aggarwal"};
    // Use copy constructor
    StrBlob blob2(blob1);

    // reference count to the data member of blob1 is 2!
    std::cout << blob1.front() << std::endl;
    std::cout << blob2.front() << std::endl;

    return 0;
}
