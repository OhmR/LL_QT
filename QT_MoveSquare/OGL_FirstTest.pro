QT += opengl
QT += widgets
QT += gui
QT += core gui

win32{
    LIBS += -lGl  -lglu32  -lglut
}
# The opengl link name is different in Linux platform
linux-g++ {
    LIBS += -lglut -lGL -lGLU
}
HEADERS += \
    oglwidget.h

SOURCES += \
    oglwidget.cpp \
    main.cpp
