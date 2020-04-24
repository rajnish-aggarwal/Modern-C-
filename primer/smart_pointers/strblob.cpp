#include "strblob.hpp"

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(const std::initializer_list<std::string> &&il) :
    data(std::make_shared<std::vector<std::string>>(il))
{}

void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

const std::string& StrBlob::front() {
    check(0, "empty dataset");
    return data->front();
}

const std::string& StrBlob::back() {
    check(0, "empty dataset");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "empty dataset");
    data->pop_back();
}

