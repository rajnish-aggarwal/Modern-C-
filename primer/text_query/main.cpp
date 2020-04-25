#include "text_query.hpp"
#include <fstream>

int main() {
    std::string fname;
    std::cout << "Please enter the filename to create a hash: ";
    std::cin >> fname;
    std::ifstream fs(fname);

    // build the text query object
    TextQuery::TextQueryBuilder tq(fs);
    TextQuery::print(std::cout, tq.query("foo"));

    return 0;
}
