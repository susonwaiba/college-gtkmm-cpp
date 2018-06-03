//
// Created by suson on 5/6/18.
//

#ifndef CHAT_GLOABL_H
#define CHAT_GLOABL_H

#include <gtkmm.h>

class App {
protected:
    Glib::RefPtr<Gtk::Application> app;
    Glib::RefPtr<Gtk::Builder> builder;
public:
    void init(const Glib::RefPtr<Gtk::Application> &refApp, const Glib::RefPtr<Gtk::Builder> &refBuilder) {
        app = refApp;
        builder = refBuilder;
    }
};


#endif //CHAT_GLOABL_H
