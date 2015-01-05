#include <QApplication>
#include "setupwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetupWindow setupWindow;
    setupWindow.show();
    //Window::getInstance()->show();
    //new Controller(Window::getInstance());
    //Player *p = new Player(Window::getInstance());
    //if(p->waitForConnected())
    //    Window::getInstance()->m_players.push_back(std::make_tuple(p, Qt::Key_Space));
    return a.exec();
}
