#include <iostream>
#include "strvec.hpp"

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

    return 0;
}
