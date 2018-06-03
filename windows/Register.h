//
// Created by suson on 5/9/18.
//

#ifndef CHAT_REGISTER_H
#define CHAT_REGISTER_H

#include <gtkmm.h>
#include "Main.h"

class Register : public Main {
private:
    Gtk::Window *window = nullptr;
    Gtk::Label *alertMessage = nullptr;
    Gtk::Entry *nameInput = nullptr;
    Gtk::Entry *emailInput = nullptr;
    Gtk::Entry *passwordInput = nullptr;
    Gtk::Entry *passwordConfirmationInput = nullptr;
    Gtk::Button *registerButton = nullptr;
    std::string name;
    std::string email;
    std::string password;
    std::string passwordConfirmation;
public:
    Register();

    void on_name_change();

    void on_email_change();

    void on_password_change();

    void on_password_confirmation_change();

    void on_register_clicked();

    void show_window();
};


#endif //CHAT_REGISTER_H
