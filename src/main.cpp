#include "include/Widgets/mainwindow.h"
#include "include/xmlReader.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

/*    QTranslator translator;
    if (translator.load(QLocale::system(), u"myapp"_qs, u"_"_qs, u":/i18n"_qs))
        a.installTranslator(&translator);*/

    MainWindow w;
    w.show();
    return QApplication::exec();
}
