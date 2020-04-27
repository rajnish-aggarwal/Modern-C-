#include "strvec.hpp"
#include <iostream>

namespace vector {

/*
 * @brief: Adds str to the element list of the vector at the location
 *          of first free. It checks to see if there is space to
 *          allocate and reallocates if there isn't
 */
void
strvec::push_back(const std::string& str) {
    check_n_alloc();
    alloc.construct(first_free++, str);
}

/*
 * @brief: Our strvec class is a valuelike object, which implies that
 *          each object manages its own memory.
 */
strvec::strvec(const strvec& v) {
    std::cout << "called copy ctor" << std::endl;
    auto ret_type = alloc_n_copy(v.elements, v.first_free);
    elements = ret_type.first;
    first_free = capacity_ = ret_type.second;
}

/*
 * @brief: The assignment operator needs to free the existing
 *          memory in the vector and allocate new one copying the
 *          elements on the rhs
 */
strvec&
strvec::operator=(const strvec& rhs) {
    std::cout << "called copy assignment op" << std::endl;
    // make sure to prevent against possible self assignment.
    auto ret_type = alloc_n_copy(rhs.elements, rhs.first_free);
    free();
    elements = ret_type.first;
    first_free = capacity_ = ret_type.second;
    return *this;
}

/*
 * @brief: Allocates new memory for the vector and
 *          copies all elements in the range begin to end for it.
 */
std::pair<std::string*, std::string*>
strvec::alloc_n_copy(const std::string* begin, const std::string* end) {
    auto start = alloc.allocate(end - begin);
    return {start, std::uninitialized_copy(begin, end, start)};
}

/*
 * @brief: Destroys the elements in the storage and then frees the
 *          memory.
 */
void
strvec::free() {
    while (first_free != elements) {
        alloc.destroy(--first_free);
    }
    alloc.deallocate(elements, capacity_ - elements);
}

/*
 * @brief: In general, when we copy memory, we have a source and
 *          destination and both are in use. However, for reallocate,
 *          the source memory will no longer be required. Hence
 *          it would be a waste of time if we copy every element
 *          from its source to destination. For solving this,
 *          the library has introduced the move operation!
 */
void
strvec::reallocate() {
    size_type sz = size() ? 2 * size() : 1;
    auto new_start = alloc.allocate(sz);
    auto curr_start = elements;
    auto start = new_start;
    // Our realloc moves resources from source to destination.
    while (curr_start != first_free) {
        alloc.construct(start++, std::move(*curr_start++));
    }
    free();
    elements = new_start;
    first_free = start;
    capacity_ = elements + sz;
}

/*
 * @brief: Here we define the move construtor for the strvec class. The move ctor
 *          always takes in an rvalue reference and must ensure that the moved-from
 *          object is left in a destructible state.
 *
 *          Making a function no except has two advantages, it tells the compiler not to
 *          do extra work to make sure of it. Also, if our move operation can throw
 *          exceptions, it is better to use copy constructors because then we can guarentee
 *          correctness even in the face of failures.
 */
strvec::strvec(strvec &&v) noexcept :
    elements(v.elements), first_free(v.first_free), capacity_(v.capacity_) {
    std::cout << "called move constructor" << std::endl;
    v.elements = v.first_free = v.capacity_ = nullptr;
}

/*
 * @brief: The move assignment operator must guard against self assignment
 *          v = std::move(v); // std::move returns an rvalue!
 *
 *          The moved from object after the move operator should still remain
 *          valid, in the sense that a user should still be able to call it's
 *          API's.
 */
strvec&
strvec::operator=(strvec &&v) noexcept {
    std::cout << "called move assignment operator" << std::endl;
    if (this != &v) {
        free();
        elements = v.elements;
        first_free = v.first_free;
        capacity_ = v.capacity_;
        v.elements = v.first_free = v.capacity_ = nullptr;
    }
    return *this;
}

} // end namespace vector
