//
// Created by suson on 5/9/18.
//

#ifndef CHAT_HOME_H
#define CHAT_HOME_H

#include <gtkmm.h>
#include "Main.h"
#include "About.h"
#include "AddFriend.h"

#define messageCount 30
#define friendCount 30

class Home : public Main {
protected:
    std::string token;
    int current_user_id;
    std::string current_user_name;
    int current_chat_user_id;
    std::string current_chat_user_name;

    Gtk::Window *window = nullptr;
    Gtk::ScrolledWindow *home_message_box = nullptr;
    Gtk::Box *home_friends_box_row = nullptr;
    Gtk::Box *home_message_box_row = nullptr;

    /*For Menu Option*/
    Gtk::Label *home_user_name = nullptr;
    Gtk::Button *logoutButton = nullptr;
    About aboutRef;
    Gtk::Button *aboutButton = nullptr;
    AddFriend addFriendRef;

    Gtk::Button *home_add_friend = nullptr;

    /*For Message List*/
    Gtk::Label *message_layout[messageCount];
    int message_layout_counter = 0;

    /*For Friend List*/
    Gtk::Box *friend_layout[friendCount];
    int friend_layout_counter = 0;
    Gtk::Label *friend_layout_name[friendCount];
    Gtk::Button *friend_layout_button[friendCount];
    int friend_layout_id[friendCount];

    /*For Chat Box*/
    Gtk::Label *home_friend_name = nullptr;
    Gtk::Entry *home_message_input = nullptr;
    Gtk::Button *home_message_send_button = nullptr;
    std::string message;
public:
    Home(std::string token_in, int current_user_id_in, std::string current_user_name_in);

    void circulate_friend(std::string name, int user_id);

    void circulate_message(std::string name, std::string message, std::string color);

    void on_logout_button_clicked();

    void on_about_button_clicked();

    void on_home_add_friend_clicked();

    void sync_friend_list();

    void sync_message();

    void on_send_button_clicked();

    void on_message_change();

    void sync_message_thread();

    void sync_friend_thread();

    void show_window();
};


#endif //CHAT_HOME_H
