#include "widget.h"
#include "ui_widget.h"

#include <iostream>
#include <random>
#include <QBrush>

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QColor(0, 0, 255, 120));
    for (auto& segment : segments) {
        painter.drawLine(segment.first.first, segment.first.second,
                         segment.second.first, segment.second.second);
    }

    painter.setPen(QColor(255, 0, 50, 120));
    for (size_t i = 0; i < segments.size(); ++i) {
        if (intersection[i]) {
            painter.drawLine(segments[i].first.first, segments[i].first.second,
                             segments[i].second.first, segments[i].second.second);
        }
    }
}

Widget::Widget() :
    QMainWindow(0), ui(std::make_unique<Ui::Widget>()) {
    ui->setupUi(this);
    setFixedSize(640, 480);

    ui->pushButton->setGeometry(190, 10, 70, 25);
    ui->lineEdit->setGeometry(280, 10, 80, 25);
    ui->pushButton_2->setGeometry(380, 10, 70, 25);

    connect(ui->pushButton, SIGNAL(released()), this, SLOT(Generate()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(Check()));
}

void Widget::Generate() {
    if (ui->lineEdit->text().size() > 0) {
        static std::mt19937 gen(std::random_device().operator()());
        static std::uniform_int_distribution<int> pos_x(0, 630), pos_y(0, 480), len(6, 26), angle(0, 2);
        segments.resize(ui->lineEdit->text().toInt());
        intersection.assign(segments.size(), false);
        for (auto& segment : segments) {
            segment.first.first = pos_x(gen);
            segment.first.second = pos_y(gen);
            segment.second = segment.first;
            if (angle(gen)) {
                segment.second.first += len(gen);
            } else {
                segment.second.second += len(gen);
            }
        }
    }
    repaint();
}

bool intersect_proection (int a, int b, int c, int d) {
    if (a > b)  std::swap(a, b);
    if (c > d)  std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

bool intersect (Segment a, Segment b) {
    return intersect_proection (a.first.first, a.second.first,
                                b.first.first, b.second.first)
        && intersect_proection (a.first.second, a.second.second,
                                b.first.second, b.second.second);
}

void Widget::Check() {
    for (size_t i = 0; i < segments.size(); ++i) {
        for (size_t j = i + 1; j < segments.size(); ++j) {
            if (intersect(segments[i], segments[j])) {
                intersection[i] = intersection[j] = true;
            }
        }
    }
    repaint();
}

Widget::~Widget() {
}
