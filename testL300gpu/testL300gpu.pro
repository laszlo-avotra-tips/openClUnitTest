include(gtest_dependency.pri)
include(cuda_dependency.pri)
include(openCl_dependency.pri)


TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread

QT += core

HEADERS += \
    rescalekernel.h \
    testL300GpuCode.h \
    vectoraddtestvector.h

SOURCES += \
        main.cpp \
        rescalekernel.cpp \
        vectoraddtestvector.cpp

DISTFILES +=

RESOURCES += \
    l300GpuCode.qrc
