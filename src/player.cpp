#include "player.hpp"

void Player::sendClickPacket(std::list<std::unique_ptr<Card> > &p_cards)
{
    write(m_packetHandler->makeClickPacket(p_cards));
    flush();
}

Player::Player(QObject *p_parent) :
    Client(p_parent)
{
}
