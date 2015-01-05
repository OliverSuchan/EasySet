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
    virtual void sendGameFinishedPacket() = 0;
    virtual void sendDeckLengthPacket() = 0;
    virtual void sendScoreboard() = 0;
    virtual void sendInputLocked() = 0;
    virtual void sendInputUnlocked(QTcpSocket *p_socket = nullptr) = 0;
    //virtual void sendWaitTimePacket() = 0;
    //const unsigned int m_waitTime = 20 * 1000;

public:
    virtual void sendGameStartedPacket() = 0;
    explicit Server(QObject *parent = 0, int p_port = 1337);

signals:

protected slots:
    void deleteLater();

public slots:
    void newCon();
    void onReadyRead();
    virtual void retrieveClick(QTcpSocket *p_client, QByteArray p_cards) = 0;
    virtual void retrievePlayerTurn(QTcpSocket *p_client) = 0;

};

#include "packethandler.hpp"
