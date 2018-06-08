//
// Created by suson on 5/19/18.
//

#include <cpr/cpr.h>
#include <json.hpp>
#include "AddFriendWindow.h"
#include "../include/Config.h"

AddFriendWindow::AddFriendWindow() {
    token = "";
    email = "";
}

void AddFriendWindow::set_values(std::string token_in) {
//    homeRef = homeRef_in;
    token = token_in;
}

void AddFriendWindow::on_email_change() {
    email = emailInput->get_text();
}

void AddFriendWindow::on_say_hi_clicked() {
    Config config;
    auto response = cpr::Post(
            cpr::Url{config.api_url + "chats/say-hi"},
            cpr::Payload{{"email", email}},
            cpr::Header{{"Authorization", "Bearer " + token}}
    );
    auto json = nlohmann::json::parse(response.text);
    int status = json["status"];
    switch (status) {
        case 1: {
            alert->override_color(Gdk::RGBA("green"), Gtk::STATE_FLAG_NORMAL);
            alert->set_text("Message send successfully!");
            emailInput->set_text("");
            int id = json["user_id"];
            std::string name = json["user_name"];
//            homeRef->sayHi(name, id);
            break;
        }
        case 0: {
            alert->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
            alert->set_text(json["message"]);
            break;
        }
        default: {

        }
    }
}

void AddFriendWindow::show_window() {
    builderRef->get_widget("add_friend_window", window);
    if (window) {

        builderRef->get_widget("add_friend_alert", alert);

        builderRef->get_widget("add_friend_email", emailInput);
        if (emailInput) {
            emailInput->signal_changed().connect(sigc::mem_fun(*this, &AddFriendWindow::on_email_change));
        }

        builderRef->get_widget("add_friend_say_hi", sayHi);
        if (sayHi) {
            sayHi->signal_clicked().connect(sigc::mem_fun(*this, &AddFriendWindow::on_say_hi_clicked));
        }

        window->show_all_children();
        window->show();
    }
}