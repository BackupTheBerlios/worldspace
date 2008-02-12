TEMPLATE = lib

CONFIG += staticlib

CONFIG -= stl \
qt \
thread
DESTDIR = .

MAKEFILE = /home/tyler/projects/qtmadtool/plugin_3ds/Makefile

SOURCES += 3ds.c \
l3ds.cpp
HEADERS += l3ds.h

