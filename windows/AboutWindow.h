//
// Created by suson on 5/16/18.
//

#ifndef CHAT_ABOUT_H
#define CHAT_ABOUT_H

#include <gtkmm.h>
#include "MainWindow.h"

class AboutWindow : public MainWindow {
private:
    Gtk::Window *window = nullptr;
public:
    void show_window();
};


#endif //CHAT_ABOUT_H
