#pragma once

#include <atomic>
#include <list>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QKeyEvent>

namespace Ui {
    class Window;
}

#include "card.hpp"
#include "informationwidget.hpp"

class Player;
class Controller;

/**
 * @brief Die Singleton-Klasse Window ist die HauptGUI.<BR>
 * Dort findet das Spiel so wirklich für die Spieler statt
 */
class Window : public QMainWindow
{
    Q_OBJECT

private:
    /**
     * @brief Thread-sicherer Wahrheitswert der angibt, ob die Eingabe gesperrt ist
     */
    std::atomic<bool> m_inputLocked;

    Ui::Window *ui;

    /**
     * @brief Liste bestehend aus Karten, die als Spielfeld dient
     * @see Card
     */
    std::list<Card*> m_field;

    /**
     * @brief Spieler, der aktuell am Zug ist
     * @see Player
     */
    Player *m_curPlayer;

    /**
     * @brief Statusanzeige des Spiels
     * @see InformationWidget
     */
    InformationWidget *m_infoWidget;

    /**
     * @brief Ein Layer, der zur Blockade der Eingabe dient
     */
    QWidget *m_layer;

    /**
     * @brief Startbutton, um das Spiel zu starten
     */
    QPushButton *m_startButton;

    /**
     * @brief Controller, der temporär genutzt wird, um das Spiel zu starten
     */
    Controller *m_controller;

    /**
     * @brief Liste aus Karten, die die aktuell angeklickten Karten darstellen
     */
    std::list<Card*> m_clickedCards;

    /**
     * @brief Konstruktor zum Erzeugen einer Window-Instanz.<BR>
     * Konstruktor ist aufgrund der Singleton-Designstruktur private
     * @param parent Elternteil des Windows
     */
    Window(QWidget *parent = 0);

    /**
      * @brief Destruktor zum Aufräumen einer Window-Instanz.<BR>
      * Destruktor ist aufgrund der Singleton-Designstruktur private
      */
    ~Window();

    /**
     * @brief Überladener Zuweisungs-Operator.<BR>
     * Ist aufgrund des Singleton-Designpatterns private
     * @return
     */
    Window& operator=(Window&) = delete;

protected:
    /**
     * @brief Wird aufgerufen, wenn der Schließen-Button des Fensters geklickt wird
     * @param p_closeEvent Schließ-Event
     */
    void closeEvent(QCloseEvent *p_closeEvent);

    /**
     * @brief Wird aufgerufen, wenn eine Taste auf der Tastatur gedrückt wird
     * @param p_keyEvent Tasten-Event
     */
    void keyPressEvent(QKeyEvent *p_keyEvent);

public:
    /**
     * @brief Liste aus allen aktuellen, lokalen Spielern und deren ausgewählte Taste
     */
    std::list<std::tuple<Player*, Qt::Key>> m_players;

    /**
     * @brief Liefert die Instanz der Singleton-Klasse Window
     * @return Window-Instanz
     */
    static Window &getInstance();

private slots:
    /**
     * @brief Wird aufgerufen, wenn der Start-Button geklickt wird
     */
    void clickStartButton();

public slots:
    /**
     * @brief Wird aufgerufen, wenn eine Karte angeklickt wird
     * @see CardWidget::clicked
     */
    void cardClicked();

    /**
     * @brief Wird aufgerufen, wenn die Verbindung zum Server unterbrochen/ getrennt wird
     */
    void clientDisconnected();

    /**
     * @brief Wird aufgerufen, wenn das Spielfeldsynchronisations-Paket empfangen wird
     * @param p_field Spielfeld
     * @see PacketHandler::readField
     */
    void retrieveField(QByteArray p_field);

    /**
     * @brief Wird aufgerufen, wenn das Deckgröße-Paket empfangen wird
     * @param p_deckLength Deckgröße
     * @see PacketHandler::readDeckLength
     */
    void retrieveDeckLength(short p_deckLength);

    /**
     * @brief Wird aufgerufen, wenn das Punktestand-Paket empfangen wird
     * @param p_scores Punktestand
     * @see PacketHandler::readScores
     */
    void retrieveScores(QByteArray p_scores);

    /**
     * @brief Wird aufgerufen, wenn das Spielstarten-Paket empfangen wird
     * @see PacketHandler::readGameStartedPacket
     */
    void retrieveGameStarted();

    /**
     * @brief Wird aufgerufen, wenn das Spielbeenden-Paket empfangen wird
     * @see PacketHandler::readGameFinishedPacket
     */
    void retrieveGameFinished();

    /**
     * @brief Wird aufgerufen, wenn der Start-Button angezeigt werden soll
     * @see Controller::showStartButton
     */
    void retrieveShowStartButton();

    /**
     * @brief Wird aufgerufen, wenn das Eingabenentsperr-Paket emfpangen wird
     * @see PacketHandler::readUnlockedPacket
     */
    void retrieveUnlock();

    /**
     * @brief Wird aufgerufen, wenn das Eingabesperr-Paket empfangen wird
     * @see PacketHandler::readLockedPacket
     */
    void retrieveLock();

signals:
    /**
     * @brief Signal das alle Karten entwählt
     */
    void unselectAll();

    /**
     * @brief Signal das den Status der Karten - ob man diese anklicken kann oder nicht - festlegt
     * @param p_val Wahrheitswert der angibt, ob die Karten anklickbar sind oder nicht
     */
    void canClick(bool p_val);

};

#include "player.hpp"
#include "controller.hpp"
