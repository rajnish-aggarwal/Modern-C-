#include <iostream>

// Many a times, classes implement the swap operation where one pointer
// is exchanged for another. Regular cases involve one copy and two assignment operations
// in these scenarios. However, calling the copy and assign operations would needlessly
// allocate memory. Something we do not really need.
//
// Hence, we write our own swap function and make it the friend of out HashPtr class

class HashPtr {
private:
    std::string *string_ptr{nullptr};
    std::size_t *ref_count{nullptr};

public:
    HashPtr(const std::string &str) :
        string_ptr(new std::string(str)),
        ref_count(new std::size_t(1)) {}
    HashPtr(const HashPtr &original) :  string_ptr(original.string_ptr),
    ref_count(original.ref_count) {
        *ref_count++;
    }
    /// sometimes, class designers use the swap function in the
    /// assignment operator since it is exception safe.
    /// Taking argument by value means the compiler will create
    /// a copy for us.
    HashPtr& operator=(HashPtr rhs) {
        swap(rhs, *this);
        /// The rhs object string will be freed if this was
        /// the only reference to it!
        return *this;
    }
    ~HashPtr() {
        if (--*ref_count == 0) {
            delete string_ptr;
            delete ref_count;
        }
    }
    friend void swap (HashPtr& lhs, HashPtr& rhs);
    const std::string& get_str() const {
        return *string_ptr;
    }
};

inline
void swap(HashPtr& lhs, HashPtr& rhs) {
    using std::swap;
    swap(lhs.ref_count, rhs.ref_count);
    swap(lhs.string_ptr, rhs.string_ptr);
}

void foo(HashPtr ptr) {
    HashPtr bar("World");
    bar = ptr;
}

int main() {
    HashPtr ptr("Hello");
    std::cout << ptr.get_str() << std::endl;
    foo(ptr);
    std::cout << ptr.get_str() << std::endl;
}
