#-------------------------------------------------
#
# Project created by QtCreator 2016-11-30T13:57:00
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ardebug
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           serialsettings.cpp \
    pair.cpp

HEADERS  += mainwindow.h \
            serialsettings.h \
    pair.h

FORMS    += mainwindow.ui \
            serialsettings.ui
