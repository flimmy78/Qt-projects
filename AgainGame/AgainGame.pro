#-------------------------------------------------
#
# Project created by QtCreator 2011-07-25T08:28:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AgainGame
TEMPLATE = app


SOURCES += main.cpp\
        againgame.cpp \
    board.cpp

HEADERS  += againgame.h \
    board.h

FORMS    += againgame.ui

RESOURCES += \
    picture.qrc
