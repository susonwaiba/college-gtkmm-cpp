//
// Created by suson on 5/9/18.
//

#ifndef CHAT_MAIN_H
#define CHAT_MAIN_H

#include <gtkmm.h>

class MainWindow {
protected:
    Glib::RefPtr<Gtk::Application> appRef;
    Glib::RefPtr<Gtk::Builder> builderRef;
public:
    void init(const Glib::RefPtr<Gtk::Application> &app, const Glib::RefPtr<Gtk::Builder> &builder);
};


#endif //CHAT_MAIN_H
