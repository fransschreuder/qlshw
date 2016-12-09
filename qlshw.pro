#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T09:41:36
#
#-------------------------------------------------

QT       += core gui
TRANSLATIONS += languages/qlshw_nl_NL.ts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qlshw
TEMPLATE = app


SOURCES += main.cpp\
        qlshw.cpp \
    treeitem.cpp \
    treemodel.cpp \
    autotooltipdelegate.cpp

HEADERS  += qlshw.h \
    treeitem.h \
    treemodel.h \
    autotooltipdelegate.h \
    version.h

FORMS    += qlshw.ui

RESOURCES += \
    icons.qrc

isEmpty(PREFIX) {
 PREFIX = /usr
}

DESK.files = qlshw.desktop
DESK.path = $${PREFIX}/share/applications

ICO.files = qlshw.svg
ICO.path = $${PREFIX}/share/pixmaps

target.path = $${PREFIX}/bin

INSTALLS += target
INSTALLS += ICO
INSTALLS += DESK

