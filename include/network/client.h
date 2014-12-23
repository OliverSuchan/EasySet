#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <QHostAddress>
#include <QTcpSocket>
#include "packethandler.h"

class Client : public QTcpSocket
{
    Q_OBJECT

public:
    PacketHandler *m_packetHandler;

public:
    explicit Client(QObject *p_parent = 0, QHostAddress p_ip = QHostAddress::LocalHost, int = 1337);

signals:

public slots:
    void retrieveScore(short p_score);
    void retrieveField(QByteArray p_field);
    void onReadyRead();
};

#endif // CLIENT_H
