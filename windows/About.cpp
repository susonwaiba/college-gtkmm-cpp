//
// Created by suson on 5/16/18.
//

#include "About.h"

void About::show_window() {
    builderRef->get_widget("about_window", window);
    if (window) {
        window->show_all_children();
        window->show();
    }
}