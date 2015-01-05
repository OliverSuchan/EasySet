#include "player.hpp"

void Player::sendClickPacket(QByteArray p_cards)
{
    write(m_packetHandler->makeClickPacket(p_cards));
    flush();
}

Player::Player(QObject *p_parent, QHostAddress p_ip, int p_port) :
    Client(p_parent, p_ip, p_port)
{
}
