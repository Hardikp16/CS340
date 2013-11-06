#-------------------------------------------------
#
# Project created by QtCreator 2013-10-30T21:56:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fotoshop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workingwindow.cpp \
    UndoArray.cpp

HEADERS  += mainwindow.h \
    workingwindow.h \
    includes.h

FORMS    += mainwindow.ui \
    workingwindow.ui

RESOURCES += \
    Images/Images.qrc
    Images/blank.jpg
