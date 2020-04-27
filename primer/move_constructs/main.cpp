#include <iostream>
#include "strvec.hpp"

vector::strvec foo() {
    vector::strvec v2;
    v2.push_back("assign");
    return v2;
}

int main() {
    vector::strvec v;
    v.push_back("Hello");
    v.push_back("Rajnish");
    v.push_back("Aggarwal");
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::cout << "Vector capacity " << v.capacity() << std::endl;
    std::cout << "Vector size " << v.size() << std::endl;

    // We previously saw that even the move operations call the
    // copy ctors when only copy ctors are defined i.e. the compiler
    // will not synthesize move operations when copy ctors are present
    // Rvalue references can be converted to const references!
    vector::strvec v1 = v;
    auto v2 = foo();
    vector::strvec v3 = std::move(v2);
    vector::strvec v4, v5;
    v4 = v3;
    v5 = std::move(v4);
    return 0;
}
