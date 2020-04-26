#include <iostream>
#include "folder.hpp"
#include "message.hpp"

int main() {
    communication::folder_t folder("foo");
    communication::message_t message("bar");
    message.save_msg(&folder);
    return 0;
}
