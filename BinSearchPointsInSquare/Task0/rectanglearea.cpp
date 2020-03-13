#include "rectanglearea.h"

RectangleArea::RectangleArea(QPointF one_, QPointF two_) : QObject(0), QGraphicsItem(), one(one_), two(two_){
}
RectangleArea::~RectangleArea() {
}

QRectF RectangleArea::boundingRect() const {
    return QRectF(one, two);
}

void RectangleArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::black, 5));
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void RectangleArea::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    start_moving = true;
    mouseCoords = event->pos();
    coords = pos();
    setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void RectangleArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    setCursor(QCursor(Qt::ArrowCursor));
    setPos(mapToScene(event->pos()) - mouseCoords);
    end_moving = true;
    Q_UNUSED(event);
}
