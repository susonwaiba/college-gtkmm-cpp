//
// Created by suson on 5/6/18.
//

#ifndef CHAT_REGISTER_H
#define CHAT_REGISTER_H

#include <gtkmm.h>
#include "App.h"

class Register : public App {
private:
    Gtk::Window *window = nullptr;
    Gtk::Entry *nameInput = nullptr;
    Gtk::Entry *emailInput = nullptr;
    Gtk::Entry *passwordInput = nullptr;
    Gtk::Button *registerButton = nullptr;
    Gtk::Button *loginButton = nullptr;
    std::string name;
    std::string email;
    std::string password;
public:
    Register() {
        name = "";
        email = "";
        password = "";
    }

    void on_name_change() {
        name = nameInput->get_buffer()->get_text();
    }

    void on_email_change() {
        email = emailInput->get_buffer()->get_text();
    }

    void on_password_change() {
        password = passwordInput->get_buffer()->get_text();
    }

    void on_register_clicked() {
    }

    void on_login_clicked() {
        if (window) {
            window->hide();
        }
    }

    void show_window() {
        builder->get_widget("register_window", window);
        if (window) {

            /*Name Input*/
            builder->get_widget("register_nameInput", nameInput);
            if (nameInput) {
                nameInput->signal_changed().connect(sigc::mem_fun(*this, &Register::on_name_change));
            }

            /*Email Input*/
            builder->get_widget("register_emailInput", emailInput);
            if (emailInput) {
                emailInput->signal_changed().connect(sigc::mem_fun(*this, &Register::on_email_change));
            }

            /*Password Input*/
            builder->get_widget("register_passwordInput", passwordInput);
            if (passwordInput) {
                passwordInput->signal_changed().connect(sigc::mem_fun(*this, &Register::on_password_change));
            }

            /*Register Button*/
            builder->get_widget("register_registerButton", registerButton);
            if (registerButton) {
                registerButton->signal_clicked().connect(sigc::mem_fun(*this, &Register::on_register_clicked));
            }

            /*Login Button*/
            builder->get_widget("register_loginButton", loginButton);
            if (loginButton) {
                loginButton->signal_clicked().connect(sigc::mem_fun(*this, &Register::on_login_clicked));
            }

            window->show();
//            app->run(*window);
        }
//        delete window;
    }
};


#endif //CHAT_REGISTER_H
