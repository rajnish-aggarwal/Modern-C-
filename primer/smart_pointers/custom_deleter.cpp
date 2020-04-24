#include <iostream>
#include <memory>

class Foo {
};

void custom_deletor(Foo *obj) {
    std::cout << "hello, I am in the custom deletor" << std::endl;
    delete obj;
}

int main() {
    auto p = new Foo;
    std::shared_ptr<Foo> (p, custom_deletor);
    return 0;
}
