TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    threadpool.c
LIBS +=-lpthread

HEADERS += \
    threadpool.h
