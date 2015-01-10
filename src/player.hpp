#pragma once

#include <QObject>
#include <QByteArray>
#include "client.hpp"

/**
 * @brief Spieler-Klasse
 */
class Player : public Client
{

public:
    /**
     * @brief Sendet ein Paket an den Server, in dem die ausgewählten Karten drinnenstehen.<BR>
     * Der Server überprüft diese auf ein Set und erhöht und senkt dementsprechend die Punktzahl des Spielers
     * @param p_cards Angeklickte Karten
     * @see PacketHandler::makeClickPacket
     */
    void sendClickPacket(QByteArray p_cards);

    /**
     * @brief Sendet ein Paket an den Server, dass dafür steht, dass dieser Spieler eine Set-Auswahl trifft
     */
    void sendTurnPacket();

    /**
     * @brief Konstruktor zum Erzeugen einer Player-Klasse
     * @param p_parent Elternteil des Players
     * @param p_ip IP-Adresse des Servers
     * @param p_port Port über den die Verbindung läuft
     */
    Player(QObject *p_parent = 0, QHostAddress p_ip = QHostAddress::LocalHost, int p_port = 1337);
};
