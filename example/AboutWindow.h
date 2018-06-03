//
// Created by suson on 5/9/18.
//

#ifndef CHAT_ABOUTWINDOW_H
#define CHAT_ABOUTWINDOW_H

#include <gtkmm.h>

class AboutWindow : public Gtk::Window {
public:
    AboutWindow();
    ~AboutWindow();

protected:
    Gtk::Label lbl_;
};


#endif //CHAT_ABOUTWINDOW_H
