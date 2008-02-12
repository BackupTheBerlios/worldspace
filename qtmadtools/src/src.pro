SOURCES += main.cpp \
 plugins.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 opengl
TARGET = ../bin/qtmadtool

FORMS += mainView.ui

QT += opengl

DESTDIR = .

HEADERS += MyGLWidget.h \
 globals.h \
 structures.h \
 plugins.h

DEFINES += LINUX

RESOURCES += icon.qrc

