#include <iostream>

// Whenever we define classes which have pointers, they can either
// have a value like behavior, where every class object has it's
// own space and does not share resources with any other object
// of the type.
//
// The other type is a pointerlike class, where all the classes use
// the same pointer. We can use smart pointer to manage such resources.
//
// In this file, we define a pointer like version of our hashptr class


/**
 * @brief: For general purpose use, we'd want to use a shared_ptr to
 *          manage shared memory. However, in this course, as an example
 *          we'll use reference count to manage the memory of our
 *          hash ptr object. This class represents the pointerlike
 *          object where all object point to shared memory.
 *
 *          Note: We still follow the rule of three and the print
 *          statement are added for clarity.
 *
 *          Also, we'd ideally put the declarations in a header file
 *          and the definitions in a impl file, this is only for
 *          illustration purpose.
 */
class HashPtr {
private:
    int i_{0};
    std::string *str_ptr_{nullptr};
    std::size_t *ref_count{nullptr};
public:
    // We do not want to provide a default ctor here!
    HashPtr(const std::string &str) :
        str_ptr_(new std::string(str)),
        ref_count(new std::size_t(1)) {}
    // Copy constructor for hashptr, we share the string
    // and the ref count
    HashPtr(const HashPtr& original) : i_(original.i_),
    str_ptr_(original.str_ptr_), ref_count(original.ref_count) {
        ++*ref_count;
        std::cout << "Copied object from an existing hashptr, ref count \
            is now = " << *ref_count << std::endl;
    }

    // Copy assignment operator for HashPtr
    HashPtr& operator=(const HashPtr &rhs) {
        ++*rhs.ref_count;
        if (--*ref_count == 0) {
            delete str_ptr_;
            delete ref_count;
        }
        str_ptr_ = rhs.str_ptr_;
        i_ = rhs.i_;
        ref_count = rhs.ref_count;
        std::cout << "New assignment happens, ref count is = " <<
            *ref_count << std::endl;
        return *this;
    }
    // destructor for hashptr
    ~HashPtr() {
        if (--*ref_count == 0) {
            std::cout << "Object is out of scope" << std::endl;
            delete ref_count;
            delete str_ptr_;
        }

        std::cout << "Didn't delete object, ref count is " <<
            *ref_count << std::endl;
    }

    std::string& get_str() const {
        return *str_ptr_;
    }
};


void foo(HashPtr ptr) {
    HashPtr bar("World");
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
