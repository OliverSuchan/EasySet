#include "cardwidget.hpp"

QPainterPath CardWidget::makePath(int p_ypos)
{
    QPainterPath form = QPainterPath();
    QRectF rect = QRectF((this->width() - this->height() / 6) / 2, p_ypos, this->height() / 6, this->height() / 6);
    switch(m_shape)
    {
    case TRIANGLE:
        form.moveTo(rect.left() + (rect.width() / 2), rect.top());
        form.lineTo(rect.bottomLeft());
        form.lineTo(rect.bottomRight());
        form.lineTo(rect.left() + (rect.width() / 2), rect.top());
        break;

    case SQUARE:
        form.addRect(rect);
        break;

    case CIRCLE:
        form.addEllipse(rect);
        break;
    }
    return form;
}

void CardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    if(!m_isClicked.load())
    {
        if(m_mouseOver.load())
            painter.setBrush(Qt::lightGray);
        else
            painter.setBrush(Qt::white);
    }
    else
        painter.setBrush(Qt::gray);
    painter.drawRoundedRect(0, 0, this->width() - painter.pen().width(), this->height() - painter.pen().width(), 10, 10);
    Qt::BrushStyle bs;
    switch(m_opacity)
    {
    case FILLED:
        bs = Qt::SolidPattern;
        break;

    case EMPTY:
        bs = Qt::NoBrush;
        break;

    case PALLID:
        bs = Qt::Dense5Pattern;
        break;
    }
    QPen pen(setColors[m_color]);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(QBrush(setColors[m_color], bs));

    switch(m_number)
    {
    case ONE:
        painter.drawPath(makePath(this->height() / 2 - this->height() / 12));
        break;

    case TWO:
        painter.drawPath(makePath(this->height() / 4));
        painter.drawPath(makePath(this->height() / 2 + this->height() / 12));
        break;

    case THREE:
        painter.drawPath(makePath(this->height() / 4 - this->height() / 12));
        painter.drawPath(makePath(this->height() / 2 - this->height() / 12));
        painter.drawPath(makePath(this->height() * 3 / 4 - this->height() / 12));
        break;
    }
}

void CardWidget::mousePressEvent(QMouseEvent *)
{
    if(m_canClick.load())
    {
        m_isClicked.store(!m_isClicked.load());
        repaint();
        emit clicked();
    }
}

void CardWidget::leaveEvent(QEvent *)
{
    m_mouseOver.store(false);
    repaint();
}

void CardWidget::enterEvent(QEvent *)
{
    if(!m_isClicked.load())
    {
        m_mouseOver.store(true);
        repaint();
    }
}

CardWidget::CardWidget(short p_color, short p_shape, short p_number, short p_opacity, QWidget *parent) :
    QWidget(parent),
    Card(p_color, p_shape, p_number, p_opacity)
{
    this->setMouseTracking(true);
    m_canClick.store(true);
    m_isClicked.store(false);
    m_mouseOver.store(false);
}

void CardWidget::unselect()
{
    m_isClicked.store(false);
    repaint();
}

void CardWidget::canClick(bool p_val)
{
    m_canClick.store(p_val);
}
