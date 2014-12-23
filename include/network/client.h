#ifndef CLIENT_H
#define CLIENT_H

#include <QHostAddress>
#include <QTcpSocket>
#include "packetadministration.h"

class Client : public QTcpSocket
{
    Q_OBJECT

public:
    PacketAdministration *m_packetAdministration;

public:
    explicit Client(QObject *p_parent = 0, QHostAddress p_ip = QHostAddress::LocalHost, int = 1337);

signals:

public slots:
    void retrieveScore(short p_score);
    void retrieveField(void* p_field);
    void onReadyRead();
};

#endif // CLIENT_H
