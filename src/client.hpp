#pragma once

#include <QTcpSocket>
#include <QHostAddress>
#include <memory>

class PacketHandler;
class Card;

class Client : public QTcpSocket
{
    Q_OBJECT

public:
    std::unique_ptr<PacketHandler> m_packetHandler;
    explicit Client(QObject *p_parent = 0, QHostAddress p_ip = QHostAddress::LocalHost, int p_port = 1337);
    virtual void sendClickPacket(std::list<Card*> &p_cards) = 0;

signals:

public slots:
    void retrieveBestScore(short p_score);
    void retrieveScore(short p_score);
    void onReadyRead();

};

#include "packethandler.hpp"
