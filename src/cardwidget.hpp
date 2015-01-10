#pragma once

#include <atomic>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "card.hpp"

/**
 * @brief Die grafische Implementierung der Klasse Card
 * @see Card
 */
class CardWidget : public QWidget, public Card
{
    Q_OBJECT

private:
    /**
     * @brief Thread-sicherer Wahrheitswert der angibt, ob die aktuelle Karte angeklickt werden kann
     */
    std::atomic<bool> m_canClick;

    /**
     * @brief Thread-sicherer Wahrheitswert der angibt, ob die aktuelle karte angeklickt wurde
     */
    std::atomic<bool> m_isClicked;

    /**
     * @brief Thread-sicherer Wahrheitswert der angibt, ob der MouseOver-Effekt aktiv ist
     */
    std::atomic<bool> m_mouseOver;

    /**
     * @brief Erzeugt Grafikobjekte in Form des Kartenattributs "Form"
     * @param p_ypos Y-Position des Grafikobjekts
     * @return Grafikobjekt
     */
    QPainterPath makePath(int p_ypos);

    /**
     * @brief Die paint-Loop.<BR>
     * Ist für das Zeichnen der Karten zuständig
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Mausklick-Event, wird bei einem Mausklick aufgerufen
     */
    void mousePressEvent(QMouseEvent *);

    /**
     * @brief Wird aufgerufen, sobald die Maus das Steuerelement verlässt
     */
    void leaveEvent(QEvent *);

    /**
     * @brief Wird aufgerufen, sonald die Maus auf das Steuerelement bewegt wird
     */
    void enterEvent(QEvent *);

public:
    /**
     * @brief Konstruktor um eine CardWidget-Instanz zu erzeugen
     * @param p_color Farbe des CardWudgets
     * @param p_shape Form des CardWidgets
     * @param p_number Anzahl des CardWidgets
     * @param p_opacity Einfärbung des CardWidgets
     * @param parent Elternteil des CardWidgets
     * @see Color
     * @see Shape
     * @see Number
     * @see Opacity
     */
    explicit CardWidget(short p_color, short p_shape, short p_number, short p_opacity, QWidget *parent = 0);

signals:
    /**
     * @brief Signal das emittiert wird, sobald ein Mausklick durchgeführt wird
     */
    void clicked();

public slots:
    /**
     * @brief Wird aufgerufen, wenn eine Karte "entwählt" werden soll
     */
    void unselect();

    /**
     * @brief Wird aufgerufen, um festzulegen, ob man das CardWidgets anklicken kann oder eben nicht
     * @param p_val Wahrheitswert der angibt, ob man das CardWidgets anklicken kann
     */
    void canClick(bool p_val);

};
