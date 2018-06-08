//
// Created by suson on 5/19/18.
//

#ifndef CHAT_ADDFRIEND_H
#define CHAT_ADDFRIEND_H

#include <gtkmm.h>
#include "MainWindow.h"

class AddFriendWindow : public MainWindow {
private:
    Gtk::Window *window = nullptr;
    Gtk::Label *alert = nullptr;
    Gtk::Button *sayHi = nullptr;
    Gtk::Entry *emailInput = nullptr;
    std::string token;
    std::string email;
public:
    AddFriendWindow();
    void set_values(std::string token_in);
    void on_email_change();
    void on_say_hi_clicked();
    void show_window();
};


#endif //CHAT_ADDFRIEND_H
