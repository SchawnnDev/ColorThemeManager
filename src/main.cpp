#include "include/Widgets/mainwindow.h"
#include "include/colorPair.h"
#include <QApplication>
#include <QDebug>

void test() {
    QColor color = ColorPair::fromRGBA("#7f11e011");
    qDebug() << ColorPair::toRGBA(color);
    qDebug() << "a=" << color.alpha() << ", r=" << color.red() << ", g=" << color.green() << ", b=" << color.blue()
             << ".";
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    test();
    return QApplication::exec();
}
