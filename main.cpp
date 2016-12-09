#include "qlshw.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator qlshwTranslator;
    qlshwTranslator.load("qlshw_" +QLocale::system().name(), ":/languages");
    a.installTranslator(&qlshwTranslator);

    MainWindow w;

    w.show();

    return a.exec();
}


