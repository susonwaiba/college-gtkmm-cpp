//
// Created by suson on 5/9/18.
//

#ifndef CHAT_BUTTONS_H
#define CHAT_BUTTONS_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>

class buttons : public Gtk::Window {
public:
    buttons();

    virtual ~buttons();

protected:
    //Signal handlers:
    void on_button_clicked();

    //Child widgets:
    Gtk::Button m_button;
};


#endif //CHAT_BUTTONS_H
