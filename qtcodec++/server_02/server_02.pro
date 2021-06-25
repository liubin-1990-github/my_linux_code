TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    ../threadpool/threadpool.c
LIBS += -lpthread

HEADERS += \
    ../threadpool/threadpool.h
INCLUDEPATH +="/home/barkly/qtcodedir/qtcodec++"
