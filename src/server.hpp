#pragma once

#include <vector>
#include <tuple>
#include <QTcpServer>

class PacketHandler;
class Card;

/**
 * @brief Die abstrakte Klasse Server, steht für den Server des Spiels
 */
class Server : public QTcpServer
{
    Q_OBJECT

protected:
    /**
     * @brief Typdefinition Cards
     * @see Card
     */
    typedef std::list<Card*> Cards;

    /**
     * @brief Typdefinition Client
     * @see Server::Cards
     */
    typedef std::tuple<QTcpSocket*, short, Cards> Client;

    /**
     * @brief Typdefinition Clients
     * @see Server::Client
     */
    typedef std::vector<Client> Clients;

    /**
     * @brief Liste aus allen verbundenen Clients
     * @see Server::Clients
     */
    Clients m_clients;

    /**
     * @brief Paketverwalter für ein- und ausgehende Pakete
     * @see PacketHandler
     */
    PacketHandler *m_packetHandler;

    /**
     * @brief Sendet das Paket für die Spielfeldsynchronisation
     * @see PacketHandler::makeFSPacket
     */
    virtual void sendFSPacket() = 0;

    /**
     * @brief Sendet die Anzahl der verbleibenden Karten im Deck
     * @see PacketHandler::makeDeckLengthPacket
     */
    virtual void sendDeckLengthPacket() = 0;

    /**
     * @brief Sendet das Paket für die Punktzahl-Synchronisation
     * @see PacketHandler::makeScoresPacket
     */
    virtual void sendScoreboard() = 0;

    /**
     * @brief Sendet das Paket, das angibt, dass das Spiel vorrüber ist und<BR>
     * trennt die Verbindungen zu allen Clients
     * @see PacketHandler::makeGameFinishedPacket
     */
    virtual void sendGameFinishedPacket() = 0;

    /**
     * @brief Sendet das Paket, um die Eingaben der Spieler zu sperren,<BR>
     * sobald ein Spieler ein Set auswählen möchte
     * @see PacketHandler::makeInputLockedPacket
     */
    virtual void sendInputLocked() = 0;

    /**
     * @brief Sendet das Paket, um die Eingaben eines bestimmten Spielers<BR>
     *  oder aller Spieler zu entsperren
     * @param p_socket
     * @see PacketHandler::makeInputUnlockedPacket
     */
    virtual void sendInputUnlocked(QTcpSocket *p_socket = nullptr) = 0;

public:
    /**
     * @brief Sendet das Paket, um das Spiel zu starten
     * @see PacketHandler::makeGameStartedPacket
     */
    virtual void sendGameStartedPacket() = 0;

    /**
     * @brief Konstruktor zum Erzeugen einer Server-Instanz
     * @param parent Elternteil des Servers
     * @param p_port Port an dem der Server lauscht
     */
    explicit Server(QObject *parent = 0, int p_port = 1337);

public slots:
    /**
     * @brief Wird aufgerufen, wenn eine neue Verbindung zur Verfügung steht
     */
    void newCon();

    /**
     * @brief Wird aufgerufen, sobald der Buffer mit den eingehenden Paketen lesebereit ist
     */
    void onReadyRead();

    /**
     * @brief Wird aufgerufen, wenn ein Set ausgewählt wurde.<BR>
     * Das Set wird überprüft und dementsprechend Punkte gutgeschrieben oder abgezogen
     * @param p_client Spieler, der das Set ausgewählt hat
     * @param p_cards Die ausgewählten Karten
     * @see PacketHandler::readClick
     */
    virtual void retrieveClick(QTcpSocket *p_client, QByteArray p_cards) = 0;

    /**
     * @brief Wird aufgerufen, sobald ein Spieler ein Set auswählen möchte
     * @param p_socket Client, dem das Anklicken der Karten gewährt ist
     * @see PacketHandler::readTurnPacket
     */
    virtual void retrievePlayerTurn(QTcpSocket *p_socket) = 0;

};

#include "packethandler.hpp"
