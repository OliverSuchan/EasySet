#include "card.hpp"

Card::Card(short p_color, short p_shape, short p_number, short p_opacity) :
    m_color(p_color),
    m_shape(p_shape),
    m_number(p_number),
    m_opacity(p_opacity)
{
}

Card Card::operator+(Card &p_card)
{
    return Card((p_card.m_color + m_color) % 3, (p_card.m_shape + m_shape) % 3, (p_card.m_number + m_number) % 3, (p_card.m_opacity + m_opacity) % 3);
}

char Card::attributesToByte()
{
    return ((m_color << 6) | (m_shape << 4) | (m_number << 2) | m_opacity);
}

Card::operator char()
{
    return attributesToByte();
}
