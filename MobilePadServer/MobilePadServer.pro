QT = core network

TARGET = MobilePadServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    controller.cpp \
    commandexecutor.cpp

HEADERS += \
    server.h \
    controller.h \
    commandexecutor.h

