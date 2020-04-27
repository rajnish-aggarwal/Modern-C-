#include <iostream>
#include <vector>
#include <algorithm>

class Foo {
private:
    std::vector<int> data;
public:
    Foo() {}
    explicit Foo(const std::vector<int> &v) :
        data(v) {std::cout << "Made a regular object" << std::endl;}
    explicit Foo(std::vector<int> &&v) : data(std::move(v))
    {std::cout << "Moved the value using std::move" << std::endl;}
    // This function takes in an rvalue reference foo object.
    Foo sorted() && {
        std::cout << "called rvalue ref version of sorted" << std::endl;
        std::sort(data.begin(), data.end());
        return *this;
    }
    // This function takes a const reference to the this pointer.
    // hence it's contents can't be modified.
    Foo(const Foo& orig) :
        data(orig.data) {}
    Foo& operator=(const Foo& rhs) {
        data = rhs.data;
        return *this;
    }
    Foo sorted() const & {
        std::cout << "called lvalue reference version of sorted"
            << std::endl;
        Foo ret(*this);
        std::sort(ret.data.begin(), ret.data.end());
        return ret;
    }
    // Since we have defined a rvalue reference function sorted() &&
    // we cannot just defined another sorted() const; If one version
    // of the function with the same parameter list has a reference
    // qualifier, all versions must adhere to it.
    // Illegal declaration.
    //Foo sorted() const;
};

Foo& refVal() {
    Foo *f = new Foo(std::vector<int> {5, 4, 3, 2, 1});
    return *f;
}

Foo retVal() {
    return Foo(std::vector<int> {5, 4, 3, 2, 1});
}


int main() {
    Foo f1(std::vector<int> {6, 5, 4, 3, 2, 1});
    std::vector<int> v1{6, 5, 4, 3, 2, 1};
    Foo f2(v1);
    retVal().sorted();
    refVal().sorted();

    return 0;
}
