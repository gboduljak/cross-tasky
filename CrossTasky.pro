#-------------------------------------------------
#
# Project created by QtCreator 2014-08-23T16:33:20
#
#-------------------------------------------------

QT       += core gui sql
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CrossTasky
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    db.cpp\
    todo.cpp \
    createtodo.cpp \
    tododetailsdialog.cpp \
    tableviewdialog.cpp \
    todoeditdialog.cpp


HEADERS  += mainwindow.h \
    task.h \
    db.h \
    todo.h \
    createtodo.h \
    tododetailsdialog.h \
    tableviewdialog.h \
    todoeditdialog.h


FORMS    += mainwindow.ui \
    createtodo.ui \
    tododetailsdialog.ui \
    tableviewdialog.ui \
    todoeditdialog.ui

RESOURCES += \
    resource.qrc


win32:RC_ICONS += icon.ico
RC_FILE = icon-resource.rc

OTHER_FILES += \
    icon-resource.rc
