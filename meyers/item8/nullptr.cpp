#include <iostream>
#include <memory>

// This item deals with the reasons to use nullptr instead of 0 or NULL

int* f(int) {
    std::cout << "I am in INT" << std::endl;
    return nullptr;
}
int* f(bool) {
    std::cout << "I am in bool" << std::endl;
    return nullptr;
}
int* f(void*) {
    std::cout << "I am in void*" << std::endl;
    return nullptr;
}

class Widget {
};

int f1(std::shared_ptr<Widget> spw) {
}
double f2(std::unique_ptr<Widget> upw) {
}
bool f3(Widget *w) {
}

template<typename funcPtr,
         typename PtrType>
auto lockAndCall (funcPtr fptr, PtrType ptr) -> decltype(fptr(ptr)) {

}


int main() {
    // 1. Both 0 and NULL are not pointers and hence shouldn't be used to assign to them
    // 2. There is rarely or no call that goes to f(void*) although that's the one a pointer
    //     intends to call
    f(0);
//    f(NULL);          // Compile time error.
    f(nullptr);

    // nullptr is of type nullptr_t which implicitly converts to all raw pointers
    // To avoid ambiguity in the function return types.
    auto result = f(nullptr);
    if (result == 0) {
    } // versus
    if (result == nullptr) {
    }
    // provides a difference in reading clarity
    // In case of templates, calling with 0 or NULL is a compile time error
    //auto result1 = lockAndCall(f1, 0);      // error!
    //auto result2 = lockAndCall(f2, NULL);   // error!
    auto result3 = lockAndCall(f3, nullptr);    // fine!!!
}
