#pragma once

#include <iostream>
#include <QWidget>
#include <QLabel>

/**
 * @brief Das InformationWidget dient zur Ausgabe des Spielstatuses
 */
class InformationWidget : public QWidget
{
    Q_OBJECT

private:
    /**
     * @brief QLabel zur Ausgabe des Punktestandes
     */
    QLabel *m_scores;

    /**
     * @brief QLabel zur Ausgabe der Anzahl der im Deck verbleibenden Karten
     */
    QLabel *m_deckLength;

    /**
     * @brief QLabel zur Ausgabe der Spieleranzahl
     */
    QLabel *m_playerCount;

public:
    /**
     * @brief Konstruktor zum Erzeugen einer InformationWidget-Instanz
     * @param parent Elternteil des InformationWidgets
     */
    explicit InformationWidget(QWidget *parent = 0);

    /**
     * @brief Legt die Anzahl der Spieler fest
     * @param p_playerCount Spieleranzahl
     * @see m_playerCount
     */
    void setPlayerCount(short p_playerCount);

    /**
     * @brief Legt die Anzahl der Karten im Deck fest
     * @param p_deckLength Anzahl der Karten im Deck
     * @see m_deckLength
     */
    void setDeckLength(short p_deckLength);

    /**
     * @brief Legt den Inhalt des Scoreboards fest
     * @param p_scores Punktestand
     * @see m_scores
     */
    void setScores(QByteArray p_scores);

};
