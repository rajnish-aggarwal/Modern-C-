#include <iostream>

//
// ---- THIS CODE COMPILES AND HAS UNDEFINED BEHAVIOR ----
//

// Whenever a class needs a destructor, it almost always
// needs a copy constructor and copy assignment operator

class HashPtr {
private:
    std::string* string_ptr_{nullptr};
public:
    HashPtr(const std::string &str) :
        string_ptr_(new std::string (str)) {}
    // dtor
    ~HashPtr() { delete string_ptr_; }
    const std::string* get_string() {
        return string_ptr_;
    }
};


// This function takes in a hashptr object by
// value hence the first copy is created because of it.
void foo(HashPtr ptr) {
    // uses the compiler generated copy operation,
    // which is incorrect!
    HashPtr new_ptr = ptr;
    // do some work with ptr;
    // Now both thr new ptr and ptr are destroyed and they both
    // call the destructor leading to undefined behavior.
    return;
}

// Another place where one would want to use the copy ctor and the
// copy assignment operation is when you want some unique object in
// every class object you create. That is a good place for these
// constructor even if you don't need the destructor.

int main() {
    HashPtr ptr("hello");
    std::cout << *(ptr.get_string()) << std::endl;
    foo(ptr);
    // Ptr is no longer valid, hence using it crashes the program!
    std::cout << *(ptr.get_string()) << std::endl;
    return 0;
}
