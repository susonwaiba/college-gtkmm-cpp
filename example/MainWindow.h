//
// Created by suson on 5/9/18.
//

#ifndef CHAT_MAINWINDOW_H
#define CHAT_MAINWINDOW_H

#include <gtkmm.h>
#include "AboutWindow.h"

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    void onButtonClicked();
    void aboutWinClose();

    Gtk::Button button_;
    Gtk::Label lbl_;
    Gtk::Box box_;
    AboutWindow* aboutw_;
};


#endif //CHAT_MAINWINDOW_H
