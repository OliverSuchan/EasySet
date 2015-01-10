#pragma once

#include <memory>
#include "enums.hpp"

/**
 * @brief Die Klasse Card stellt das digitale pendant zu den analogen Karten des Spiels Set dar
 */
class Card
{
    //Legt die Klasse Window als Friendklasse fest
    friend class Window;
    //Legt die Klasse Controller als Friendklasse fest
    friend class Controller;

protected:
    /**
     * @brief Farbe der Karte (Wert im Intervall I = [0;2])
     * @see Color
     */
    short m_color;

    /**
     * @brief Form der Karte (Wert im Intervall I = [0;2])
     * @see Shape
     */
    short m_shape;

    /**
     * @brief Anzahl der Karte (Wert im Intervall I = [0;2])
     * @see Number
     */
    short m_number;

    /**
     * @brief Einfärbung der Karte (Wert im Intervall I = [0;2])
     * @see Opacity
     */
    short m_opacity;

public:
    /**
     * @brief Konstruktor zum Erzeugen einer Card-Instanz
     * @param p_color Farbe der zu erzeugenden Karte
     * @param p_shape Form der zu erzeugenden Karte
     * @param p_number Anzahl der zu erzeugenden Karte
     * @param p_opacity Einfärbung der zu erzeugenden Karte
     */
    Card(short p_color, short p_shape, short p_number, short p_opacity);

    /**
     * @brief Überladener Plus-Operator, um Karten wie Vektoren zu addieren
     * @param p_card Karte die als 2. Summand dient
     * @return Summe aus der aktuellen Karte und der übergebenen Karte
     */
    Card operator+(Card &p_card);

    /**
     * @brief Konvertiert alle Attribute zu einem Byte
     * @return 1 Byte, das alle Attribute umfasst
     */
    char attributesToByte();

    /**
     * @brief Char-Konvertierungsoperator
     */
    operator char();

};

#include "cardwidget.hpp"
#include "window.hpp"
#include "controller.hpp"
