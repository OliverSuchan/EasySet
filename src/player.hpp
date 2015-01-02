#pragma once

#include <QObject>
#include <QByteArray>
#include "client.hpp"

class Player : public Client
{

public:
    void sendClickPacket(QByteArray p_cards);
    Player(QObject *p_parent = 0);
};
