#pragma once

#include <QColor>

enum PacketHeader
{
    WAIT_TIME = 0x01,
    SCORE = 0x3,
    SCORES = 0x5,
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
