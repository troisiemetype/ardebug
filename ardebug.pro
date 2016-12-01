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
    pair.cpp \
    suppresspair.cpp \
    dialog.cpp \
    varsettings.cpp

HEADERS  += mainwindow.h \
            serialsettings.h \
    pair.h \
    suppresspair.h \
    dialog.h \
    varsettings.h

FORMS    += mainwindow.ui \
            serialsettings.ui \
    suppresspair.ui \
    dialog.ui \
    varsettings.ui
