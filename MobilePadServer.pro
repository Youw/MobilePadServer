QT = core network

TARGET = MobilePadServer
CONFIG += console
CONFIG -= app_bundle
DESTDIR = $$PWD/bin

TEMPLATE = app

win32:LIBS += -lUser32

SOURCES += \
    main.cpp \
    server.cpp \
    controller.cpp \
    commandexecutor.cpp

win32:SOURCES += \
    commandexecutor_win.cpp

HEADERS += \
    server.h \
    controller.h \
    commandexecutor.h

