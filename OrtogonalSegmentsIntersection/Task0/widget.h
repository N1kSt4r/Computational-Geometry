#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPainter>
#include <QMouseEvent>
#include <memory>
#include <vector>

namespace Ui { class Widget; }

using Segment = std::pair<std::pair<int, int>, std::pair<int, int>>;

class Widget : public QMainWindow {
    Q_OBJECT

public:
    explicit Widget();
    ~Widget();

private:
    std::vector<Segment> segments;
    std::vector<char> intersection;
    std::unique_ptr<Ui::Widget> ui;
    void paintEvent(QPaintEvent *event);

private slots:
    void Generate();
    void Check();
};
