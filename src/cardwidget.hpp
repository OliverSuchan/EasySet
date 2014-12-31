#pragma once

#include <atomic>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "card.hpp"

class CardWidget : public QWidget, public Card
{
    Q_OBJECT

private:
    std::atomic<bool> m_canClick;
    std::atomic<bool> m_isClicked;
    std::atomic<bool> m_mouseOver;
    QPainterPath makePath(int p_ypos);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);

public:
    explicit CardWidget(short p_color, short p_shape, short p_number, short p_opacity, QWidget *parent = 0);

signals:
    void clicked();

public slots:
    void unselect();
    void canClick(bool p_val);

};
