include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_testmetaiot_ide.h\
    ./QT_Work0/increment.h


SOURCES += \
        main.cpp
