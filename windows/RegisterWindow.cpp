//
// Created by suson on 5/9/18.
//

#include <iostream>
#include <cpr/cpr.h>
#include <json.hpp>
#include "../include/Config.h"
#include "RegisterWindow.h"

RegisterWindow::RegisterWindow() {
    name = "";
    email = "";
    password = "";
    passwordConfirmation = "";
}

void RegisterWindow::on_name_change() {
    name = nameInput->get_text();
}

void RegisterWindow::on_email_change() {
    email = emailInput->get_text();
}

void RegisterWindow::on_password_change() {
    password = passwordInput->get_text();
}

void RegisterWindow::on_password_confirmation_change() {
    passwordConfirmation = passwordConfirmationInput->get_text();
}

void RegisterWindow::on_register_clicked() {
    Config config;
    auto response = cpr::Post(cpr::Url{config.api_url + "register"}, cpr::Payload{
            {"name",                  name},
            {"email",                 email},
            {"password",              password},
            {"password_confirmation", passwordConfirmation},
    });
    auto json = nlohmann::json::parse(response.text);
    std::cout << json.dump(4) << std::endl;
    switch (response.status_code) {
        case 200:
            alertMessage->override_color(Gdk::RGBA("green"), Gtk::STATE_FLAG_NORMAL);
            alertMessage->set_text("Register successful! Try Login.");
            nameInput->set_text("");
            emailInput->set_text("");
            passwordInput->set_text("");
            passwordConfirmationInput->set_text("");
            break;
        case 400:
            alertMessage->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
            alertMessage->set_text(json["error"]);
            break;
        default:
            alertMessage->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
            alertMessage->set_text("Something went wrong! Check form.");
    }
}

void RegisterWindow::show_window() {
    builderRef->get_widget("register_window", window);
    builderRef->get_widget("register_alert_message", alertMessage);
    if (window) {

        /*Name Input*/
        builderRef->get_widget("register_name_input", nameInput);
        if (nameInput) {
            nameInput->signal_changed().connect(sigc::mem_fun(*this, &RegisterWindow::on_name_change));
        }
        std::cout << nameInput << std::endl;

        /*Email Input*/
        builderRef->get_widget("register_email_input", emailInput);
        if (emailInput) {
            emailInput->signal_changed().connect(sigc::mem_fun(*this, &RegisterWindow::on_email_change));
        }

        /*Password Input*/
        builderRef->get_widget("register_password_input", passwordInput);
        if (passwordInput) {
            passwordInput->signal_changed().connect(sigc::mem_fun(*this, &RegisterWindow::on_password_change));
        }

        /*Password Confirmation Input*/
        builderRef->get_widget("register_password_confirmation_input", passwordConfirmationInput);
        if (passwordConfirmationInput) {
            passwordConfirmationInput->signal_changed().connect(
                    sigc::mem_fun(*this, &RegisterWindow::on_password_confirmation_change));
        }

        /*RegisterWindow Button*/
        builderRef->get_widget("register_register_button", registerButton);
        if (registerButton) {
            registerButton->signal_clicked().connect(sigc::mem_fun(*this, &RegisterWindow::on_register_clicked));
        }

        window->show_all_children();
        window->show();
    }
}