#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPainter>
#include <QMouseEvent>
#include <memory>
#include <vector>

namespace Ui {
class Widget;
}

class Widget : public QMainWindow {
    Q_OBJECT

public:
    explicit Widget();
    ~Widget();

private:
    bool in_poly = false;
    std::vector<QPoint> points;
    std::unique_ptr<Ui::Widget> ui;
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

private slots:
    void pushButton();
};
