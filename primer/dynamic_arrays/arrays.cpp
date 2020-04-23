#include <iostream>
#include <memory>

int main() {
    // dynamic array allocation can be initialized in c++ 11
    int *p = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    // for freeing the dynamically allocated memory, we should use [] with delete
    // to tell the compiler that we are trying to delete an array
    delete [] p;

    // It is however always good to use smart pointer to manage memmory!
    // Unique ptr's use the delete [] operation when the object goes out of scope
    {
        auto p = std::unique_ptr<int[]> (new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
        // When p goes out of scope, the unique ptr will call delete[] on the managed memory.
        // unique ptr supports the access [] specified
        for (uint32_t i = 0; i < 10; ++i) {
            std::cout << p[i] << std::endl;
        }
    }

    // Shared pointers on the other hand provide no deleted for managed memory.
    // hence we need to provide our own deleter to free memory.
    {
        auto p = std::shared_ptr<int> (new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                [] (int *p) { delete [] p; });
        // shared ptr does not support access
        for (uint32_t i = 0; i < 10; ++i) {
            std::cout << *(p.get() + i) << std::endl;
        }
    }

    return 0;
}
