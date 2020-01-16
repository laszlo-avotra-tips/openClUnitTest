include(gtest_dependency.pri)
include(openCl_dependency.pri)
#include(staticLib_dependency.pri)
include(cuda_dependency.pri)


TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread

QT += core

HEADERS += \
        openclvectoradd.h \
        testCuda.h \
        testEnvironment.h \
        testOpenCl.h \
        testvector.h

SOURCES += \
        main.cpp \
        openclvectoradd.cpp \
        testvector.cpp

DISTFILES +=

RESOURCES += \
    openClCode.qrc
