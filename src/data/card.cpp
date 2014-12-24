#include "Card.h"

Card *Card::nextCard()
{
    return m_nextCard;
}

Card *Card::previousCard()
{
    return m_previousCard;
}

Card::Card(short p_color, short p_shape, short p_number, short p_opacity)
    : m_color(p_color),
      m_shape(p_shape),
      m_number(p_number),
      m_opacity(p_opacity)
{

}

Card::operator char()
{
    return attributesToByte();
}

Card Card::operator +(Card & a)
{
    return Card((a.m_color + m_color) % 3, (a.m_shape + m_shape) % 3, (a.m_number + m_number) % 3, (a.m_opacity + m_opacity) % 3); // Karten werden wie Vektoren addiert
}

Card *Card::operator+(int p_step)
{
    Card* currentCard = this;
    for(int i = 0; i < p_step; i++)
    {
        currentCard = currentCard->nextCard(); // p_step mal den Pointer currentCard auf die nächste Karte schieben
    }
    return currentCard;
}


Card* Card::operator-(int p_step)
{
    Card* currentCard = this;
    for (int i = 0; i < p_step; i++)
    {
        currentCard = currentCard->previousCard();
    }
    return currentCard;
}

int Card::size()
{
    int val = 1;
    while(*this + val != this && *this + val != nullptr) ++val;
    return val;
}


char Card::attributesToByte()
{
    char val = 0;
    val |= (m_color << 6) | (m_shape << 4) | (m_number << 2) | m_opacity;
    return val;
}


