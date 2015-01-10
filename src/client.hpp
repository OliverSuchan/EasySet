#pragma once

#include <QTcpSocket>
#include <QHostAddress>

class PacketHandler;
class Card;

/**
 * @brief Die abstrakte Klasse Client kümmert sich um die Verbindung zum Server und macht so ein Spielen möglich
 */
class Client : public QTcpSocket
{
    Q_OBJECT

protected:
    /**
     * @brief Paketverwalter für ein- und ausgehende Pakete
     * @see PacketHandler
     */
    PacketHandler *m_packetHandler;

public:
    /**
     * @brief Konstruktor zum Erzeugen einer Client-Instanz
     * @param p_parent Elternteil des Clients
     * @param p_ip IP-Adresse mit der sich der Client verbinden soll
     * @param p_port Port, auf dem die Verbindung stattfindet
     */
    explicit Client(QObject *p_parent = 0, QHostAddress p_ip = QHostAddress::LocalHost, int p_port = 1337);

    /**
     * @brief Sendet ein Klick-Paket - mit den ausgewählten Karten - an den Server.<BR>
     * (Muss von Klasse Player definiert werden)
     * @param p_cards Array bestehend aus den angewählten Karten
     */
    virtual void sendClickPacket(QByteArray p_cards) = 0;

    /**
     * @brief Sendet ein Paket an den Server das angibt, dass der aktuelle Socket am Zug ist.<BR>
     * (Muss von Klasse Player definiert werden)
     */
    virtual void sendTurnPacket() = 0;

public slots:
    /**
     * @brief Wird aufgerufen, sobald der Buffer mit den eingehenden Paketen lesebereit ist
     */
    void onReadyRead();

};

#include "packethandler.hpp"
