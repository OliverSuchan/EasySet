#include "card.hpp"

// Konstruktor
Card::Card(short p_color, short p_shape, short p_number, short p_opacity) :     
    m_color(p_color),
    m_shape(p_shape),
    m_number(p_number),
    m_opacity(p_opacity)
{
}

Card Card::operator+(Card &p_card) // Karten werden wie Vektoren aufaddiert, die Parameter werden dann Modulo 3 genommen
{
    return Card((p_card.m_color + m_color) % 3, (p_card.m_shape + m_shape) % 3, (p_card.m_number + m_number) % 3, (p_card.m_opacity + m_opacity) % 3);
}

char Card::attributesToByte()   // Attribute werden als Byte gespeichert
{
    return ((m_color << 6) | (m_shape << 4) | (m_number << 2) | m_opacity);
}

// Konvertierung von Card in char
Card::operator char()
{
    return attributesToByte();
}
