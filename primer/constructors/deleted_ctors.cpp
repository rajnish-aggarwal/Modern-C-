#include <iostream>

// Although most classes need a copy constructor/assignment op,
// some classes like the iostream should restrict them.
// Hence, they must prevent anyone from creating copies of these
// objects.

// This is where the deleted functions come into picture.

// No copies, assignments allowed on the below object.
// Also a good thing to note is that the assignment operator
// must always return reference to the lhs(this) pointer.
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy& source) = delete;
    NoCopy& operator=(const NoCopy& rhs) = delete;
    ~NoCopy() = default;
private:
    int foo_{0};
};

// WARNING: Never use a deleted destructor. This will
// 1. Not allow us to declare variables of that type
// 2. Although we can dynamically allocate memory for that type,
//      we can never delete it!
//
// If we do not define any of these members, the compiler implicitly
// generates them for us.
//
//
// In the older standard, we used to make sure no copies/assignment
// operations happen by making these ctors private and not defining them
// this would result in either compile or link time errors.
//
// In the new standard however, one should always use deleted functions
// for this purpose.
//
//
// If any of the members of a class has a deleted copy, assinment or
// destructor, the compiler synthesized version of the class copy/
// assign will also be deleted. This is also true if a member is
// const or reference type variable.
//
int main() {
    NoCopy dont_copy;
    // We are in error here because we are trying to call a deleted
    // function. The compiler will complain when and if we try to
    // do so.
    NoCopy try_me = dont_copy;
}
