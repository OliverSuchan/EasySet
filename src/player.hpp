#pragma once

#include "client.hpp"

class Player : public Client
{

public:
    void sendClickPacket(std::list<Card*> &p_cards);
    Player(QObject *p_parent = 0);
};
