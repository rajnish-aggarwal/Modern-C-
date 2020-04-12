#include <iostream>

// Why should one prefer scoped enums to unscoped enums!


// enums can mostly not be forward declared, not at least without
// doing some extra work. Scoped enums on the other hand can be
// forward declared.
//

// Hence in C++98, only definitions of enums are allowed and
// declarations are prohibited so that the compiler can decide
// what should be the size of the enum it should allocate.
//

// This is a drawback since any change to the value of the enum, if
// it is included in a header file, results in a whole new compilation
// change. Which is bad!

// In c++ 11, you can do something like
enum class Status; // and define status later!
// The reason that makes this possible is the fact that enums in
// c++11 have a predefined fixed type! And it can be overwritten.
//
//

enum class Status_: std::uint32_t; // rather than the usual int.

// The same forward declaration can be done for unscoped enums as well
// but again they cause namespace pollution.
enum Status_u: std::uint32_t;

int main() {
    // enum names leak into the scope
    // These are referred to as unscoped enums
    //enum Color {black, white, red};
    //auto white = false;   // not allowed because white is already
                            // declared in this scope.

    enum class ColorC {black, white, red};
    auto white = false;     // this is allowed now since white from
                            // the enum does not leak into the scope.
                            //
    ColorC c = ColorC::white;   // can't just declare a variable with
                                // value white like before.

    // type casting is also easily done with unscoped enums
    // since they are not strongly typed and can be implicitly
    // converted to other types.

    // However, for scoped enums, they are strongly typed. And hence
    // no implicity conversions are allowed and we get a compile time
    // error!
}

enum class Status {};
enum class Status_: std::uint32_t {};
enum Stats_u:std::uint32_t {};
