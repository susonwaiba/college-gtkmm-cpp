//
// Created by suson on 5/9/18.
//

#include "Main.h"

void Main::init(const Glib::RefPtr<Gtk::Application> &app, const Glib::RefPtr<Gtk::Builder> &builder) {
    appRef = app;
    builderRef = builder;
}