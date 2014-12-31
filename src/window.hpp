#pragma once

#include <list>
#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
    class Window;
}

#include "card.hpp"

class Player;


class Window : public QMainWindow
{
    Q_OBJECT

private:
    std::list<Card*> m_clickedCards;
    Player *m_curPlayer;
    explicit Window(QWidget *parent = 0);
    ~Window();
    Window& operator=(Window&) = delete;
    Ui::Window *ui;
    std::list<std::unique_ptr<Card>> m_field;

protected:
    void keyPressEvent(QKeyEvent *p_keyEvent);

public:
    std::list<std::tuple<Player*, Qt::Key>> m_players;
    static Window *getInstance();

public slots:
    void cardClicked();
    void retrieveField(QByteArray p_field);

signals:
    void unselectAll();
    void canClick(bool p_val);

};

#include "player.hpp"
