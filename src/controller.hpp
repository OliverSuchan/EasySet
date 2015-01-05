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
    void sendWaitTimePacket();
    void sendDeckLengthPacket();
    void sendScoreboard();
    void sendGameFinishedPacket();
    void sendInputLocked();
    void sendInputUnlocked(QTcpSocket *p_socket = nullptr);
    bool check(Cards &p_cards);
    Client &getClient(QTcpSocket *p_socket);
    short getSetCount();
    //QTimer *timer;

public:
    void sendGameStartedPacket();
    Controller(QObject *p_parent = 0);

signals:
    void showStartButton();

public slots:
    void draw(short p_count = 3);
    void retrieveClick(QTcpSocket *p_client, QByteArray p_cards);
    void retrievePlayerTurn(QTcpSocket *p_socket);

};
