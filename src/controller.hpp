#pragma once

#include <list>
#include <stdlib.h>
#include <time.h>
#include "server.hpp"
#include "card.hpp"

class Controller : public Server
{
private:
    Cards m_deck;
    Cards m_field;
    Card* searchForCard(short p_color, short p_shape, short p_number, short p_opacity, Cards &p_cards);
    void sendFSPacket(QTcpSocket *p_socket);
    bool check(Cards &p_cards);

public:
    Controller(QObject *p_parent = 0);
    void draw(short p_count = 3);

public slots:
    void retrieveClick(QTcpSocket *p_client, char p_card);
};
