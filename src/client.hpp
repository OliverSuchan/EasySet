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
    PacketHandler *m_packetHandler;
    explicit Client(QObject *p_parent = 0, QHostAddress p_ip = QHostAddress::LocalHost, int p_port = 1337);
    virtual void sendClickPacket(QByteArray p_cards) = 0;
    virtual void sendTurnPacket() = 0;

signals:

public slots:
    void onReadyRead();

};

#include "packethandler.hpp"
