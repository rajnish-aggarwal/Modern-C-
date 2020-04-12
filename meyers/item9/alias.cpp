#include <iostream>
#include <vector>
#include <list>
// This item convinces us of why we should use the using keyword instead of
// typedef's

// To reduce the size of the declaration, typedef's are good but very c++98 style.
// Function pointers are easier to digest with using rather than typedef's


// Difference between dependent and non-dependent types
// MyAllocList<T>::type is a type dependant on the template param
// T

// On the other hand, when a compiler encounters MyAllocList<T> as
// an alias declaration, it know it must refer to a type and hence
// it becomes a non-dependent type.
//
// When compilers however see MyALlocList<T>::type they can't be sure
// if type is a parameter inside the struct or a typedef.
//

class Wine {
};

class Widget {
};

// Now when someone says MyAllocList<T>::type, what type is really
// depends on what T is and hence compilers require you to write
// typename to make sure that it a defined type rather than a
// data member.
int foo(std::vector<int> &v) {
    std::cout << "I am in foo" << std::endl;
}

using fptr = int (*) (std::vector<int> &v);
// versus
typedef int (* fptr_dep) (std::vector<int> &v);

// alias declarations can be templatized whereas typedef declarations cannot!
// in this case the declarations are called aliased templates.

// E.g. defining a linked list with a custom allocator
template<typename T>
class myAlloc;

template<typename T>
using MyAllocList = std::list<T, myAlloc<T>>;

// with typedef's however, we need to include a templated structure
// which is much more work.
template<typename T>
struct MyAllocListS {
    typedef std::list<T, myAlloc<T>> type;
};


template<typename T>
class myAlloc {
    // In this class, if we want a private variable which uses the template definition.
private:
    // declarations of this sort become important because we do not know if type
    // is a member of MyAllocListS or a typedef!
    typename MyAllocListS<T>::type listS;
    MyAllocList<T> list;            // no need for the cumbersome typename::type
};


/*
template<>
class MyAllocList<Wine> {
    enum class WineType { red, white, rose };
    WineType type;                          // here type is a data mem.
};
*/

int main() {
    fptr fptr1 = foo;
    fptr_dep fptr2 = foo;
    std::vector<int> v;

    fptr1(v);
    fptr2(v);

//    MyAllocList <Widget> lw;
//    MyAllocListS<Widget>::type lwS;
}


