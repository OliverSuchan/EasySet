#pragma once

#include <QColor>

enum PacketHeader
{
    SCORE = 0x3,
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
