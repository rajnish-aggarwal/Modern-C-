#include <iostream>
#include <vector>

// It is possible that sometimes the auto keyword returns unexpected
// values. This is primarily an issue when library implementors return
// proxy objects for optimization or functionality constraints.
//
// A good way to deal with it is to know when that happens and perform
// explicit casting

class Widget {
};

std::vector<bool> features(const Widget& w) {
}
int main() {
    Widget w;
    // In the normal case, std::vector<bool> when accessing an element,
    // return std::vector<bool>::reference_type which is a word rather than
    // a bit.
    bool highPriority = features(w)[5];
    processWidget(w, highPriority);

    // however now if we replace it with auto, what happens is that
    // auto deduces the type of high priority to be std::vector<bool>::reference_type
    // and holds a reference to a temporary object which gets destroyed in the
    // next line.
    // Hence our code produces undefined behavior
    // auto = features(w)[5];

    // This usually happens when writes have created proxy classes to be returned
    // to augment and emulate the behavior of some type.
    // The issue is with the invisible proxy classes for which auto can't really
    // do much.
    //
    // AVOID:
    // auto someVar = expression of "invisible" proxy class type:

    // SOLUTION: explicit cast
    auto highPriority1 = static_cast<bool> (features(w)[5]);

    // explicit casts should always be used whenever you do the cast intentionally!
    return 0;
}
