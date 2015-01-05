#pragma once

#include <QColor>

enum PacketHeader
{
    //WAIT_TIME = 0x01,
    GAME_STATE = 0x01,
    DECK = 0x02,
    INPUT_STATE = 0x03,
    PLAYER_TURN = 0x04,
    SCORES = 0x05,
    FIELD_SYNCHRO = 0x7,
    CLICK = 0xA
};

enum Color
{
    RED,
    BLUE,
    GREEN
};

static const QColor setColors[3] = { Qt::red, Qt::blue, Qt::darkGreen};

enum Shape
{
    TRIANGLE,
    SQUARE,
    CIRCLE
};

enum Number
{
    ONE,
    TWO,
    THREE
};

enum Opacity
{
    FILLED,
    EMPTY,
    PALLID
};

#include "card.hpp"
