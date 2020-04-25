#include "text_query.hpp"
#include <fstream>
#include <sstream>

namespace TextQuery {
/**
 * @brief: The text query constructor takes in a file stream.
 *          It parses it to create a line in the file and keep
 *          a mapping for every word in the line to the line number
 *          inside wm_.
 *
 * @param[in]: input file stream
 */
TextQueryBuilder::TextQueryBuilder(std::ifstream &fs) :
   file_(std::make_shared<file_t>()) {
    std::string text;
    while (std::getline(fs, text)) {
        file_->push_back(text);
        line_num_t line_num = file_->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word) {
            if (wm_.find(word) != wm_.end()) {
                wm_[word]->insert(line_num);
            } else {
                auto set = std::shared_ptr<std::set<line_num_t>> (
                        new std::set<line_num_t>());
                set->insert(line_num);
                wm_.emplace(word, set);
            }
        }
    }
}


/**
 * @brief: The query function is exposed to the users of the
 *          TextQueryBuilder class. A user can pass a word to know
 *          all lines it is present in.
 *
 *          If word is not found, we return an empty query object
 *
 * @param[in]: query word
 * @param[out]: result of the query including all lines where the
 *              word is present.
 */
QueryResult TextQueryBuilder::query(const std::string &q) {
    std::shared_ptr<lines_t> lines{nullptr};
    if (wm_.find(q) != wm_.end()) {
        lines = wm_[q];
    }
    return QueryResult(q, file_, lines);
}

/**
 * @brief: Functionality to print a query result. This function takes
 *          in the output stream type and prints the line which contains
 *          the word.
 *
 * @param[in]: stream where a user wants to direct the output
 * @param[in]: result of a query from the TextQueryBuilder
 */
std::ostream& print(std::ostream& os, const QueryResult &result) {
    os << result.queryString_ << " occurs " <<
        result.lines_->size() << " times " << std::endl;

    for (const auto& line : *(result.lines_)) {
        os << line + 1 << ": " <<
            (*result.file_)[line] << std::endl;
    }

    return os;
}

} // end namespace TextQuery
