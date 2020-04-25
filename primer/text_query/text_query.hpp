#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <memory>

namespace TextQuery {

using file_t = std::vector<std::string>;
using line_num_t = std::vector<std::string>::size_type;
using lines_t = std::set<line_num_t>;
using word_map_t = std::unordered_map<std::string,
                    std::shared_ptr<lines_t>>;

class QueryResult;

/**
 * @brief : This is the query builder class, which takes in a
 *          filestream and builds the internal data structure for
 *          fast queries.
 *
 *          All words are mapped to all the lines they occur in (sorted).
 *          All lines in the file are stored in a vector for reference.
 */
class TextQueryBuilder {
public:
    TextQueryBuilder(std::ifstream &);
    QueryResult query(const std::string &);

private:
    std::shared_ptr<file_t> file_;
    word_map_t wm_;
};

/**
 * @brief: For all user queries, the builder returns a QueryResult.
 *          The result comprises of the search string and a set
 *          containing all the lines where the queried string is present.
 *
 *          The file vector is shared with the builder and can be used
 *          to print all the lines where the string is present.
 */
class QueryResult {
private:
    std::string queryString_;
    std::shared_ptr<file_t> file_;
    std::shared_ptr<lines_t> lines_;

public:
    QueryResult(const std::string &query,
            std::shared_ptr<file_t> f,
            std::shared_ptr<lines_t> lines) :
        queryString_(query), file_(f), lines_(lines) {}
    friend std::ostream& print(std::ostream&, const QueryResult&);
};


std::ostream& print(std::ostream& os, const QueryResult &result);

} // end namespace TextQuery
