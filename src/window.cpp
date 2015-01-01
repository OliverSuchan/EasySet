#include "window.hpp"
#include "ui_window.h"

Window *Window::getInstance()
{
    static Window *winInstance = new Window;
    return winInstance;
}

void Window::cardClicked()
{
    Card *clickedCard = dynamic_cast<Card*>(sender());
    for(auto it = m_clickedCards.begin(); it != m_clickedCards.end(); ++it)
    {
        if(*it == clickedCard)
        {
            m_clickedCards.remove(clickedCard);
            return;
        }
    }
    m_clickedCards.push_back(clickedCard);
    std::cout << char(*clickedCard) << std::endl;
    if(m_clickedCards.size() == 3)
    {
        m_curPlayer->sendClickPacket(m_clickedCards);
        m_clickedCards.clear();
        emit unselectAll();
        emit canClick(false);
    }
}

void Window::retrieveField(QByteArray p_field)
{
    static const void * sentBy = sender();
    if(sentBy != sender())
        return;
    m_field.clear();
    for(auto it = p_field.begin(); it != p_field.end(); ++it)
    {
        m_field.push_back(std::unique_ptr<Card>(new CardWidget((*it >> 6) & 0x03, (*it >> 4) & 0x03, (*it >> 2) & 0x03, *it & 0x03, this)));
        CardWidget *cardWidget = static_cast<CardWidget*>(m_field.back().get());
       cardWidget->setGeometry(((m_field.size() -1) % 4) * 110 + 20, ((m_field.size() - 1) / 4) * 220 + 20, 90, 200);
        cardWidget->show();
        connect(cardWidget, SIGNAL(clicked()), this, SLOT(cardClicked()));
        connect(this, SIGNAL(canClick(bool)), cardWidget, SLOT(canClick(bool)));
        connect(this, SIGNAL(unselectAll()), cardWidget, SLOT(unselect()));
    }
    emit canClick(false);
}

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window),
    m_field()
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *p_keyEvent)
{
    for(auto it = m_players.begin(); it != m_players.end(); ++it)
    {
        if(std::get<1>(*it) == p_keyEvent->key())
        {
            m_curPlayer = std::get<0>(*it);
            emit canClick(true);
        }
    }
}

