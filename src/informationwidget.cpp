#include "informationwidget.hpp"

InformationWidget::InformationWidget(QWidget *parent) :
    QWidget(parent)
{
    QFont font;
    font.setBold(true);
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSize(8);

    m_playerCount = new QLabel(this);
    m_playerCount->move(20, 20);
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

    this->setMinimumSize(210, m_scores->x() + m_scores->height() + 20);
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

void InformationWidget::setScores(QByteArray p_scores)
{
    short c = 1;
    QString scoreBoard = "Scoreboard: \n\n\n";
    for(auto it = p_scores.begin(); it != p_scores.end(); ++it) {
        scoreBoard += ("Spieler " + QString::number(c) + ":\t" + QString::number(*it) + "\n\n");
        c++;
    }
    m_scores->setText(scoreBoard);
    m_scores->adjustSize();
    this->setMinimumSize(m_deckLength->x() + m_deckLength->width() + 20, m_scores->y() + m_scores->height() + 20);
}
