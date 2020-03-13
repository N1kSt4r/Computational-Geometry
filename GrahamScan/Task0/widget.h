#pragma once

#include <memory>
#include <vector>
#include <QPainter>
#include <QMouseEvent>
#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class Widget;
}

using Point = std::pair<int, int>;

class Widget : public QMainWindow {
    Q_OBJECT

public:
    explicit Widget();
    ~Widget();

private:
    bool in_poly = false;
    std::vector<QPoint> points;
    std::unique_ptr<Ui::Widget> ui;
    std::vector<QPoint> stack_shell;
    void paintEvent(QPaintEvent *event);

private slots:
    void Generate();
    void Check();
};
