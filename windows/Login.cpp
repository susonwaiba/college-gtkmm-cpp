//
// Created by suson on 5/9/18.
//

#include <cpr/cpr.h>
#include <json.hpp>
#include <fstream>
#include "../include/Config.h"
#include "Login.h"

Login::Login() {
    email = "";
    password = "";
};

void Login::on_email_change() {
    email = emailInput->get_text();
}

void Login::on_password_change() {
    password = passwordInput->get_text();
}

void Login::on_login_clicked() {
    Config config;
    std::ofstream authFile;
    auto response = cpr::Post(cpr::Url{config.base_url + "oauth/token"}, cpr::Payload{
            {"grant_type",    config.grant_type},
            {"client_id",     config.client_id},
            {"client_secret", config.client_secret},
            {"username",      email},
            {"password",      password},
            {"scope",         "*"},
    });
    auto json = nlohmann::json::parse(response.text);
    switch (response.status_code) {
        case 200: {
            alertMessage->override_color(Gdk::RGBA("green"), Gtk::STATE_FLAG_NORMAL);
            alertMessage->set_text("Login successful!");
            authFile.open(config.auth_file);
            authFile << std::setw(4) << json << std::endl;
            authFile.close();

            window->hide();
            system("./Chat &");

            break;
        }
        case 401: {
            alertMessage->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
            alertMessage->set_text(json["message"]);
            break;
        }
        default: {
            alertMessage->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
            alertMessage->set_text("Something went wrong! Check form.");
        }
    }
}

void Login::on_register_clicked() {
    registerRef.init(appRef, builderRef);
    registerRef.show_window();
}

void Login::show_window() {
    builderRef->get_widget("login_window", window);
    builderRef->get_widget("login_alert_message", alertMessage);
    if (window) {

        builderRef->get_widget("login_email_input", emailInput);
        if (emailInput) {
            emailInput->signal_changed().connect(sigc::mem_fun(*this, &Login::on_email_change));
        }

        builderRef->get_widget("login_password_input", passwordInput);
        if (passwordInput) {
            passwordInput->signal_changed().connect(sigc::mem_fun(*this, &Login::on_password_change));
        }

        builderRef->get_widget("login_login_button", loginButton);
        if (loginButton) {
            loginButton->signal_clicked().connect(sigc::mem_fun(*this, &Login::on_login_clicked));
        }

        builderRef->get_widget("login_register_button", registerButton);
        if (registerButton) {
            registerButton->signal_clicked().connect(sigc::mem_fun(*this, &Login::on_register_clicked));
        }

        window->show_all_children();
        appRef->run(*window);
    }
}
