#ifndef PACKETADMINISTRATION_H
#define PACKETADMINISTRATION_H

#include <iostream>
#include <iterator>
#include <algorithm>
#include <QByteArray>
#include <QObject>

class PacketAdministration : public QObject
{
    Q_OBJECT

    enum PacketHeader
    {
        SCORE = 0x3,
        FIELD_SYNCHRO = 0x7,
        CLICK = 0xA
    };

private:
    void processPacket(QByteArray);

public:
    PacketAdministration(QObject* p_parent = 0);
    void processPackets(QByteArray p_packets);

signals:
    void readScore(short p_score);
};

#endif // PACKETADMINISTRATION_H
