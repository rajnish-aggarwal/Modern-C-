#include <iostream>
#include <memory>
#include <string>
#include <vector>

// New and delete operations perform 2 functions. They allocate memory
// and they also call the default or provided constructor for each allocation.
// Sometimes this is not required. All we want to do it allocate uninitialized memory
// and later construct objects in it based on need.
//
// Allocate in C++ is the right tool for doing this.
//

int main() {
    uint32_t n = 100;
    std::allocator<std::string> alloc;
    // allocates unitialized space for 10 strings.
    auto p = alloc.allocate(n);
    // We want to keep the start position for later use hence keep q as a duplicate pointer.
    auto q = p;
    alloc.construct(q++, "hello");
    alloc.construct(q++, " ");
    alloc.construct(q++, "world");
    // q always points to the next uninitialized memory hence it is invalid to dereference
    // and use q. It leads to undefined behavior.

    auto iter = p;
    while (iter != q) {
        std::cout << *iter << std::endl;
        ++iter;
    }
    // When done using the objects, we must remember to destroy them and
    // free the allocated memory
    while (q != p) {
        // --q because this is where our data is.
        alloc.destroy(--q);
    }

    // deallocate memory, remember to specify the number of elements to be deallocated.
    alloc.deallocate(p, n);

    // Library algorithms to copy elements into allocated memory
    std::allocator<int> alloc_int;
    std::vector<int> v{1, 2, 3, 4, 5};
    auto i = alloc_int.allocate(v.size() * 2);
    auto j = std::uninitialized_copy(v.begin(), v.end(), i);
    std::uninitialized_fill_n(j, v.size(), 42);

    auto iter2 = i;
    while (iter2 != j) {
        std::cout << *iter2 << std::endl;
        ++iter2;
    }

    while (j != i) {
        alloc_int.destroy(--j);
    }
    alloc_int.deallocate(i, v.size() * 2);
    return 0;
}
