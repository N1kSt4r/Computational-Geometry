#include "widget.h"
#include "ui_widget.h"

#include <iostream>
#include <QBrush>

void Widget::mousePressEvent(QMouseEvent *event) {
    points.push_back(event->pos());
    repaint();
}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    if (in_poly) {
        painter.setBrush(Qt::red);
        in_poly = false;
    } else {
        painter.setBrush(Qt::white);
    }
    painter.drawPolygon(points.data(), points.size());
}

bool pointCheck(QPoint one, QPoint two, QPoint three, QPoint pos) {
    // Функция рассматривает точки
    // Первые три задают стороны многоугольника, которые идут подряд, четвертая - курсор

    if (two.y() == pos.y() && two.x() >= pos.x() && (one.y() - pos.y()) * (three.y() - pos.y()) < 0) {
        return true;
    }
    // Первые два условия указывают на то, что наш луч пересекает соединение двух сторон
    // Третье говорит о том, что другие концы лежат с разных сторон, относительно луча
    // То есть стороны образуют углы вида <, >, а луч проходит через сам угол

    if ((one.y() - pos.y()) * (two.y() - pos.y()) < 0) {
        if (one.x() >= pos.x() || two.x() >= pos.x()) {
            return one.x() + (two.x() - one.x()) * (pos.y() - one.y()) / (two.y() - one.y()) >= pos.x();
        }
    }
    // Этот блок проверяет пересечение только первой стороны, т.к. иначе мы бы рассматривали стороны по 2 раза
    // Первое условие говорит о том, что вершины стороны лежат с разных сторон, относительно луча
    // Второе условие, что хотя бы одна вершина находится правее чем наш указатель
    // Тогда посмотрим в каком соотношении разбивает луч наш отрезок: (pos.y() - one.y()) / (two.y() - one.y())
    // И к первой точке прибавим длину проекции отрезка на ось х умноженное на отношение,
    // т.е. найдем координату х точки пересечения. И если она правее или совпадает, то луч и отрезок пересекаются

    return false;
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    if (points.size() < 3) {
        // Если точки не образуют простой многоугольник - выходим
        return;
    }

    QPoint pos = event->pos();
    int counter = 0;

    for (size_t i = 2; i < points.size(); ++i) {
        counter += pointCheck(points[i - 2], points[i - 1], points[i], pos);
    }
    // Т.к. мы рассматриваем по 3 точки, то мы не можем рассмотреть все в цикле
    // Нужно отдельно рассмотреть предпоследнюю, последнюю и первую
    // и предпоследнюю, первую и вторую
    counter += pointCheck(points[points.size() - 2], points[points.size() - 1], points[0], pos);
    counter += pointCheck(points[points.size() - 1], points[0], points[1], pos);

    if (counter % 2 == 1) {
        in_poly = true;
    }
    repaint();
}

Widget::Widget() :
    QMainWindow(0), ui(std::make_unique<Ui::Widget>()) {
    ui->setupUi(this);
    setFixedSize(640, 480);
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    ui->pushButton->setGeometry(290, 10, 60, 25);
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(pushButton()));
}

void Widget::pushButton() {
    points.clear();
    repaint();
}

Widget::~Widget() {
}
