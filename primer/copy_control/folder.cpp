#include "folder.hpp"
#include "message.hpp"

namespace communication {
/*
 * @brief: copy constructor for the folders. When a copy for a
 *          folder is made, we copy all the messages and add
 *          that folder to the message as well.
 */

folder_t::folder_t(const folder_t& f) :
    name_(f.name_) {
    for (auto msg : f.messages_) {
        msg->save_msg(this);
    }
}


/*
 * @brief: destructor for a folder, removes the folder from
 *          all the messages that are contained in it.
 */
folder_t::~folder_t() {
    for (auto msg : messages_) {
        msg->remove_msg(this);
    }
}

} // end namespace communication
