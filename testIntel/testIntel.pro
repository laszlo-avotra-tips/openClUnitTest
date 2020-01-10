include(gtest_dependency.pri)
include(openCl_dependency.pri)


TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread

QT += core

HEADERS += \
        openclsamplecode.h \
        testSampleCode.h \
        testvector.h

SOURCES += \
        main.cpp \
        openclsamplecode.cpp \
        testvector.cpp

DISTFILES +=
