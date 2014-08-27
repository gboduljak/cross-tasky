#-------------------------------------------------
#
# Project created by QtCreator 2014-08-23T16:33:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CrossTasky
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    db.cpp\
    todo.cpp \
    createtodo.cpp


HEADERS  += mainwindow.h \
    task.h \
    db.h \
    todo.h \
    createtodo.h


FORMS    += mainwindow.ui \
    createtodo.ui

RESOURCES += \
    resource.qrc
