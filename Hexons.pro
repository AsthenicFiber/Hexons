#QT += core
#QT -= gui
QT += widgets
QT += multimedia

CONFIG += c++11

TARGET = Hexons
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    controlwindow.cpp \
    hexon.cpp \
    hex.cpp \
    map.cpp \
    hexitem.cpp \
    obstacle.cpp \
    matrix.cpp \
    nnbase.cpp \
    food.cpp

HEADERS += \
    controlwindow.h \
    hexon.h \
    hex.h \
    map.h \
    hexitem.h \
    obstacle.h \
    matrix.h \
    nnbase.h \
    food.h

FORMS += \
    controlwindow.ui

DISTFILES += \
    lost_woods.wav \
    song_of_storms5.wav
