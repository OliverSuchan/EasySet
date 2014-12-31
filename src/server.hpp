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
    typedef std::list<std::unique_ptr<Card>> Cards;
    typedef std::tuple<QTcpSocket*, short, Cards> Client;
    typedef std::vector<Client> Clients;
    Clients m_clients;
    std::unique_ptr<PacketHandler> m_packetHandler;
    virtual void sendFSPacket(QTcpSocket *p_field) = 0;

public:
    explicit Server(QObject *parent = 0, int p_port = 1337);

signals:

protected slots:
    void deleteLater();

public slots:
    void newCon();
    void onReadyRead();

};

#include "packethandler.hpp"
