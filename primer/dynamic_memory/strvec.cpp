#include "strvec.hpp"

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
    while (curr_start != first_free) {
        alloc.construct(start++, std::move(*curr_start++));
    }
    free();
    elements = new_start;
    first_free = start;
    capacity_ = elements + sz;
}

} // end namespace vector
