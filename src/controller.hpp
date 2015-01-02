#pragma once

#include <atomic>
#include <list>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <QTimer>
#include "server.hpp"
#include "card.hpp"

class Controller : public Server
{
    Q_OBJECT

private:
    Cards m_deck;
    Cards m_field;
    Card* searchForCard(short p_color, short p_shape, short p_number, short p_opacity, Cards &p_cards);
    std::atomic<bool> m_extraCards;
    void sendFSPacket();
    void sendScorePacket(QTcpSocket *p_field, short p_score);
    void sendWaitTimePacket();
    bool check(Cards &p_cards);
    Client &getClient(QTcpSocket *p_socket);
    void updateScores();
    QTimer *timer;

public:
    Controller(QObject *p_parent = 0);

public slots:
    void draw(short p_count = 3);
    void retrieveClick(QTcpSocket *p_client, QByteArray p_cards);
};
