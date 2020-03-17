TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++14

LIBS += /usr/lib/x86_64-linux-gnu/libOpenCL.so


SOURCES += main.cpp

DISTFILES += \
    arr_process_00.cl
