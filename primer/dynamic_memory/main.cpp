#include <iostream>
#include "strvec.hpp"

vector::strvec foo() {
    vector::strvec v;
    v.push_back("assign");
    return v;
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

    vector::strvec v1 = v;
    auto v2 = foo();
    vector::strvec v3 = std::move(v2);
    vector::strvec v4, v5;
    v4 = v3;
    v5 = std::move(v4);
    return 0;
}
