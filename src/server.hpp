#pragma once

#include <memory>
#include <vector>
#include <tuple>
#include <QTcpServer>

class PacketHandler;
class Card;

class Server : public QTcpServer
{
    Q_OBJECT

protected:
    typedef std::list<Card*> Cards;
    typedef std::tuple<QTcpSocket*, short, Cards> Client;
    typedef std::vector<Client> Clients;
    Clients m_clients;
    PacketHandler *m_packetHandler;
    virtual void sendFSPacket() = 0;
    virtual void sendScorePacket(QTcpSocket *p_field, short p_score) = 0;
    virtual void sendWaitTimePacket() = 0;
    const unsigned int m_waitTime = 20 * 1000;

public:
    explicit Server(QObject *parent = 0, int p_port = 1337);

signals:

protected slots:
    void deleteLater();

public slots:
    void newCon();
    void onReadyRead();
    virtual void retrieveClick(QTcpSocket *p_client, QByteArray p_cards) = 0;

};

#include "packethandler.hpp"
