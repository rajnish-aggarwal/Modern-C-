#include <iostream>
#include <vector>
#include <atomic>

// brace initialization of non-static class members
class Widget {
private:
    int x{0};
    int y = 0;
    //int z(0);       // error!
public:
    Widget(int i, bool b) {
    }
    Widget(int i, double d) {
    }
    Widget(std::initializer_list<long double> il) {
    }
};

Widget w() {
}


int main() {
    // 1. Brace initialization works everywhere!
    // 2. Brace initialization is very harmful when a constructor of a
    //    class uses it as an argument. It overpowers the other constructors
    std::vector<int> v{1, 2, 3};
    std::atomic<int> ai1{0};            // fine
    //std::atomic<int> ai2 = 0;         // incorrect!
    Widget w();                         // doesn't call the default ctor but a function
                                        // returning a Widget object

    Widget w1{};                        // calls the default ctor

    // Braced initialization does not do narrowing type conversions
    double x, y, z;
    // int sum1 {x + y + z};               // error!

    // initialization using () or = doesn't check for narrowing conversions
    int sum2 = x + y + z;               // legal
    int sum3(x + y + z);                // legal

    // The relation between braced initialization and std::initializer_list
    Widget w2(10, true);            // calls first ctor
    Widget w3{19, true};            // std::initializer_list ctor called
    Widget w4(19, 5.0);             // calls second ctor
    Widget w5{10, 5.0};             // calls std::initializer_list ctor

    // If at all there is narrowing conversions, the compiler throws an error
    // and if there is no narrowing conversion then the defined ctor can be
    // called

    // Empty set of bracer {} calls the default constructor
    Widget w6({});                  // calls std::initializer_list ctor
    Widget w7{{}};                  // calls std::initializer_list ctor

    std::vector<int> v2(10, 20);    // initializes 10 elements with values 20
    std::vector<int> v3{10, 20};    // initializes 2 elements with values 10, 20

    // Lesson: Choose one type of initializtion and stick to it with the if's and else's
    return 0;
}

