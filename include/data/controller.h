#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "window.h"
#include "stdlib.h"
#include "time.h"

class Controller;

#include "card.h"

/**
 * @brief Steuerklasse zum Aufbau des Spiels
 */
class Controller
{

private:
    /**
     * @brief Fenster
     */
    Window w;

    /**
     * @brief Pointer auf Karte in der Deckliste
     */
    Card* m_deckCard;

    /**
     * @brief Liste der Karten, die bei den Spielern in Besitz sind
     */
    std::vector<Card*> m_playerCards;

    /**
     * @brief Pointer auf Karte auf dem Spielfeld
     */
    Card* m_field;

    /**
     * @brief Größe des Decks
     */
    short decklength;


public:
    /**
     * @brief Konstruktor zum Erzeugen der Steuer-Klasse
     */
    Controller();

    /**
     * @brief Zeigt alle Karten an
     */
    void displayCards();

    /**
     * @brief Prüft ob 3 Karten ein Set bilden
     * @param a Karte 1
     * @param b Karte 2
     * @param c Karte 3
     * @return Wahrheitswert der angibt, ob es sich bei den 3 Karten um ein Set handelt,<BR>
     * oder halt eben nicht
     */
    bool check(Card &a, Card &b, Card &c);

    /**
     * @brief Gibt einen Pointer auf das Spielfeld zurück
     * @return Pointer auf Spielfeld
     */
    Card* getField();

    /**
     * @brief Fügt eine Karte ins Decke ein
     * @param a Karte die eingefügt werden soll
     */
    void insertDeckCard(Card &a);

    /**
     * @brief Zieht eine zufällige Karte vom Deck
     */
    void draw();

};

#endif // CONTROLLER_H

