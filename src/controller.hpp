#pragma once

#include <atomic>
#include <list>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <chrono>
#include <QTimer>
#include "server.hpp"
#include "card.hpp"

/**
 * @brief Die Klasse Controller ist für den kompletten Spielverlauf zuständig.<BR>
 * Sie regelt, wann welcher Client welche Pakete empfängt, wann das Spiel zu Ende ist/anfängt und<BR>
 * wenn Karten nachgelegt werden sollen
 */
class Controller : public Server
{
    Q_OBJECT

private:
    /**
     * @brief Thread-sicherer Wahrheitswert der angibt, ob extra Karten auf dem Spielfeld liegen
     */
    std::atomic<bool> m_extraCards;

    /**
     * @brief Liste bestehend aus allen Karten die sich im Deck befinden
     * @see Server::Cards
     */
    Cards m_deck;

    /**
     * @brief Liste bestehend aus allen Karten die sich auf dem Spielfeld befinden
     * @see Server::Cards
     */
    Cards m_field;

    /**
     * @brief Gibt an welcher Client aktuell am Zug ist
     */
    QTcpSocket *m_playerTurn;

    /**
     * @brief Timer, der einem Spieler,der an der Reihe ist, 5 Sekunden Zeit gibt,<BR>
     * um das Set, das er gefunden hat, auszuwählen, bevor ihm ein Punkt abgezogen wird
     */
    QTimer *clickTimer;

    /**
     * @brief Sendet das Paket für die Spielfeldsynchronisation
     * @see PacketHandler::makeFSPacket
     */
    void sendFSPacket();

    /**
     * @brief Sendet die Anzahl der verbleibenden Karten im Deck
     * @see PacketHandler::makeDeckLengthPacket
     */
    void sendDeckLengthPacket();

    /**
     * @brief Sendet das Paket für die Punktzahl-Synchronisation
     * @see PacketHandler::makeScoresPacket
     */
    void sendScoreboard();

    /**
     * @brief Sendet das Paket, das angibt, dass das Spiel vorrüber ist und<BR>
     * trennt die Verbindungen zu allen Clients
     * @see PacketHandler::makeGameFinishedPacket
     */
    void sendGameFinishedPacket();

    /**
     * @brief Sendet das Paket, um die Eingaben der Spieler zu sperren,<BR>
     * sobald ein Spieler ein Set auswählen möchte
     * @see PacketHandler::makeInputLockedPacket
     */
    void sendInputLocked();

    /**
     * @brief Sendet das Paket, um die Eingaben eines bestimmten Spielers<BR>
     *  oder aller Spieler zu entsperren
     * @param p_socket
     * @see PacketHandler::makeInputUnlockedPacket
     */
    void sendInputUnlocked(QTcpSocket *p_socket = nullptr);

    /**
     * @brief Überprüft ob eine Liste aus Karten ein Set bilden
     * @param p_cards Liste aus zu überprüfenden Karten
     * @return Wahrheitswert der angibt, ob die Karten ein Set bilden
     */
    bool check(Cards &p_cards);

    /**
     * @brief Berechnet die Anzahl der auf dem Spielfeld liegenden Sets
     * @return Anzahl der Sets auf dem Spielfeld
     */
    short getSetCount();

    /**
     * @brief Gibt einen Client-Tuple für einen bestimmten Socket zurück
     * @param p_socket Socket für den das Client-Tuple gesucht werden soll
     * @return Client-Tuple
     * @see Server::Client
     */
    Client &getClient(QTcpSocket *p_socket);

    /**
     * @brief Sucht nach einer Karte in einer Liste mit gegebenen Attributen
     * @param p_color Farbe der gesuchten Karte
     * @param p_shape Form der gesuchten Karte
     * @param p_number Anzahl der gesuchten Karte
     * @param p_opacity Einfärbung der gesuchten Karte
     * @param p_cards Liste aus Karten, in der nach dieser speziellen Karte gesucht werden soll
     * @return Die gefundene Karte
     * @see Card
     */
    Card* searchForCard(short p_color, short p_shape, short p_number, short p_opacity, Cards &p_cards);

public:
    /**
     * @brief Sendet das Paket, um das Spiel zu starten
     * @see PacketHandler::makeGameStartedPacket
     */
    void sendGameStartedPacket();

    /**
     * @brief Konstruktor zum Erzeugen einer Controller-Instanz
     * @param p_parent Elternteil des Controllers
     */
    Controller(QObject *p_parent = 0);

signals:
    /**
     * @brief Wird emittiert, um den Startbutton auf dem Hauptfenster anzuzeigen
     * @see Window::retrieveShowStartButton
     */
    void showStartButton();

private slots:
    /**
     * @brief Wird aufgerufen, um den Punktestand des aktuellen Spielers zu erniedrigen
     */
    void deductScore();

public slots:
    /**
     * @brief Zieht eine bestimmte Anzahl zufälliger Karten aus dem Deck und legt sie aufs Spielfeld.<BR>
     * Danach wird eine Spielfeld-Synchronisation ausgeführt
     * @param p_count
     */
    void draw(unsigned int p_count = 3);

    /**
     * @brief Wird aufgerufen, wenn ein Set ausgewählt wurde.<BR>
     * Das Set wird überprüft und dementsprechend Punkte gutgeschrieben oder abgezogen
     * @param p_client Spieler, der das Set ausgewählt hat
     * @param p_cards Die ausgewählten Karten
     * @see PacketHandler::readClick
     */
    void retrieveClick(QTcpSocket *p_client, QByteArray p_cards);

    /**
     * @brief Wird aufgerufen, sobald ein Spieler ein Set auswählen möchte
     * @param p_socket Client, dem das Anklicken der Karten gewährt ist
     * @see PacketHandler::readTurnPacket
     */
    void retrievePlayerTurn(QTcpSocket *p_socket);

};
