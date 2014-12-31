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
    void processPacket(QByteArray p_packet, std::unique_ptr<QTcpSocket> p_socket = nullptr);

public:
    explicit PacketHandler(QObject *parent = 0);
    void processPackets(QByteArray p_packets, std::unique_ptr<QTcpSocket> p_socket = nullptr);
    QByteArray makeFSPacket(std::list<std::unique_ptr<Card>> &p_field);
    QByteArray makeClickPacket(std::list<std::unique_ptr<Card>> &p_cards);

signals:
    void readField(QByteArray p_field);
    void readScore(short p_score);
    void readClick(QTcpSocket *p_socket, char p_card);

public slots:

};
