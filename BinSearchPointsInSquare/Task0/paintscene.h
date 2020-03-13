#pragma once

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include <memory>
#include "rectanglearea.h"
#include <vector>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QLineEdit>
#include <iostream>
#include <sstream>
#include <string>

class PaintScene : public QObject, public QGraphicsItem {
    Q_OBJECT
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void paintRedPoints();
    void paintBlackPointsIf();

public:
    ~PaintScene();
    void paintBlackPoints();
    explicit PaintScene(QGraphicsScene* scene_, QLineEdit* out, std::vector<std::pair<int, int>>* points);

private:
    QPointF one, two;
    QGraphicsScene* scene;
    QBrush red_brush, black_brush;
    std::unique_ptr<RectangleArea> rect;
    std::vector<std::pair<int, int>>* points;
    QLineEdit* out;
};
