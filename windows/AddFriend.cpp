//
// Created by suson on 5/19/18.
//

#include "AddFriend.h"

void AddFriend::show_window() {
    builderRef->get_widget("add_friend_window", window);
    if (window) {
        window->show_all_children();
        window->show();
    }
}