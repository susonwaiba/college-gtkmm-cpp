//
// Created by suson on 5/9/18.
//

#include "AboutWindow.h"

AboutWindow::AboutWindow()
{
    this->set_default_size(100, 100);
    this->set_title("About");

    lbl_.set_label("About label");
    this->add(lbl_);

    this->show_all_children();
}

AboutWindow::~AboutWindow()
{

}