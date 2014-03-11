#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T13:17:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assignment2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generator.cpp \
    runner.cpp \
    operator.cpp \
    watchdog.cpp

HEADERS  += mainwindow.h \
    generator.h \
    runner.h \
    operator.h \
    watchdog.h

FORMS    += mainwindow.ui
