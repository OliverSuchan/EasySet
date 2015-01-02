#include "informationwidget.hpp"

InformationWidget::InformationWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(210, 180);

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

    m_curScore = new QLabel(this);
    m_curScore->move(20, m_playerNum->y() + 40);
    m_curScore->setFont(font);
    m_curScore->show();
    setScore(0);

    m_deckLength = new QLabel(this);
    m_deckLength->move(20, m_curScore->y() + 40);
    m_deckLength->setFont(font);
    m_deckLength->show();
    setDeckLength(0);

    m_waitTime = new QLCDNumber(this);

    m_waitTime->setSegmentStyle(QLCDNumber::Flat);
    m_waitTime->show();
    m_waitTime->move((this->width() - m_waitTime->width()) / 2, m_deckLength->y() + 30);
    m_waitTime->setGeometry(m_waitTime->x(), m_waitTime->y(), m_waitTime->width(), 50);
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

void InformationWidget::setScore(short p_score)
{
    m_curScore->setText("Ihr Punktestand: " + QString::number(p_score));
    m_curScore->adjustSize();
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
    QTime curTime = QTime(0, m_currentValue / 60, m_currentValue % 60);
    QString text = curTime.toString("mm:ss");
    m_waitTime->display(text);
    m_currentValue--;
    if(m_currentValue <= 0)
        m_currentValue = m_startValue;
}
