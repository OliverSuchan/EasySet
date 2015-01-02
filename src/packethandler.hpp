#pragma once

#include <iostream>
#include <bitset>
#include <QObject>
#include <QTcpSocket>
#include "enums.hpp"
#include "card.hpp"

class PacketHandler : public QObject
{
    Q_OBJECT

private:
    void processPacket(QByteArray p_packet, QTcpSocket* p_socket = nullptr);

public:
    explicit PacketHandler(QObject *parent = 0);
    void processPackets(QByteArray p_packets, QTcpSocket *p_socket = nullptr);
    QByteArray makeFSPacket(std::list<Card*> &p_field);
    QByteArray makeClickPacket(QByteArray p_cards);
    QByteArray makeScoresPacket(QByteArray p_scores);
    QByteArray makeScorePacket(short p_score);
    QByteArray makeWaitTimePacket(unsigned int p_waitTime);
    QByteArray makeDeckLengthPacket(short p_deckLength);

signals:
    void readField(QByteArray p_field);
    void readScore(short p_score);
    void readScores(QByteArray p_scores);
    void readClick(QTcpSocket *p_socket, QByteArray p_cards);
    void readWaitTime(unsigned int p_waitTime);
    void readDeckLength(short p_deckLength);

public slots:

};
