#-------------------------------------------------
#
# Project created by QtCreator 2011-06-06T12:31:06
#
#-------------------------------------------------

QT       += core gui network

TARGET = DemoBlogger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    postframe.cpp \
    commentframe.cpp

HEADERS  += mainwindow.h \
    postframe.h \
    commentframe.h

FORMS    += mainwindow.ui \
    postframe.ui \
    commentframe.ui

RESOURCES += \
    bloggerres.qrc

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lqtgdata
