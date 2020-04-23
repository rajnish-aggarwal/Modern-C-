#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>

// Can we always work with lambda functions? It depends!
// If we need to use the same lambda at a number of places, it becomes
// extremely tedious to write and maintain such code. Hence we'd always
// prefer functions.
//
// But lambda's had the great property of capturing local scope and because
// of it they could support unary predicate functions, ones which take a signle
// argument.
//
// std::bind and placeholders come to our rescue in such a scenario.

/// This check size cannot be used in argument for the find_if function
/// because the comparator should have a unary predicate.
bool check_size(const std::string &s, std::size_t sz) {
    return s.length() >= sz;
}

void print(const std::string &w1, const std::string &w2) {
    std::cout << w1 << " " << w2 << std::endl;
}

void print_ref(std::ostream &os, const std::string &w1, const std::string &w2) {
    os << w1 << " " << w2 << std::endl;
}
int main() {
    std::vector<std::string> words {"my", "name", "is", "rajnish", "aggarwal"};
    std::sort(words.begin(), words.end(),
            [](const std::string &w1, const std::string &w2) { return w1.size() < w2.size(); }
            );
    using namespace std::placeholders;
    auto wc = std::find_if(words.begin(), words.end(), std::bind(check_size, _1, 4));
    std::for_each(wc, words.end(),
            [](const std::string &w) { std::cout << w << " "; });
    std::cout << std::endl;

    // We can alter the arguments to bind as well!
    auto bindPrint = std::bind(print, _2, _1);
    bindPrint("world", "hello");

    // To bind parameters which need to be passed by reference, we should use
    // the ref functionality to generate a reference
    auto bindPrint2 = std::bind(print_ref, std::ref(std::cout), _2, _1);
    bindPrint2("world", "hello");

    // Overloaded functions are not supported with bind!! Their definition cannot be
    // resolved.
    return 0;
}
