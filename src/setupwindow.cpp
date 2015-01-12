#include "src/setupwindow.hpp"
#include "ui_setupwindow.h"
int SetupWindow::getActualPlayerCount()
{
    int count = 0;
    for(int i = 0; i < ui->listWidget_3->count(); i++)
    {
        if(ui->listWidget_3->item(i)->text() != "-")
            count++;
    }
    return count;
}

SetupWindow::SetupWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SetupWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    for(int i = 1; i <= 8; i++)
    {
        ui->listWidget_2->addItem("Spieler "  + QString::number(i) + ": ");
        ui->listWidget_3->addItem("-");
    }
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
    ui->listWidget_2->setFocus();
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
    Window::getInstance().m_players.push_back(std::make_tuple(new Player(), Qt::Key_Space));
    Window::getInstance().show();
    this->close();
}

void SetupWindow::on_pushButton_5_clicked()
{
    Player *p = new Player(nullptr, QHostAddress(ui->lineEdit->text()), ui->lineEdit_2->text().toInt());
    if(p->waitForConnected())
    {
        Window::getInstance().m_players.push_back(std::make_tuple(p, Qt::Key_Space));
        Window::getInstance().show();
        this->close();
    }
    else
        QMessageBox::information(this, "Fehler beim Verbinden", "Beim Verbinden mit dem Server ist ein Fehler aufgetreten.");
}

void SetupWindow::on_pushButton_clicked()
{
    if(ui->listWidget_2->selectedItems().length() && ui->lineEdit_3->text().length())
    {
        for(int i = 0; i < ui->listWidget_3->count(); i++)
        {
            if(ui->listWidget_3->item(i)->text() == ui->lineEdit_3->text())
                return;
        }
        ui->listWidget_3->item(ui->listWidget_2->currentIndex().row())->setText(ui->lineEdit_3->text());
        ui->listWidget_2->setCurrentRow(ui->listWidget_2->currentIndex().row() + 1);
    }
    ui->lineEdit_3->clear();
}

void SetupWindow::on_pushButton_2_clicked()
{
    if( ui->listWidget_3->item(ui->listWidget_2->currentIndex().row())->text() == "#")
        ui->pushButton_9->setEnabled(true);
    ui->listWidget_3->item(ui->listWidget_2->currentIndex().row())->setText("-");
}

void SetupWindow::on_pushButton_8_clicked()
{
    if(getActualPlayerCount())
    {
        new Controller();
        for(int i = 0; i < ui->listWidget_3->count(); i++)
        {
            if(ui->listWidget_3->item(i)->text() != "-")
            {
                if(ui->listWidget_3->item(i)->text() == "#")
                {
                    KI *ki = new KI();
                    if(ki->waitForConnected())
                        Window::getInstance().m_players.push_back(std::make_tuple(ki, static_cast<Qt::Key>(-1)));
                }
                else
                {
                    Player *p = new Player();
                    if(p->waitForConnected())
                        Window::getInstance().m_players.push_back(std::make_tuple(p, static_cast<Qt::Key>(QKeySequence(ui->listWidget_3->item(i)->text())[0])));
                }
            }
        }
        Window::getInstance().show();
        this->close();
    }
    else
        QMessageBox::information(this, "Keine Spieler", "Dem Spiel wurden keine Spieler hinzugefügt.");
}

void SetupWindow::on_pushButton_9_clicked()
{
    ui->listWidget_3->item(ui->listWidget_2->currentIndex().row())->setText("#");
    ui->pushButton_9->setEnabled(false);
}
