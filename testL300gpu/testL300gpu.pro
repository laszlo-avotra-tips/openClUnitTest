include(gtest_dependency.pri)
include(cuda_dependency.pri)
include(openCl_dependency.pri)


TEMPLATE = app
CONFIG += console
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += thread

QT += core

HEADERS += \
    testL300GpuCode.h \
    vectoraddtestvector.h

SOURCES += \
        main.cpp \
        vectoraddtestvector.cpp

DISTFILES +=

RESOURCES += \
    l300GpuCode.qrc
