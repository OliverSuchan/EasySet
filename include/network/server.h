#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>
#include <QTcpServer>
#include <QTcpSocket>
#include "packethandler.h"

class Server : public QTcpServer
{
    Q_OBJECT

    typedef std::vector<QTcpSocket*> Clients;

protected:
    Clients m_clients;
    PacketHandler *m_packetHandler;
    virtual void sendFSPacket(QTcpSocket *p_client) = 0;

public:
    explicit Server(QObject *parent = 0);

signals:

public slots:
    void newCon();
    void on_readyRead();
    void deleteLater();

};

#endif // SERVER_H
