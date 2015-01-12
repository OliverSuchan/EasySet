#pragma once

#include <iostream>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QDesktopWidget>
#include "window.hpp"
#include "player.hpp"
#include "ki.hpp"
#include "controller.hpp"

namespace Ui {
class SetupWindow;
}

/**
 * @brief Die Klasse SetupWindow ist ein kleiner Einrichtungsassistent, um ein Spiel zu konfigurieren
 */
class SetupWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::SetupWindow *ui;

    /**
     * @brief Gibt die Anzahl der hinzugefügten Spieler an
     * @return Hinzugefügte Spieler
     */
    int getActualPlayerCount();

public:
    /**
     * @brief Konstruktor zum Erzeugen einer SetupWindow-Instanz
     * @param parent Elternteil des SetupWindows
     */
    explicit SetupWindow(QWidget *parent = 0);

    /**
      * @brief Destruktor zum Aufräumen einer SetupWindow-Instanz
      */
    ~SetupWindow();

private slots:
    /**
     * @brief Wird aufgerufen, wenn sich die Seite ändert
     * @param arg1 Seite
     */
    void on_stackedWidget_currentChanged(int arg1);

    /**
     * @brief Wird aufgerufen, wenn der "Zurück"-Button geklickt wird
     */
    void on_commandLinkButton_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Abbrechen"-Button geklickt wird
     */
    void on_commandLinkButton_2_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Spieler hinzufügen"-Button geklickt wird
     */
    void on_pushButton_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Spieler entfernen"-Button geklickt wird
     */
    void on_pushButton_2_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Lokales Spiel"-Button geklickt wird
     */
    void on_pushButton_3_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Online Spiel"-Button geklickt wird
     */
    void on_pushButton_4_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Beitreten"-Button geklickt wird
     */
    void on_pushButton_5_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Beitreten"-Button geklickt wird
     */
    void on_pushButton_6_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Erstellen"-Button geklickt wird
     */
    void on_pushButton_7_clicked();

    /**
     * @brief Wird aufgerufen, wenn der "Fertig"-Button geklickt wird
     */
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
};
