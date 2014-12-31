#ifndef CLIENT_H
#define CLIENT_H

#include <QHostAddress>
#include <QTcpSocket>
#include "../include/packetadministration.h"

class Client : public QTcpSocket
{
    Q_OBJECT

public:
    PacketAdministration *m_packetAdministration;

public:
    explicit Client(QHostAddress = QHostAddress::LocalHost, QObject *parent = 0);

signals:

public slots:
    void retrieveScore(short p_score);
    void onReadyRead();
};

#endif // CLIENT_H
