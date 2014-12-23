#ifndef PACKETADMINISTRATION_H
#define PACKETADMINISTRATION_H

#include <iostream>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <QByteArray>
#include <QObject>

class PacketHandler : public QObject
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
    PacketHandler(QObject* p_parent = 0);
    void processPackets(QByteArray p_packets);
    QByteArray makeFSPacket(void* p_field);
    QByteArray makeClickPacket(void* p_card);
    QByteArray makeScorePacket(short p_score);

signals:
    void readScore(short p_score);
    void readField(QByteArray p_field);
    void readClick(void* p_card);

};

#endif // PACKETADMINISTRATION_H
