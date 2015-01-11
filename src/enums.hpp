#pragma once

#include <QColor>

/**
 * @brief Anonyme innere Klasse, mit den verschiedenen Pakettypen
 */
enum PacketHeader
{
    GAME_STATE = 0x01,
    DECK = 0x02,
    INPUT_STATE = 0x03,
    PLAYER_TURN = 0x04,
    SCORES = 0x05,
    FIELD_SYNCHRO = 0x07,
    CLICK = 0x0A
};

/**
 * @brief Anonyme innere Klasse, mit den verschiedenen Farben einer Karte
 */
enum Color
{
    RED,
    BLUE,
    GREEN
};

/**
 * @brief Die möglichen Farben der Karten
 */
static const QColor setColors[3] = { Qt::red, Qt::blue, Qt::darkGreen};

/**
 * @brief Anonyme innere Klasse, mit den verschiedenen Formen einer Karte
 */
enum Shape
{
    TRIANGLE,
    SQUARE,
    CIRCLE
};

/**
 * @brief Anonyme innere Klasse, mit den verschiedenen Anzahlen einer Karte
 */
enum Number
{
    ONE,
    TWO,
    THREE
};

/**
 * @brief Anonyme innere Klasse, mit den verschiedenen Einfärbungen einer Karte
 */
enum Opacity
{
    FILLED,
    EMPTY,
    PALLID
};

//#include "card.hpp"
