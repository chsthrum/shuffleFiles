#-------------------------------------------------
#
# Project created by QtCreator 2017-05-30T23:33:45
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = shuffleFiles
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += c++11


CONFIG += link_pkgconfig
PKGCONFIG += opencv


SOURCES += main.cpp
