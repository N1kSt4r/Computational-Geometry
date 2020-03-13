#include "widget.h"
#include "ui_widget.h"

#include <random>
#include <iostream>

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QPen(QColor(0, 255, 255, 120), 4));
    painter.setBrush(Qt::NoBrush);
    painter.drawPolygon(stack_shell.data(), stack_shell.size());

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(0, 178, 255, 50)));
    for (auto& point : points) {
        painter.drawEllipse(point, 4, 4);
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
        static std::uniform_int_distribution<int> pos_x(20, 610), pos_y(40, 460);
        static std::normal_distribution<> pos_xx(315, 60), pos_yy(250, 40);
        points.resize(ui->lineEdit->text().toInt());

        for (auto& point : points) {
            // pos_xx, pos_yy - нормальное распределение
            // pos_x, pos_y - равномерное распределение
            point = QPoint(pos_xx(gen), pos_yy(gen));
        }
    }
    stack_shell.clear();
    repaint();
}

int OrientedDirection(const QPoint& begin, const QPoint& end, const QPoint& point) {
    auto diff1 = begin - end;
    auto diff2 = point - end;
    return diff1.y() * diff2.x() - diff1.x() * diff2.y();
}

void Widget::Check() {
    stack_shell.clear();
    std::nth_element(points.begin(), points.begin(), points.end(),
                     [](const QPoint& one, const QPoint& two) {
        return std::make_pair(one.x(), one.y()) < std::make_pair(two.x(), two.y());
    });

    if (!points.empty()) {
        std::sort(++points.begin(), points.end(),
        [base{points.front()}](const QPoint& one, const QPoint& two) -> bool {
            return OrientedDirection(base, one, two) < 0;
        });
    }

    for (size_t i = 0; i < std::min((size_t)2, points.size()); ++i) {
        stack_shell.push_back(points[i]);
    }
    for (size_t i = 2; i < points.size(); ++i) {
        while (OrientedDirection(stack_shell[stack_shell.size() - 2], stack_shell.back(), points[i]) >= 0) {
            stack_shell.pop_back();
        }
        stack_shell.push_back(points[i]);
    }
    repaint();
}

Widget::~Widget() {
}
