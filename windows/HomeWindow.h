//
// Created by suson on 5/9/18.
//

#ifndef CHAT_HOME_H
#define CHAT_HOME_H

#include <gtkmm.h>
#include "MainWindow.h"
#include "AboutWindow.h"
#include "AddFriendWindow.h"

#define messageCount 30
#define friendCount 30

class HomeWindow : public MainWindow {
protected:
    std::string token;
    int current_user_id;
    std::string current_user_name;
    int current_chat_user_id;
    std::string current_chat_user_name;

    int last_message_id;

    Gtk::Window *window = nullptr;
    Gtk::ScrolledWindow *home_message_box = nullptr;
    Gtk::Box *home_friends_box_row = nullptr;
    Gtk::Box *home_message_box_row = nullptr;

    /*For Menu Option*/
    Gtk::Label *home_user_name = nullptr;
    Gtk::Button *logoutButton = nullptr;
    AboutWindow aboutRef;
    Gtk::Button *aboutButton = nullptr;
    AddFriendWindow addFriendRef;

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

    Glib::Dispatcher dispatcher;
    Glib::Thread* message_sync_thread;

    int friend_sync_timer;

    int current_friend_color_count;
    std::string current_friend_colors[2] = {"green", "orange"};
public:
    HomeWindow(std::string token_in, int current_user_id_in, std::string current_user_name_in);

    void circulate_friend(std::string name, int user_id);

    void circulate_message(std::string name, std::string message, std::string color);

    void on_logout_button_clicked();

    void on_about_button_clicked();

    void on_home_add_friend_clicked();

    void sync_friend_list();

    void sync_message();

    void on_send_button_clicked();

    void on_message_change();

    void on_friend_message_clicked(int position);

    void sync_worker_thread();

    void on_notification_from_worker_thread();

    void sayHi(std::string name, int id);

    void show_window();
};


#endif //CHAT_HOME_H
