#pragma once

#include <string>
#include <unordered_set>

// This file defines the folders which contain the messages.
//
// Properties:
//  1. Each folder can contain multiple messages
//  2. We can add and remove messages from a folder
//  3. We can add/remove a folder
//

// Note: The folder class follows the sematic properties of the message
//        class, please refer to message.hpp for more details.
//

namespace communication {

class message_t;

using messages_t = std::unordered_set<message_t*>;
class folder_t {
public:
    explicit folder_t(const std::string& name) :
        name_(name) {}
    // copy constructor
    folder_t(const folder_t& original);
    // copy assignment operator is deleted! We do not
    // want to allow one folder to be assigned to another.
    folder_t& operator=(const folder_t& rhs) = delete;
    // api to add a message to a folder
    void add_msg(message_t *msg) {
        messages_.insert(msg);
    }
    void remove_msg(message_t *msg) {
        messages_.erase(msg);
    }
    ~folder_t();

private:
    void remove_folder_from_msgs();
    void add_folder_to_msgs();
private:
    std::string name_;
    messages_t messages_;
};

} // end namespace communication
