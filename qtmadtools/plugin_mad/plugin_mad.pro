SOURCES += mad.c

TEMPLATE = lib

CONFIG += staticlib \
console
CONFIG -= stl \
qt \
thread
INSTALLS += target

MAKEFILE = /home/tyler/projects/qtmadtool/plugin_mad/Makefile

DESTDIR = ../bin/plugins

target.path = /usr/share/qtmadtool/plugins

TARGET = mad.so

