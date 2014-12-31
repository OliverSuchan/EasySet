#pragma once

#include "client.hpp"

class Player : public Client
{

public:
    void sendClickPacket(std::list<std::unique_ptr<Card>> &p_cards);
    Player(QObject *p_parent = 0);
};
