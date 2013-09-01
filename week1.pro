#-------------------------------------------------
#
# Project created by QtCreator 2013-08-31T21:21:35
#
#-------------------------------------------------

QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++0x

TARGET = week1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mini.cpp \
    toolbar.cpp \
    mainwidget.cpp \
    calckernel.cpp \
    askwidget.cpp

HEADERS  += widget.h\
       fly.h \
    mini.h \
    toolbar.h \
    mainwidget.h \
    calckernel.h \
    askwidget.h

FORMS    += widget.ui

RESOURCES += \
    dada.qrc
