#include "widget.h"
#include "ui_widget.h"

#include "paintscene.h"
#include <iostream>
#include <random>

std::vector<std::pair<int, int>> GetRandomPoints(int size) {
    std::vector<std::pair<int, int>> points(size);
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> dist_x(5, 635), dist_y(5, 430);
    for (auto& point : points) {
        point.first = dist_x(gen);
        point.second = dist_y(gen);
    }
    return points;
}

Widget::Widget() :
    QMainWindow(0), ui(std::make_unique<Ui::Widget>()) {
    ui->setupUi(this);
    setFixedSize(640, 480);

    scene = std::move(std::make_unique<QGraphicsScene>(this));   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов

    ui->graphicsView->resize(640, 480);  // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene.get());  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    ui->lineEdit->setGeometry(565, 5, 70, 25);
    ui->lineEdit_2->setGeometry(5, 5, 70, 25);
    ui->pushButton->setGeometry(525, 5, 35, 25);
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(pushButton()));

    scene->setSceneRect(0, 0, 640, 460); // Устанавливаем размер сцены
    paint_scene = std::move(std::make_unique<PaintScene>(scene.get(), ui->lineEdit_2, &points));
    paint_scene->setPos(0, 0);
    scene->addItem(paint_scene.get());
}

void Widget::pushButton() {
    if (ui->lineEdit->text().size() > 0) {
        points = GetRandomPoints(ui->lineEdit->text().toInt());
        paint_scene->paintBlackPoints();
    }
}

Widget::~Widget() {
}
