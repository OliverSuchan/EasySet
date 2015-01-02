#include "informationwidget.hpp"

InformationWidget::InformationWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(210, 720);

    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, SIGNAL(timeout()), this, SLOT(showCountDown()));
    m_refreshTimer->start(1000);

    QFont font;
    font.setBold(true);
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSize(8);

    m_playerNum = new QLabel(this);
    m_playerNum->move(20, 20);
    m_playerNum->setFont(font);
    m_playerNum->show();
    setPlayerNumber(0);

    m_playerCount = new QLabel(this);
    m_playerCount->move(20, m_playerNum->y() + 40);
    m_playerCount->setFont(font);
    m_playerCount->show();
    setPlayerCount(0);

    m_deckLength = new QLabel(this);
    m_deckLength->move(20, m_playerCount->y() + 40);
    m_deckLength->setFont(font);
    m_deckLength->show();
    setDeckLength(0);

    m_scores = new QLabel(this);
    m_scores->move(20, m_deckLength->y() + 40);
    m_scores->setFont(font);
    m_scores->show();

    /*  Test
    l.push_back(2);
    l.push_back(7);
    l.push_back(5);*/


    // Timer

    /*m_waitTime = new QLCDNumber(this);

    m_waitTime->setSegmentStyle(QLCDNumber::Flat);
    m_waitTime->show();
    m_waitTime->move((this->width() - m_waitTime->width()) / 2, m_deckLength->y() + 30);
    m_waitTime->setGeometry(m_waitTime->x(), m_waitTime->y(), m_waitTime->width(), 50);*/
}

void InformationWidget::setPlayerNumber(int p_number)
{
    if(p_number)
    {
        m_playerNum->setText("Spieler " + QString::number(p_number) + " ist am Zug");
    }
    else
        m_playerNum->setText("Kein Spieler am Zug!");

    m_playerNum->adjustSize();
}

void InformationWidget::setPlayerCount(short p_score)
{
    m_playerCount->setText("Anzahl Spieler: " + QString::number(p_score));
    m_playerCount->adjustSize();
}

void InformationWidget::setDeckLength(short p_deckLength)
{
    m_deckLength->setText("Anzahl der Karten im Deck: " + QString::number(p_deckLength));
    m_deckLength->adjustSize();
}

void InformationWidget::setWaitTimeValue(int p_value)
{
    m_startValue = p_value;
    m_currentValue = m_startValue;
}

void InformationWidget::restartTimer()
{
    m_currentValue = m_startValue;
}

void InformationWidget::showCountDown()
{
    /*QTime curTime = QTime(0, m_currentValue / 60, m_currentValue % 60);
    QString text = curTime.toString("mm:ss");
    m_waitTime->display(text);
    m_currentValue--;
    if(m_currentValue <= 0)
        m_currentValue = m_startValue;*/
}
void InformationWidget::setScores(QByteArray p_scores)
{
    short c = 1;
    scoreboard = "Scoreboard: \n\n\n";
    for(auto it = p_scores.begin(); it != p_scores.end(); ++it) {
        scoreboard += ("Spieler " + QString::number(c) + ":        " + QString::number(*it) + "\n\n");
        c++;
    }
    m_scores->setText(scoreboard);
    m_scores->adjustSize();
}
