#-------------------------------------------------
#
# Project created by QtCreator 2015-01-27T20:25:46
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spanzuratoarea
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    code.cpp \
    secdialog.cpp \
    thirddialog.cpp \
    admindialog.cpp

HEADERS  += mainwindow.h \
    secdialog.h \
    thirddialog.h \
    admindialog.h

FORMS    += mainwindow.ui \
    secdialog.ui \
    thirddialog.ui \
    admindialog.ui

DISTFILES +=

RC_ICONS += icon.ico
