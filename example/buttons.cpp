//
// Created by suson on 5/9/18.
//

#include "buttons.h"
#include <iostream>

buttons::buttons()
{
    m_button.add_pixlabel("info.xpm", "cool button");

    set_title("Pixmap'd buttons!");
    set_border_width(10);

    m_button.signal_clicked().connect( sigc::mem_fun(*this,
                                                     &buttons::on_button_clicked) );

    add(m_button);

    show_all_children();
}

buttons::~buttons()
{
}

void buttons::on_button_clicked()
{
    std::cout << "The Button was clicked." << std::endl;
}