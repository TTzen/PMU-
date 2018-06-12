#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T16:19:42
#
#-------------------------------------------------

QT       += core gui network

CONFIG	 += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = upper
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += power_parameter

SOURCES += \
        main.cpp \
        widget.cpp \
    power_parameter/currentSignal.cpp \
    power_parameter/PowerQuality.cpp \
    power_parameter/voltageSignal.cpp

HEADERS += \
        widget.h \
    power_parameter/currentSignal.h \
    power_parameter/PowerQuality.h \
    power_parameter/voltageSignal.h

FORMS += \
        widget.ui
