//
// Created by suson on 5/9/18.
//

#ifndef CHAT_LOGIN_H
#define CHAT_LOGIN_H

#include <gtkmm.h>
#include "MainWindow.h"
#include "RegisterWindow.h"

class LoginWindow : public MainWindow {
private:
    Gtk::Window *window = nullptr;
    Gtk::Label *alertMessage = nullptr;
    Gtk::Entry *emailInput = nullptr;
    Gtk::Entry *passwordInput = nullptr;
    Gtk::Button *loginButton = nullptr;
    Gtk::Button *registerButton = nullptr;
    std::string email;
    std::string password;
    RegisterWindow registerRef;
public:
    LoginWindow();

    void on_email_change();

    void on_password_change();

    void on_login_clicked();

    void on_register_clicked();

    void show_window();
};


#endif //CHAT_LOGIN_H
