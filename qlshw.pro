#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T09:41:36
#
#-------------------------------------------------

QT       += core gui

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
    autotooltipdelegate.h

FORMS    += qlshw.ui

RESOURCES += \
    icons.qrc
