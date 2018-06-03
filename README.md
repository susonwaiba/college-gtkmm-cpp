# LPSS CHAT APP

button->signal_clicked().connect(sigc::ptr_fun(on_close_clicked));

void on_close_clicked() {
    if (window)
        window->hide();
}