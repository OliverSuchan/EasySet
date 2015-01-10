#pragma once

#include <iostream>
#include <QObject>
#include <QTcpSocket>
#include "enums.hpp"
#include "card.hpp"

/**
 * @brief Die PacketHandler-Klasse dient zur Verwaltung von ein- bzw. ausgehenden Paketen.<BR>
 * Werden bestimmte Pakettypen erkannt, so werden die entsprechenden Signale emittiert,<BR>
 * und dadurch die Slots in den externen Klassen aufgerufen
 */
class PacketHandler : public QObject
{
    Q_OBJECT

private:
    /**
     * @brief Verarbeitet ein einzelnen Paket
     * @param p_packet Das zu verarbeitende Paket
     * @param p_socket Absender
     */
    void processPacket(QByteArray p_packet, QTcpSocket* p_socket = nullptr);

public:
    /**
     * @brief Konstruktor zum Erzeugen einer PacketHandler-Instanz
     * @param parent Elternteil des PacketHandlers
     */
    explicit PacketHandler(QObject *parent = 0);

    /**
     * @brief Teilt den Datenstrom in die einzelnen Pakete auf und verarbeitet diese dann
     * @param p_packets Datenstrom
     * @param p_socket Absender
     * @see processPacket
     */
    void processPackets(QByteArray p_packets, QTcpSocket *p_socket = nullptr);

    /**
     * @brief Erzeugt ein Paket für die Spielfeldsynchronisation, anhand einer Liste aus Karte
     * @param p_field Liste aus Karten - Spielfeld
     * @return Paket
     */
    QByteArray makeFSPacket(std::list<Card*> &p_field);

    /**
     * @brief Erzeugt ein Paket das eine Set-Auswahl darstellt
     * @param p_cards Ausgewählte Karten
     * @return Paket
     */
    QByteArray makeClickPacket(QByteArray p_cards);

    /**
     * @brief Erzeugt ein Paket, für die Punkte-Synchronisation
     * @param p_scores Die Punkte aller Spieler
     * @return Paket
     */
    QByteArray makeScoresPacket(QByteArray p_scores);

    /**
     * @brief Erzeugt eine Paket das den Start des Spiels darstellt
     * @return Paket
     */
    QByteArray makeGameStartedPacket();

    /**
     * @brief Erzeugt ein Paket, um das Spielende anzusagen
     * @return Paket
     */
    QByteArray makeGameFinishedPacket();

    /**
     * @brief Erzeugt ein Paket das die Anzahl der im Deck beinhalteten Karten darstellt
     * @param p_deckLength Deckgröße
     * @return Paket
     */
    QByteArray makeDeckLengthPacket(short p_deckLength);

    /**
     * @brief Erzeugt ein Paket das die Sperrung der Eingaben bewirkt
     * @return Paket
     */
    QByteArray makeInputLockedPacket();

    /**
     * @brief Erzeugt ein Paket das die Entsperrung der Eingaben bewirkt
     * @return Paket
     */
    QByteArray makeInputUnlockedPacket();

    /**
     * @brief Erzeugt ein Paket das angibt, dass ein Spieler ein Set auswählen möchte
     * @return Paket
     */
    QByteArray makeTurnPacket();

signals:
    /**
     * @brief Signal das emittiert wird, wenn das Spielfeldsynchronisations-Paket verarbeitet wird
     * @param p_field Spielfeld
     */
    void readField(QByteArray p_field);

    /**
     * @brief Signal das emittiert wird, wenn das Punktestandsynchronisations-Paket verarbeitet wird
     * @param p_scores Punktestand
     */
    void readScores(QByteArray p_scores);

    /**
     * @brief Signal das emittiert wird, wenn ein Klick-Paket verarbeitet wird
     * @param p_socket Absender
     * @param p_cards Ausgewählte Karten
     */
    void readClick(QTcpSocket *p_socket, QByteArray p_cards);

    /**
     * @brief Signal das emittiert wird, wenn das Spielstarten-Paket verarbeitet wird
     */
    void readGameStartedPacket();

    /**
     * @brief Signal das emittiert wird, wenn das Spielbeenden-Paket verarbeitet wird
     */
    void readGameFinishedPacket();

    /**
     * @brief Signal das emittiert wird, wenn das Deckgrößen-Paket verarbeitet wird
     * @param p_deckLength Deckgröße
     */
    void readDeckLength(short p_deckLength);

    /**
     * @brief Signal das emittiert wird, wenn das Eingabensperr-Paket verarbeitet wird
     */
    void readLockedPacket();

    /**
     * @brief Signal das emittiert wird, wenn das Eingabenentsperr-Paket verarbeitet wird
     */
    void readUnlockedPacket();

    /**
     * @brief Signal das emittiert wird, wenn das Spieler-Am-Zug-Paket verarbeitet wird
     * @param p_socket Spieler, der am Zug ist
     */
    void readTurnPacket(QTcpSocket *p_socket);

};
