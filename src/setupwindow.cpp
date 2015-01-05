#include "src/setupwindow.hpp"
#include "ui_setupwindow.h"

SetupWindow::SetupWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetupWindow)
{
    ui->setupUi(this);
}

SetupWindow::~SetupWindow()
{
    delete ui;
}

void SetupWindow::on_commandLinkButton_2_clicked()
{
    this->close();
}

void SetupWindow::on_stackedWidget_currentChanged(int arg1)
{
    if(arg1 > 0)
        ui->commandLinkButton->setEnabled(true);
    else
        ui->commandLinkButton->setEnabled(false);
}

void SetupWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void SetupWindow::on_commandLinkButton_clicked()
{
    if(ui->stackedWidget->currentIndex() == 3)
        ui->stackedWidget->setCurrentIndex(2);
    else
        ui->stackedWidget->setCurrentIndex(0);
}

void SetupWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void SetupWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void SetupWindow::on_pushButton_7_clicked()
{
    new Controller();
    Window::getInstance()->m_players.push_back(std::make_tuple(new Player(), Qt::Key_Space));
    Window::getInstance()->show();
    this->close();
}

void SetupWindow::on_pushButton_5_clicked()
{
    Player *p = new Player(nullptr, QHostAddress(ui->lineEdit->text()), ui->lineEdit_2->text().toInt());
    if(p->waitForConnected())
    {
        Window::getInstance()->m_players.push_back(std::make_tuple(p, Qt::Key_Space));
        Window::getInstance()->show();
        this->close();
    }
    else
        QMessageBox::information(this, "Fehler beim Verbinden", "Beim Verbinden mit dem Server ist ein Fehler aufgetreten.");
}
