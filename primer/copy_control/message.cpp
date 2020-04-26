#include "message.hpp"

namespace communication {

/*
 * @brief: Saves this message to the folder
 *          Also stores the folder pointer in the object
 * @param[in]: Folder in which the message needs to be stored
 */

void
message_t::save_msg(folder_t *folder) {
    folder->add_msg(this);
    folders_.insert(folder);
}

/*
 * @brief: remove a message from the given folder
 *          also removes the folder from the set of folders that
 *          contain this message
 * @param[in]: folder from which to remove the message
 */
void
message_t::remove_msg(folder_t *folder) {
    folder->remove_msg(this);
    folders_.erase(folder);
}

/*
 * @brief: Copy contructor, copies the original message string
 *          and the folders it is contained in for this folder.
 *          Also adds the new copy to all the folders.
 */
message_t::message_t(const message_t& original) :
    message_(original.message_),
    folders_(original.folders_) {
        // Add the new message to every folder
        add_msg_to_folders();
    }

/*
 * @brief: Assignment operator, copies rhs message string to lhs.
 *          Copies rhs message folders to lhs. It first removes
 *          the lhs from the current set of folders and then
 *          also adds the message to the rhs folders.
 */
message_t&
message_t::operator=(const message_t& rhs) {
    remove_msg_from_folders();
    folders_.clear();
    message_ = rhs.message_;
    folders_ = rhs.folders_;
    add_msg_to_folders();
    return *this;
}

/*
 * @brief: destructor removes the message from all the folders
 *          it is contained in.
 */
message_t::~message_t() {
    remove_msg_from_folders();
}

/*
 * @brief: private utility to add the message to all the folders.
 *          the user must ensure that the set of folders where one
 *          is adding is the current set of folders and nothing stale.
 */
void
message_t::add_msg_to_folders() {
    for (auto folder : folders_) {
        folder->add_msg(this);
    }
}

/*
 * @brief: private utility to remove the message from all the folders.
 *          the user must ensure that the set of folders to remove
 *          the message from is correct.
 */
void
message_t::remove_msg_from_folders() {
    for (auto folder : folders_) {
        folder->remove_msg(this);
    }
}

/*
 * @brief: Swaps the contents of lhs and rhs also managing the folders.
 */
void
swap(message_t& lhs, message_t& rhs) {
    /*
     * An interesting observation is that the actual code snippet
     * is more optimal than the below code. This is because the below
     * code calls add_msg thrice and remove_msg twice!
    auto temp = lhs;
    lhs = rhs;
    rhs = temp;
    */
    using std::swap;
    for(auto folder : lhs.folders_) {
        folder->remove_msg(&lhs);
    }
    for(auto folder : rhs.folders_) {
        folder->remove_msg(&rhs);
    }
    swap(lhs.folders_, rhs.folders_);
    swap(lhs.message_, rhs.message_);
    for(auto folder : lhs.folders_) {
        folder->add_msg(&lhs);
    }
    for(auto folder : rhs.folders_) {
        folder->add_msg(&rhs);
    }
}

} // end namespace communication
