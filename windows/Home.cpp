//
// Created by suson on 5/9/18.
//

#include <iostream>
#include <thread>
#include <gtkmm.h>
#include <fstream>
#include <cpr/cpr.h>
#include <json.hpp>
#include "Home.h"
#include "../include/Config.h"

Home::Home(std::string token_in, int current_user_id_in, std::string current_user_name_in) {
    token = token_in;
    current_user_id = current_user_id_in;
    current_user_name = current_user_name_in;
    current_chat_user_id = 0;
    message = "";
    last_message_id = 0;
    friend_sync_timer = 0;
    current_friend_color_count = 0;
}

void Home::circulate_friend(std::string name, int user_id) {
    if (friend_layout_counter < friendCount) {
        home_friends_box_row->remove(*friend_layout[friend_layout_counter]);
        friend_layout_name[friend_layout_counter]->set_label(name);
        friend_layout_id[friend_layout_counter] = user_id;
        home_friends_box_row->add(*friend_layout[friend_layout_counter]);
        friend_layout_counter++;
    } else {
        friend_layout_counter = 0;
        this->circulate_friend(name, user_id);
    }
}

void Home::circulate_message(std::string name, std::string message, std::string color) {
    if (message_layout_counter < messageCount) {
        home_message_box_row->remove(*message_layout[message_layout_counter]);
        message_layout[message_layout_counter]->set_label(name + ": " + message);
        message_layout[message_layout_counter]->override_color(Gdk::RGBA(color), Gtk::STATE_FLAG_NORMAL);
        home_message_box_row->add(*message_layout[message_layout_counter]);
        message_layout_counter++;
    } else {
        message_layout_counter = 0;
        this->circulate_message(name, message, color);
    }
}

void Home::on_logout_button_clicked() {
    Config config;
    std::ofstream authFile;
    authFile.open(config.auth_file);
    authFile << "";
    authFile.close();
    window->hide();
    system("./Chat &");
}

void Home::on_about_button_clicked() {
    aboutRef.init(appRef, builderRef);
    aboutRef.show_window();
}

void Home::on_home_add_friend_clicked() {
    addFriendRef.init(appRef, builderRef);
    addFriendRef.show_window();
}

void Home::sync_friend_list() {
    Config config;
    auto response = cpr::Get(
            cpr::Url{config.api_url + "chats"},
            cpr::Header{{"Authorization", "Bearer " + token}}
    );
    auto json = nlohmann::json::parse(response.text);
    for (nlohmann::json::iterator it = json["data"].begin(); it != json["data"].end(); ++it) {
        std::string friend_name = it.value()["friend"]["name"];
        int friend_id = it.value()["friend"]["id"];
        if (current_chat_user_id == 0) {
            current_chat_user_id = friend_id;
            current_chat_user_name = friend_name;
            home_friend_name->set_text(current_chat_user_name);
//            this->sync_message();
        }
        this->circulate_friend(friend_name, friend_id);
    }
}

void Home::on_send_button_clicked() {
    if (current_chat_user_id == 0) {
        return;
    }
    Config config;
    auto response = cpr::Post(
            cpr::Url{config.api_url + "chats/add/" + std::to_string(current_chat_user_id)},
            cpr::Payload{{"message", message}},
            cpr::Header{{"Authorization", "Bearer " + token}}
    );
    auto json = nlohmann::json::parse(response.text);
    int status = json["status"];
    switch (status) {
        case 1: {
            home_message_input->set_text("");
            break;
        }
        default: {

        }
    }
}

void Home::on_message_change() {
    message = home_message_input->get_text();
}

void Home::on_friend_message_clicked(int position) {
    current_chat_user_id = friend_layout_id[position];
    current_chat_user_name = friend_layout_name[position]->get_text();
    home_friend_name->set_text(current_chat_user_name);
    last_message_id = 0;
    for (int i = 1; i <= messageCount; i++) {
        home_message_box_row->remove(*message_layout[i - 1]);
    }
}

void Home::sync_message() {
    Config config;
    auto response = cpr::Get(
            cpr::Url{config.api_url + "chats/messages/" + std::to_string(current_chat_user_id) + "/" +
                     std::to_string(last_message_id)},
            cpr::Header{{"Authorization", "Bearer " + token}}
    );
    auto json = nlohmann::json::parse(response.text);

    last_message_id = json["last_id"];
    if (json["data_count"] > 0) {
        for (nlohmann::json::iterator it = json["data"].begin(); it != json["data"].end(); ++it) {
            std::string message_text = it.value()["message"];
            int message_user_id = it.value()["user_id"];
            if (message_user_id == current_user_id) {
                this->circulate_message(current_user_name, message_text, "blue");
            } else {
                this->circulate_message(current_chat_user_name, message_text, "black");
            }
        }
    }

}

void Home::sync_worker_thread() {
    while(true) {
        sleep(1);
        dispatcher.emit();
    }
}

void Home::on_notification_from_worker_thread() {
    if (friend_sync_timer == 20) {
        for (int i = 1; i <= friendCount; i++) {
            home_friends_box_row->remove(*friend_layout[i - 1]);
        }
        this->sync_friend_list();
        friend_sync_timer = 0;
    }

    home_friend_name->override_color(Gdk::RGBA(current_friend_colors[current_friend_color_count++]), Gtk::STATE_FLAG_NORMAL);
    if (current_friend_color_count > 1) {
        current_friend_color_count = 0;
    }
    this->sync_message();
    friend_sync_timer++;
}

void Home::show_window() {
    builderRef->get_widget("home_window", window);

    if (window) {
        builderRef->get_widget("home_user_name", home_user_name);
        if (home_user_name) {
            home_user_name->set_text(current_user_name);
        }

        dispatcher.connect(sigc::mem_fun(*this, &Home::on_notification_from_worker_thread));

        builderRef->get_widget("home_message_box", home_message_box);

        builderRef->get_widget("home_friend_name", home_friend_name);

        builderRef->get_widget("home_friends_box_row", home_friends_box_row);
        builderRef->get_widget("home_message_box_row", home_message_box_row);

        for (int i = 1; i <= friendCount; i++) {
            builderRef->get_widget("friend_layout_" + std::to_string(i), friend_layout[i - 1]);
            home_friends_box_row->remove(*friend_layout[i - 1]);
        }

        for (int i = 1; i <= friendCount; i++) {
            builderRef->get_widget("friend_layout_name_" + std::to_string(i), friend_layout_name[i - 1]);
        }

        for (int i = 1; i <= friendCount; i++) {
            builderRef->get_widget("friend_layout_button_" + std::to_string(i), friend_layout_button[i - 1]);
            friend_layout_button[i - 1]->signal_clicked().connect(sigc::bind<-1, int>(
                    sigc::mem_fun(*this, &Home::on_friend_message_clicked), i-1));
        }

        for (int i = 1; i <= messageCount; i++) {
            builderRef->get_widget("message_layout_" + std::to_string(i), message_layout[i - 1]);
            home_message_box_row->remove(*message_layout[i - 1]);
        }

        builderRef->get_widget("home_friend_name", home_friend_name);

        builderRef->get_widget("home_about_button", aboutButton);
        if (aboutButton) {
            aboutButton->signal_clicked().connect(sigc::mem_fun(*this, &Home::on_about_button_clicked));
        }

        builderRef->get_widget("home_logout_button", logoutButton);
        if (logoutButton) {
            logoutButton->signal_clicked().connect(sigc::mem_fun(*this, &Home::on_logout_button_clicked));
        }

        builderRef->get_widget("home_add_friend", home_add_friend);
        if (home_add_friend) {
            home_add_friend->signal_clicked().connect(sigc::mem_fun(*this, &Home::on_home_add_friend_clicked));
        }

        builderRef->get_widget("home_message_input", home_message_input);
        if (home_message_input) {
            home_message_input->signal_changed().connect(sigc::mem_fun(*this, &Home::on_message_change));
        }

        builderRef->get_widget("home_message_send_button", home_message_send_button);
        if (home_message_send_button) {
            home_message_send_button->signal_clicked().connect(sigc::mem_fun(*this, &Home::on_send_button_clicked));
        }

        this->sync_friend_list();

        Glib::RefPtr<Gtk::Adjustment> home_message_box_adj = home_message_box->get_vadjustment();
        home_message_box_adj->set_value(home_message_box_adj->get_upper());

        Glib::Thread::create(sigc::mem_fun(*this, &Home::sync_worker_thread), true);

        window->show_all_children();
        appRef->run(*window);

    }
}
