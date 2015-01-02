#pragma once

#include <list>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>

namespace Ui {
    class Window;
}

#include "card.hpp"
#include "informationwidget.hpp"

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
    std::list<Card*> m_field;
    InformationWidget *infoWidget;

protected:
    void closeEvent(QCloseEvent *p_closeEvent);
    void keyPressEvent(QKeyEvent *p_keyEvent);

public:
    std::list<std::tuple<Player*, Qt::Key>> m_players;
    static Window *getInstance();

public slots:
    void cardClicked();
    void retrieveField(QByteArray p_field);
    void retrieveWaitTime(unsigned int p_waitTime);
    void retrieveDeckLength(short p_deckLength);
    void retrieveScores(QByteArray p_scores);

signals:
    void unselectAll();
    void canClick(bool p_val);

};

#include "player.hpp"
