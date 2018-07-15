QT += opengl
QT += widgets
QT += gui
QT += core gui

LIBS += -lopengl32 \
        -lglu32 \
        -lglut

HEADERS += \
    oglwidget.h

SOURCES += \
    oglwidget.cpp \
    main.cpp
