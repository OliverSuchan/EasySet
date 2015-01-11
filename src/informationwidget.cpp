#include "informationwidget.hpp"
//Konstruktor
InformationWidget::InformationWidget(QWidget *parent) :
    QWidget(parent)
{
    // erzeuge einen Font für die QLabel
    QFont font;
    font.setBold(true);
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSize(8);
    
    // erzeuge verschiedene QLabel mit dem Font zum Anzeigen von Informationen
    m_playerCount = new QLabel(this);   // Spieleranzahl
    m_playerCount->move(20, 20);
    m_playerCount->setFont(font);
    m_playerCount->show();
    setPlayerCount(0);

    m_deckLength = new QLabel(this);    // Decklänge
    m_deckLength->move(20, m_playerCount->y() + 40);
    m_deckLength->setFont(font);
    m_deckLength->show();
    setDeckLength(0);

    m_scores = new QLabel(this);        // Scoreboard
    m_scores->move(20, m_deckLength->y() + 40);
    m_scores->setFont(font);
    m_scores->show();

    this->setMinimumSize(210, m_scores->x() + m_scores->height() + 20);
}

// zeige die übergebene Spieleranzahl auf dem Label an
void InformationWidget::setPlayerCount(short p_score)
{
    m_playerCount->setText("Anzahl Spieler: " + QString::number(p_score));
    m_playerCount->adjustSize();
}

// zeige die übergebene Stapelgröße auf dem Label an
void InformationWidget::setDeckLength(short p_deckLength)
{
    m_deckLength->setText("Anzahl der Karten im Deck: " + QString::number(p_deckLength));
    m_deckLength->adjustSize();
}

// zeige die übergebenen Punkte auf einem Scoreboard-Label an
void InformationWidget::setScores(QByteArray p_scores)
{
    short c = 1;
    QString scoreBoard = "Scoreboard: \n\n\n"; // QString, der immer weiter verlängert wird
    for(auto it = p_scores.begin(); it != p_scores.end(); ++it) {
        scoreBoard += ("Spieler " + QString::number(c) + ":\t" + QString::number(*it) + "\n\n");
        c++;
    }
    m_scores->setText(scoreBoard);
    m_scores->adjustSize();
    this->setMinimumSize(m_deckLength->x() + m_deckLength->width() + 20, m_scores->y() + m_scores->height() + 20);
}
