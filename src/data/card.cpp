#include "Card.h"

Card::Card(short p_color, short p_shape, short p_number, short p_opacity)
    : m_color(p_color),
      m_shape(p_shape),
      m_number(p_number),
      m_opacity(p_opacity)
{

}

Card Card::operator +(Card & a){
    return Card((a.m_color + m_color) % 3, (a.m_shape + m_shape) % 3, (a.m_number + m_number) % 3, (a.m_opacity + m_opacity) % 3); // Karten werden wie Vektoren addiert
}                                                                                                                                  // die Parameter werden modulo 3 genommen

Card *Card::operator+(unsigned short p_step)
{
    Card* currentCard = this;
    for(int i = 0; i < p_step; i++)
    {
        currentCard = this->m_nextCard; // p_step mal den Pointer currentCard auf die nächste Karte schieben
    }
    return currentCard;
}
Card* Card::operator-(unsigned short p_step)
{
    Card* currentCard = this;
    for (int i = 0; i < p_step; i++)
    {
        currentCard = this->m_previousCard;
    }
    return currentCard;
}


