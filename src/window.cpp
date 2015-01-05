#include "window.hpp"
#include "ui_window.h"

Window *Window::getInstance()
{
    static Window *winInstance = new Window;
    return winInstance;
}

void Window::clickStartButton()
{
    m_controller->sendGameStartedPacket();
}

void Window::retrieveShowStartButton()
{
    m_controller = static_cast<Controller*>(sender());
    m_startButton->show();
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(clickStartButton()));
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
    if(m_clickedCards.size() == 3)
    {
        QByteArray packet;
        for(auto it = m_clickedCards.begin(); it != m_clickedCards.end(); ++it)
        {
            packet.append(char(**it));
        }
        if(m_curPlayer)
            m_curPlayer->sendClickPacket(packet);
        m_clickedCards.clear();
        m_curPlayer = nullptr;
        emit unselectAll();
        emit canClick(false);
    }
}

void Window::retrieveField(QByteArray p_field)
{
    static const void * sentBy = sender();
    if(sentBy != sender())
        return;
    //infoWidget->restartTimer();
    for(auto it = m_field.begin(); it != m_field.end(); ++it)
    {
        CardWidget *curCard = static_cast<CardWidget*>(*it);
        delete curCard;
        curCard = nullptr;
    }
    m_field.clear();
    for(auto it = p_field.begin(); it != p_field.end(); ++it)
    {
        CardWidget *cardWidget = new CardWidget((*it >> 6) & 0x03, (*it >> 4) & 0x03, (*it >> 2) & 0x03, *it & 0x03, this);
        m_field.push_back(cardWidget);
        cardWidget->setGeometry(((m_field.size() -1) % 4) * 110 + 20, ((m_field.size() - 1) / 4) * 220 + 20, 90, 200);
        cardWidget->show();
        connect(cardWidget, SIGNAL(clicked()), this, SLOT(cardClicked()));
        connect(this, SIGNAL(canClick(bool)), cardWidget, SLOT(canClick(bool)));
        connect(this, SIGNAL(unselectAll()), cardWidget, SLOT(unselect()));
    }
    CardWidget *someCard = static_cast<CardWidget*>(m_field.back());
    infoWidget->move(someCard->width() * 4 + 20 * 4 + 20, 0);
    this->setFixedSize(infoWidget->x() + infoWidget->width() + 20, someCard->y() + someCard->height() + 20);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    m_layer->setGeometry(0, 0, someCard->x() + someCard->width() + 20, someCard->y() + someCard->height() + 20);
    m_layer->raise();
    m_startButton->move((someCard->x() + someCard->width() + 20 - m_startButton->width()) / 2, (someCard->y() + someCard->height() + 20 - m_startButton->height()) / 2);
    if(m_curPlayer)
        emit canClick(true);
    else
        emit canClick(false);
}

//void Window::retrieveWaitTime(unsigned int p_waitTime)
//{
//    static const void * sentBy = sender();
//    if(sentBy != sender())
//        return;
//    infoWidget->setWaitTimeValue(p_waitTime / 1000);
//}

void Window::retrieveDeckLength(short p_deckLength)
{
    infoWidget->setDeckLength(p_deckLength);
}
void Window::retrieveScores(QByteArray p_scores)
{
    infoWidget->setScores(p_scores);
}

void Window::retrieveGameStarted()
{
    std::cout << "game started" << std::endl;
    m_layer->hide();
}

void Window::retrieveGameFinished()
{
    std::cout << "game finished" << std::endl;
    emit canClick(false);
}

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window),
    m_field(),
    m_curPlayer(nullptr),
    m_controller(nullptr)
{
    ui->setupUi(this);
    m_players = std::list<std::tuple<Player*, Qt::Key>>();
    this->setWindowTitle("EasySet");
    this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    infoWidget = new InformationWidget(this);
    infoWidget->show();
    m_layer = new QFrame(this, Qt::WindowStaysOnTopHint);
    m_layer->setAutoFillBackground(true);
    m_layer->setPalette(QPalette(QColor(100, 100, 100, 100)));
    m_layer->show();
    m_startButton = new QPushButton(m_layer);
    m_startButton->setStyleSheet("QPushButton {color: red;}");
    m_startButton->setText("Start!");
    m_startButton->hide();
}

Window::~Window()
{
    delete ui;
}

void Window::closeEvent(QCloseEvent *p_closeEvent)
{
    QMessageBox::StandardButton reply = QMessageBox::warning(this, "Achtung!", "Sind Sie sich sicher, dass Sie das Spiel beenden wollen?\nDer Vorgang kann nicht rückgängig gemacht werden!", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        p_closeEvent->accept();
    else
        p_closeEvent->ignore();
}

void Window::keyPressEvent(QKeyEvent *p_keyEvent)
{
    for(auto it = m_players.begin(); it != m_players.end(); ++it)
    {
        if(std::get<1>(*it) == p_keyEvent->key())
        {
            if(!m_curPlayer)
            {
                m_curPlayer = std::get<0>(*it);
                emit canClick(true);
            }
        }
    }
}

