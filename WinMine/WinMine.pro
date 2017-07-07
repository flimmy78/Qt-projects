#-------------------------------------------------
#
# Project created by QtCreator 2011-07-23T19:22:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WinMine
TEMPLATE = app


SOURCES += main.cpp\
        winmine.cpp \
    board.cpp

HEADERS  += winmine.h \
    board.h

FORMS    += winmine.ui

RESOURCES += \
    img.qrc
