/* This item presents a reasonable argument of why one would want to use the auto keyword
 * instead to standard type deductions. Pitfalls are elaborated in item 2 (std::initialzer_list)
 * and item 6.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

// Prevent lengthy initialization names and self type deductions
template<typename It>
void dwin(It b, It e) {
    while (b != e) {
        // because we don't know the type of the iterator.
        typename std::iterator_traits<It>::value_type
            currValue = *b;
    }

    // On the other hand
    while (b != e) {
        auto cVal = *b;     // done!
    }
}

class Widget {
public:
    bool operator< (const auto& p1) {
        return *this < p1;
    }
};


int main() {
    int x;                  // uninitialzed variables are harmful
    //auto x;               // unitialized auto variables are errors!
    auto x_init = 0;

    // auto can represent closures, types only known to cmpilers
    auto deferUPless =
        [](const std::unique_ptr<Widget> &p1,
           const std::unique_ptr<Widget> &p2)
        { return *p1 < *p2; };
    // In C++14, parameters to lambda functions can be auto
    auto derefUPless =
        [](const auto &p1, const auto &p2) {
            // remember type deductions for auto are like the template
            // parameter T
            return *p1 < *p2;
        };
    // One can say that to record closures, we can use std::function
    // objects. The issue with this it the fact that this is an instantiation
    // of an std::function template which has a fixed size different than
    // the closure for a given template. If the size is not adequate, we
    // can even allocate objects on the heap! Hence std::function objects
    // use more memory than auto declared closure captures. And it is slower!
    //
    // And as can be seen, it is very tedious to type and error prone.
    std::function<bool(const std::unique_ptr<Widget>&,
                       const std::unique_ptr<Widget>&)>
        derefFPles = [](const std::unique_ptr<Widget>& p1,
                        const std::unique_ptr<Widget>& p2) {
            return *p1 < *p2;
        };
    // mismanaged types because of explicit specification
    std::vector<int> v;
    // std::vector<int>::size_type is the actual return object
    // of std::vector<int> which is guarenteed to be as large as
    // the machine width. However unsigned has a size of 32 bits even
    // on a 64 bit machine!!
    unsigned sz = v.size();

    // Next consider a hash table where the keys are const objects!!
    std::unordered_map<std::string, int> m;
    // Now because our keys are const objects, the compiler is forced to
    // do an implicit copy for us!!
    for (const std::pair<std::string, int> &p : m) {
        // .. iterate over the key value pairs in a map
    }
    // Real declaration
    for (const std::pair<const std::string, int> &p : m) {
    }
    // Using auto prevents us from falling into this trap!
    for (const auto& p : m) {
        // do something!
    }

    // Hence based on the above examples, it is convincing enough to use
    // the auto keyword instead of manually typing each variables type.
    // For readability, one can use better naming conventions.
    return 0;
}
