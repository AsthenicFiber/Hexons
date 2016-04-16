#QT += core
#QT -= gui
QT += widgets

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
    nnbase.cpp

HEADERS += \
    controlwindow.h \
    hexon.h \
    hex.h \
    map.h \
    hexitem.h \
    obstacle.h \
    matrix.h \
    nnbase.h

FORMS += \
    controlwindow.ui
