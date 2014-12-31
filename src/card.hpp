#pragma once

#include <memory>
#include "enums.hpp"

class Card
{
    friend class Window;
    friend class Controller;

protected:
    short m_color;
    short m_shape;
    short m_number;
    short m_opacity;

public:
    Card(short p_color, short p_shape, short p_number, short p_opacity);
    Card operator+(Card &p_card);
    char attributesToByte();
    operator char();

};

#include "cardwidget.hpp"
#include "window.hpp"
#include "controller.hpp"
