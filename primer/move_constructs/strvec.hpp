// This class defines the interface for the strvec class which behaves
// like std::vector for strings.
//
// A custom allocator is used to allocate unconstructed memory.

#pragma once

#include <string>
#include <memory>
#include <utility>

namespace vector {
class strvec {
public:
    using size_type = size_t;
    strvec() : elements(nullptr), first_free(nullptr), capacity_(nullptr) {}
    std::string* begin() { return elements; }
    std::string* end() { return capacity_; }
    void push_back(const std::string& string);
    // define a push_back function that takes an rvalue
    void push_back(std::string &&string);
    // copy constructor
    strvec(const strvec&);
    // copy assignment operator
    strvec& operator=(const strvec&);
    // destructor
    ~strvec() { free(); }
    // move constructor
    strvec(strvec &&v) noexcept;
    // move assignment operator
    strvec& operator=(strvec &&v) noexcept;
    size_type size() { return first_free - elements; }
    size_type capacity() { return capacity_ - elements; }
private:
    std::string* elements;                // denotes start of vector
    std::string* first_free;              // position of first free element
    std::string* capacity_;               // pointer to the end of vector
    std::allocator<std::string> alloc;
    void check_n_alloc() {
        if (size() == capacity()) {
            reallocate();
        }
    }
    void reallocate();
    void free();
    std::pair<std::string*, std::string*> alloc_n_copy(
            const std::string*, const std::string *);
};

} // end namespace vector
