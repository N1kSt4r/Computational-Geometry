#include "paintscene.h"
#include "rectanglearea.h"

PaintScene::PaintScene(QGraphicsScene* scene_, QLineEdit* out_, std::vector<std::pair<int, int>>* points_)
    : QObject(0), QGraphicsItem(), scene(scene_), points(points_), out(out_) {
    QColor color = Qt::black;
    color.setAlphaF(1./3);
    black_brush = QBrush(color);
    color = Qt::red;
    color.setAlphaF(1./3);
    red_brush = QBrush(color);
    paintBlackPoints();
}

PaintScene::~PaintScene() {
}

QRectF PaintScene::boundingRect() const {
    return QRectF (0, 0, 640, 460);
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    one = event->scenePos();
}

void PaintScene::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (rect && rect->end_moving) {
        rect->end_moving = false;
        paintBlackPointsIf();
        paintRedPoints();
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    two = event->scenePos();
    if (rect != nullptr) {
        scene->removeItem(rect.get());
        scene->addRect(0, 0, 640, 480, QPen(Qt::white), QBrush(Qt::white));
        paintBlackPoints();
    }
    if (one.rx() > two.rx()) {
        std::swap(one.rx(), two.rx());
    }
    if (one.ry() > two.ry()) {
        std::swap(one.ry(), two.ry());
    }
    rect = std::move(std::make_unique<RectangleArea>(one, two));
    rect->end_moving = true;
    scene->addItem(rect.get());
}

void PaintScene::paintBlackPoints() {
    scene->addRect(0, 0, 640, 480, QPen(Qt::white), QBrush(Qt::white));
    for (auto point : *points) {
        scene->addEllipse(point.first - 2, point.second - 2, 4, 4, Qt::NoPen, black_brush);
    }
}

void PaintScene::paintBlackPointsIf() {
    QPointF pos = rect->coords;
    QPointF one = pos + rect->one;
    QPointF two = pos + rect->two;
    one -= QPointF(6, 6);
    two += QPointF(6, 6);
    scene->addRect(QRectF(one, two), Qt::NoPen, Qt::white);
    for (auto point : *points) {
        if (point.first > one.x() && point.first < two.x() &&
                point.second > one.y() && point.second < two.y()) {
            scene->addEllipse(point.first - 2, point.second - 2, 4, 4, Qt::NoPen, black_brush);
        }
    }
}

void PaintScene::paintRedPoints() {
    QPointF pos = rect->pos();
    QPointF one = pos + rect->one;
    QPointF two = pos + rect->two;
    scene->addRect(QRectF(one, two), Qt::NoPen, Qt::white);

    int counter = 0;

    for (auto point : *points) {
        if (point.first > one.x() && point.first < two.x() &&
                point.second > one.y() && point.second < two.y()) {
            scene->addEllipse(point.first - 2, point.second - 2, 4, 4, Qt::NoPen, red_brush);
            ++counter;
        }
    }

    scene->addRect(QRectF(one, two), QPen(Qt::black, 5));
    out->setText(QString::number(counter));
}
