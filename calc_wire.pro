#-------------------------------------------------
#
# Project created by QtCreator 2011-10-13T10:16:02
#
#-------------------------------------------------

QT       += core gui printsupport
CONFIG += qwt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calc_wire
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vol.cpp \
    plot.cpp

HEADERS  += mainwindow.h \
    vol.h \
    plot.h

FORMS    +=
LIBS += -lqwt-qt5
#INCLUDEPATH += /usr/include/qt5/qwt


















