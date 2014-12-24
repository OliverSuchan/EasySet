#ifndef CARD_H
#define CARD_H

class Card;

#include "Controller.h"

/**
 * @brief Die Klasse Card ist das digitale pendant zu den analogen Karten<BR>
 *        zum Spiel Set.
 */
class Card
{
private:
    /**
     * @brief Farbe der Karte (0-2)
     */
    short m_color;

    /**
     * @brief Form der Karte (0-2)
     */
    short m_shape;

    /**
     * @brief Anzahl auf der Karte (0-2)
     */
    short m_number;

    /**
     * @brief Einfärbung der Karze (0-2)
     */
    short m_opacity;

    /**
     * @brief Pointer auf die nächste Karte
     */
    Card* m_nextCard;

    /**
     * @brief Pointer auf die vorherige Karte
     */
    Card* m_previousCard;

    friend class Controller;

public:
    /**
     * @brief Konstruktor zum Erzeugen einer Card-Instanz
     * @param p_color Farbe der zu erzeugenden Karte
     * @param p_shape Form der zu erzeugenden Karte
     * @param p_number Anzahl der zu erzeugenden Karte
     * @param p_opacity Einfärbung der zu erzeugenden Karte
     */
    Card(short p_color, short p_shape, short p_number, short p_opacity);

    operator char();

    /**
     * @brief Überladener Plus-Operator, um Karten zu addieren
     * @param a Zu addierende Karte
     * @return Addierte Karten
     */
    Card operator+(Card & a);

    /**
     * @brief Überladener Plus-Operator, um in der "Liste" weiterzuspringen
     * @param p_step Anzahl der zu springenden Schritte
     * @return Karte p_step-Schritte weiter in der Liste
     */
    Card* operator+(int p_step);

    /**
     * @brief Überladener Minus-Operator, um in der Liste zurückzuspringen
     * @param p_step Anzahl der zurückzuspringenden Schritte
     * @return Karte p_step-Schritte zurück in der Liste
     */
    Card* operator-(int p_step);

    int size();

    char attributesToByte();

    Card *nextCard();
    Card *previousCard();
};

#endif // CARD_H
