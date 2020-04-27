#pragma once

#include <string>
#include <unordered_set>
#include "folder.hpp"
// This file defines the Message class to demonstrate copy control
// for classes that need to do some sort of bookkeeping rather than
// managing dynamically allocated memory.
//
// The message class is the first obejct for it. Each message
// can be contained in multiple folders and the message utility must
// provide functions to save and remove messages from folders.
//
// Also, each message should store the set of folders it is present
// in. Each folder will also have a set to store all the messages it
// contains.
//
// A user first needs to create a message object which contains
// some string based text and then call save on it with a certain
// folder.
//
// A copy of a message must be contained in the same set of folders
// but with a new pointer. Each folder should be updated to
// reflect the new message.
//
// Destroying a message must remove it from all the folders it is
// contained in.
//
// Assignment in our Message object implies that the contents and
// folder of the LHS message will now be that of the RHS message.
// The previous message folders need to be updated to reflect the
// removal of the message.
//
// We also defined move operations for our message class and since
// inserting to a set can throw a bad_alloc exception, we do not mark
// these functions as noexcept

/*
 * @brief: The below message class implements the utilies of the
 *          Message object as specified above.
 */
namespace communication {

using folders_t = std::unordered_set<folder_t*>;
class message_t {
public:
    explicit message_t(const std::string& msg) : message_(msg) {}
    // save my message to the destination folder
    void save_msg(folder_t *folder);
    // remove my message from the specified folder
    void remove_msg(folder_t *folder);
    // copy contructor
    message_t(const message_t& original);
    // copy assignment operator
    message_t& operator=(const message_t& rhs);
    // destructor
    ~message_t();
    // move ctor
    message_t(message_t &&m);
    // move assignment ctor
    message_t& operator=(message_t &&rhs);
    friend void swap(message_t& lhs, message_t& rhs);
private:
    void add_msg_to_folders();
    void remove_msg_from_folders();
    void move_folders(message_t *);
private:
    // text of the file
    std::string message_;
    // set of folders where the message is present.
    folders_t folders_;
};

void swap(message_t& lhs, message_t& rhs);
} // end namespace communication
