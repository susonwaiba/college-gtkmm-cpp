#ifndef CHAT_LOGIN_H
#define CHAT_LOGIN_H

#include <iostream>
#include <gtkmm.h>
#include "App.h"
#include "Register.h"

class Login : public App {
private:
    Gtk::Window *window = nullptr;
    Gtk::Entry *emailInput = nullptr;
    Gtk::Entry *passwordInput = nullptr;
    Gtk::Button *loginButton = nullptr;
    Gtk::Button *registerButton = nullptr;
    std::string email;
    std::string password;
public:
    Login() {
        email = "";
        password = "";
    }

    void on_email_change() {
        email = emailInput->get_buffer()->get_text();
    }

    void on_password_change() {
        password = passwordInput->get_buffer()->get_text();
    }

    void on_login_clicked() {
        std::cout << "Email: " << email << std::endl;
        std::cout << "Password: " << password << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
    }

    void on_register_clicked() {
        Register refRegister;
        refRegister.init(app, builder);
        refRegister.show_window();
    }

    void show_window() {
        builder->get_widget("login_window", window);
        if (window) {

            /*Email Input*/
            builder->get_widget("login_emailInput", emailInput);
            if (emailInput) {
                emailInput->signal_changed().connect(sigc::mem_fun(*this, &Login::on_email_change));
            }
            /*Password Input*/
            builder->get_widget("login_passwordInput", passwordInput);
            if (passwordInput) {
                passwordInput->signal_changed().connect(sigc::mem_fun(*this, &Login::on_password_change));
            }

            /*Login Button*/
            builder->get_widget("login_loginButton", loginButton);
            if (loginButton) {
                loginButton->signal_clicked().connect(sigc::mem_fun(*this, &Login::on_login_clicked));
            }

            /*Register Button*/
            builder->get_widget("login_registerButton", registerButton);
            if (registerButton) {
                registerButton->signal_clicked().connect(sigc::mem_fun(*this, &Login::on_register_clicked));
            }

            app->run(*window);
        }
        delete window;
    }
};


#endif //CHAT_LOGIN_H
