#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include "paintscene.h"
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
    std::unique_ptr<Ui::Widget> ui;
    std::unique_ptr<QGraphicsScene> scene;
    std::unique_ptr<PaintScene> paint_scene;
    std::vector<std::pair<int, int>> points;

private slots:
    void pushButton();
};
