#-------------------------------------------------
#
# Project created by QtCreator 2019-01-24T04:48:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SubStringFinder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++17

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    indexing/indexerthread.cpp \
    indexing/indexer.cpp \
    indexing/indexerprogressdialog.cpp \
    serching/searcher.cpp

HEADERS += \
        mainwindow.h \
    indexing/indexerthread.h \
    indexing/indexer.h \
    indexing/indexerprogressdialog.h \
    serching/searcher.h

FORMS += \
        mainwindow.ui \
    indexing/indexerprogressdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
