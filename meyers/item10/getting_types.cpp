#include <iostream>
#include <type_traits>
#include <tuple>
// There is one use case for when we want to use unscoped enums. Where
// we need the type of a field.


using UserInfo = std::tuple<std::string,
                            std::string,
                            size_t>;

// A function that takes an arbitrary enum and can return it's value
// as a compile time constant
template<typename E>
constexpr typename std::underlying_type<E>::type
    toUType(E enumerator) noexcept {
    return
        static_cast<typename std::underlying_type<E>::type>
                                                (enumerator);
}

int main() {
    UserInfo uInfo;

    // Readability of a code like this is very bad
    auto val1 = std::get<1>(uInfo);
    // To elaborate the fields of the userinfo you can have an unscoped
    // enum
    enum UserInfoFields {uiName, uiEmail, uiRep};
    // and one can write, implicit case ensures that we get a
    // size_t object.
    auto val2 = std::get<uiEmail>(uInfo);

    // The same piece of code with scoped enums is more verbose
    enum class UInfoFields {uiName, uiEmail, uiRep};

    auto val3 = std::get<static_cast<size_t>
        (UInfoFields::uiEmail)>(uInfo);

    // The verbosity can be reduced by writing a function that takes
    // an enum and returns the required type. However, std::get is
    // a template and it requires it's argument at compile time.
    //
    // To do this our template function should be able to return its
    // result at compilation, because of which we return a constexpr
    // from it.
    auto val4 = std::get<toUType(UInfoFields::uiEmail)>(uInfo);

    return 0;
}
