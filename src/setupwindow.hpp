#ifndef SETUPWINDOW_HPP
#define SETUPWINDOW_HPP

#include <iostream>
#include <QMainWindow>
#include "window.hpp"
#include "player.hpp"
#include "controller.hpp"

namespace Ui {
class SetupWindow;
}

class SetupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetupWindow(QWidget *parent = 0);
    ~SetupWindow();

private slots:
    void on_stackedWidget_currentChanged(int arg1);
    void on_commandLinkButton_clicked();
    void on_commandLinkButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::SetupWindow *ui;
};

#endif // SETUPWINDOW_HPP
