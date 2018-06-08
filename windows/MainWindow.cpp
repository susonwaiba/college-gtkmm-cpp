//
// Created by suson on 5/9/18.
//

#include "MainWindow.h"

void MainWindow::init(const Glib::RefPtr<Gtk::Application> &app, const Glib::RefPtr<Gtk::Builder> &builder) {
    appRef = app;
    builderRef = builder;
}