#
BUILD:=$(shell echo $$((`cat VERSION`+1)) )
UPDATEV:= $(shell echo $$((`cat VERSION`+1)) >VERSION )

CC := gcc
CCPP := c++
RANLIB ?= ranlib
LIBS ?=
SHAREDLIBS ?=
CFLAGS ?= -O
LDFLAGS ?=
SHAREDFLAGS ?= -shared
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include
MANDIR ?= $(PREFIX)/man
CONFDIR ?= $(PREFIX)/etc
INSTALL_GROUP ?= root
INSTALL_USER ?= root
SHAREDFLAGS := $(SHAREDFLAGS)
LIBS := $(LIBS) -lX11 -lXi -lXmu  -lGL  -lm -lpthread -lSDL -lXxf86dga -lXv -lGLU
SHAREDLIBS := $(SHAREDLIBS)
CFLAGS := $(CFLAGS) -g -ggdb    -Wall -D_LINUX -DBUILD=$(BUILD)
LDFLAGS := -L/usr/X11R6/lib -L/usr/lib $(LDFLAGS)

CXXFLAGS := $(CXXFLAGS) $(CFLAGS) -I. -I./lang -I./w3dsrc -I./w3dsrc/ui -I./w3dsrc/gfx -I./w3dsrc/bios -I./w3dsrc/display -I./w3dsrc/input -I./w3dsrc/engine
CFLAGS := $(CFLAGS) -I. -I./lang -I./w3dsrc -I./w3dsrc/ui -I./w3dsrc/gfx -I./w3dsrc/bios -I./w3dsrc/display -I./w3dsrc/input -I./w3dsrc/engine
ALL: w3d_x86.exe
	gcc $(CFLAGS) -c ./w3dsrc/bios/bios.c -o ./w3dsrc/bios/bios.o
main.o: w3dsrc/main.c w3dsrc/bios.h w3dsrc/w3d_base.h
	gcc $(CFLAGS) -c ./w3dsrc/main.c -o ./w3dsrc/main.o

w3d_x86.exe :./w3dsrc/bios/bios.o ./w3dsrc/main.o 
	g++ -I./w3d/ui/libgli/include -o w3d_x86.exe  ./w3dsrc/bios/bios.o ./w3dsrc/main.o   $(LIBS) $(LDFLAGS)  
	 mv w3d_x86.exe ..
clean:
	find -name '*.o'|xargs rm -f ;rm  ../w3d_x86.exe
