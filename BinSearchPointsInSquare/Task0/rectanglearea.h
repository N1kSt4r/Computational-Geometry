#pragma once

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QCursor>

class RectangleArea : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    QPointF one, two;
    bool end_moving = false;
    bool start_moving = false;
    QPointF mouseCoords, coords;

public:
    ~RectangleArea();
    explicit RectangleArea(QPointF one_, QPointF two_);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};
