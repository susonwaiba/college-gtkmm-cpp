//
// Created by suson on 5/19/18.
//

#ifndef CHAT_ADDFRIEND_H
#define CHAT_ADDFRIEND_H

#include <gtkmm.h>
#include "Main.h"

class AddFriend : public Main {
private:
    Gtk::Window *window = nullptr;
public:
    void show_window();
};


#endif //CHAT_ADDFRIEND_H
