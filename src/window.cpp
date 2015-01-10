#include "window.hpp"
#include "ui_window.h"

Window &Window::getInstance()
{
    static Window winInstance;
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

void Window::retrieveUnlock()
{
    m_inputLocked.store(false);
    m_layer->hide();
    this->setFocus();
    if(m_curPlayer)
    {
        m_layer->setPalette(QPalette(QColor(255, 200, 200, 125)));
        m_layer->show();
        m_layer->lower();
    }
}

void Window::retrieveLock()
{
    static const void * sentBy = sender();
    if(sentBy != sender())
        return;
    m_inputLocked.store(true);
    m_layer->show();
    m_layer->raise();
    m_layer->setPalette(QPalette(QColor(0, 0, 0, 125)));
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
        m_layer->hide();
        emit unselectAll();
        emit canClick(false);
    }
}

void Window::clientDisconnected()
{
    static const void * sentBy = sender();
    if(sentBy != sender())
        return;
    QMessageBox::information(this, "Verbindungsfehler", "Die Verbindung zwischen Server und Client wurde getrennt.");
}

void Window::retrieveField(QByteArray p_field)
{
    static const void * sentBy = sender();
    if(sentBy != sender())
        return;
    m_curPlayer = nullptr;
    for(auto it = m_field.begin(); it != m_field.end(); ++it)
    {
        CardWidget *curCard = static_cast<CardWidget*>(*it);
        delete curCard;
        curCard = nullptr;
    }
    m_field.clear();
    int mod = (p_field.size() > 12) ? (5) : (4);
    for(auto it = p_field.begin(); it != p_field.end(); ++it)
    {
        CardWidget *cardWidget = new CardWidget((*it >> 6) & 0x03, (*it >> 4) & 0x03, (*it >> 2) & 0x03, *it & 0x03, this);
        m_field.push_back(cardWidget);
        cardWidget->setGeometry(((m_field.size() -1) % mod) * 110 + 20, ((m_field.size() - 1) / mod) * 220 + 20, 90, 200);
        cardWidget->show();
        connect(cardWidget, SIGNAL(clicked()), this, SLOT(cardClicked()));
        connect(this, SIGNAL(canClick(bool)), cardWidget, SLOT(canClick(bool)));
        connect(this, SIGNAL(unselectAll()), cardWidget, SLOT(unselect()));
    }
    CardWidget *someCard = static_cast<CardWidget*>(m_field.back());
    m_infoWidget->move(someCard->width() * mod + 20 * mod + 20, 0);
    int infoWidgetHeight = m_infoWidget->y() + m_infoWidget->height() + 20;
    int cardWidgetHeight = someCard->y() + someCard->height() + 20;
    this->setFixedSize(m_infoWidget->x() + m_infoWidget->width() + 20, (infoWidgetHeight > cardWidgetHeight) ? (infoWidgetHeight) : (cardWidgetHeight));
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    m_layer->setGeometry(0, 0, m_infoWidget->x(), someCard->y() + someCard->height() + 20);
    m_layer->raise();
    m_startButton->move((m_layer->width() - m_startButton->width()) / 2, (m_layer->height() - m_startButton->height()) / 2);
    emit canClick(false);
}

void Window::retrieveDeckLength(short p_deckLength)
{
    m_infoWidget->setDeckLength(p_deckLength);
}
void Window::retrieveScores(QByteArray p_scores)
{
    m_infoWidget->setScores(p_scores);
    m_infoWidget->setPlayerCount(p_scores.size());
}

void Window::retrieveGameStarted()
{
    m_layer->hide();
    m_startButton->hide();
    this->setFocus();
}

void Window::retrieveGameFinished()
{
    emit canClick(false);
    m_inputLocked.store(true);
    QMessageBox::information(this, "Ende!", "Das Spiel ist vorbei - es gibt keine Sets mehr");
    this->close();
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
    m_infoWidget = new InformationWidget(this);
    m_infoWidget->show();
    m_layer = new QWidget(this);
    m_layer->setAutoFillBackground(true);
    m_layer->setPalette(QPalette(QColor(0, 0, 0, 125)));
    m_layer->show();
    m_startButton = new QPushButton(m_layer);
    m_startButton->setStyleSheet("QPushButton {color: red;}");
    m_startButton->setText("Start!");
    m_startButton->hide();
    m_inputLocked.store(false);
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
            if(!m_curPlayer && !m_inputLocked.load())
            {
                m_curPlayer = std::get<0>(*it);
                m_curPlayer->sendTurnPacket();
                emit canClick(true);
            }
        }
    }
}

