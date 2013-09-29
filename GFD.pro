#-------------------------------------------------
#
# Project created by QtCreator 2013-09-27T18:19:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = GFD
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    gfd.cpp \
    gfdvar.cpp \
    gfdvarint.cpp \
    gfdvarstring.cpp \
    gfdvarbool.cpp \
    gfdvardouble.cpp \
    gfdvararray.cpp \
    gfdvarobject.cpp

HEADERS += \
    gfd.h \
    gfdvar.h \
    gfdvarint.h \
    gfdvarstring.h \
    gfdvarbool.h \
    gfdvardouble.h \
    gfdvararray.h \
    gfdvarobject.h

QMAKE_CXXFLAGS += -std=c++0x
