//
// Created by suson on 5/9/18.
//

#include "MainWindow.h"
#include "AboutWindow.h"

MainWindow::MainWindow()
{
    this->set_default_size(100, 100);
    box_.set_orientation(Gtk::ORIENTATION_VERTICAL);
    this->add(box_);
    box_.pack_start(lbl_);

    lbl_.set_label("a test");

    button_.set_label("Open About Window");
    box_.pack_end(button_);

    button_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onButtonClicked));

    aboutw_ = 0;

    this->show_all_children();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onButtonClicked()
{
    if(aboutw_ != 0)
        return;

    aboutw_ = new AboutWindow;
    aboutw_->signal_hide().connect(sigc::mem_fun(*this, &MainWindow::aboutWinClose));
    aboutw_->show();
}

void MainWindow::aboutWinClose()
{
    aboutw_ = 0;
}
