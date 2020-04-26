#include <iostream>

// Whenever we define classes which have pointers, they can either
// have a value like behavior, where every class object has it's
// own space and does not share resources with any other object
// of the type.
//
// The other type is a pointerlike class, where all the classes use
// the same pointer. We can use smart pointer to manage such resources.
//
// In this file, we define a value like version of our hashptr class


/**
 * @brief: Our valuelike hash ptr class, defines an int and a pointer
 *          to a string. Although the integer value can be implicitly
 *          copied over, to copy the pointer, we need a copy contructor
 *          and a copy assignment operator for this class.
 *
 *          Always follow the rule of three (pre C++11). Whenever you
 *          need a destructor, you almost always need a copy ctor
 *          and a copy assignment operator.
 */
class HashPtr {
private:
    int i_{0};
    std::string *str_ptr_{nullptr};
public:
    HashPtr() {}
    HashPtr(const std::string &str) :
        str_ptr_(new std::string(str)) {}
    // Copy constructor for hashptr
    HashPtr(const HashPtr& original) : i_(original.i_),
    str_ptr_(new std::string(*original.str_ptr_)) {}

    // Copy assignment operator for HashPtr
    HashPtr& operator=(const HashPtr &rhs) {
        // This code is incorrect and does not protect against
        // self assignemnt
        /*
        delete str_ptr_;
        i_ = rhs.i_;
        str_ptr_ = new std::string (*(rhs.str_ptr_));
        return *this;
        */
        // Correct piece of code:
        auto new_ptr = new std::string(*rhs.str_ptr_);
        delete str_ptr_;
        str_ptr_ = new_ptr;
        i_ = rhs.i_;
        return *this;
    }
    // destructor for hashptr
    ~HashPtr() { delete str_ptr_; }

    std::string& get_str() const {
        return *str_ptr_;
    }
};


void foo(HashPtr ptr) {
    HashPtr bar;
    // assignment operator called.
    bar = ptr;
}


int main() {
    HashPtr ptr("Hello");
    std::cout << ptr.get_str() << std::endl;
    // Call copy ctor;
    HashPtr temp(ptr);
    foo(ptr);
    std::cout << ptr.get_str() << std::endl;

    return 0;
}
