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

CXXFLAGS := $(CXXFLAGS) $(CFLAGS) -I./w3d/ui/libgli/include
ALL: w3d_x86.exe
fuentes.o: w3d/gfx/fuentes.c w3d/opengl.h w3d/global.h w3d/bios/bios.h \
  w3d/definiciones.h w3d/gfx/gfx_carga_img.h w3d/gfx/fuentes.h
	gcc $(CFLAGS) -c ./w3d/gfx/fuentes.c -o ./w3d/gfx/fuentes.o
gfx_carga_img.o: w3d/gfx/gfx_carga_img.c w3d/opengl.h w3d/global.h \
  w3d/bios/bios.h w3d/definiciones.h
	gcc $(CFLAGS) -c ./w3d/gfx/gfx_carga_img.c -o ./w3d/gfx/gfx_carga_img.o
bios.o: w3d/bios/bios.c w3d/global.h w3d/bios/bios.h w3d/definiciones.h
	gcc $(CFLAGS) -c ./w3d/bios/bios.c -o ./w3d/bios/bios.o
display.o: w3d/display/display.c w3d/display/display.h \
  w3d/display/init_gl.h w3d/opengl.h w3d/global.h w3d/bios/bios.h \
  w3d/definiciones.h
	gcc $(CFLAGS) -c ./w3d/display/display.c -o ./w3d/display/display.o
init_gl.o: w3d/display/init_gl.c w3d/opengl.h w3d/global.h \
  w3d/bios/bios.h w3d/definiciones.h w3d/engine/mad.h \
  w3d/engine/estructuras.h w3d/display/logo.h
	gcc $(CFLAGS) -c ./w3d/display/init_gl.c -o ./w3d/display/init_gl.o
logo.o: w3d/display/logo.c w3d/opengl.h
	gcc $(CFLAGS) -c ./w3d/display/logo.c -o ./w3d/display/logo.o
teclado.o: w3d/input/teclado.c w3d/opengl.h
	gcc $(CFLAGS) -c ./w3d/input/teclado.c -o ./w3d/input/teclado.o
espacio.o: w3d/engine/espacio.c w3d/global.h w3d/bios/bios.h \
  w3d/definiciones.h w3d/engine/estructuras.h w3d/opengl.h \
  w3d/gfx/gfx_carga_img.h
	gcc $(CFLAGS) -c ./w3d/engine/espacio.c -o ./w3d/engine/espacio.o
mad.o: w3d/engine/mad.c w3d/engine/mad.h w3d/engine/estructuras.h \
  w3d/global.h w3d/bios/bios.h w3d/definiciones.h w3d/opengl.h \
  w3d/engine/texturas.h
	gcc $(CFLAGS) -c ./w3d/engine/mad.c -o ./w3d/engine/mad.o
texturas.o: w3d/engine/texturas.c w3d/opengl.h w3d/bios/bios.h \
  w3d/gfx/gfx_carga_img.h
	gcc $(CFLAGS) -c ./w3d/engine/texturas.c -o ./w3d/engine/texturas.o
engine.o: w3d/engine/engine.c w3d/opengl.h w3d/global.h w3d/bios/bios.h \
  w3d/definiciones.h w3d/engine/estructuras.h w3d/engine/espacio.h
	gcc $(CFLAGS) -c ./w3d/engine/engine.c -o ./w3d/engine/engine.o
main.o: w3d/main.c w3d/global.h w3d/bios/bios.h w3d/definiciones.h \
  w3d/display/display.h w3d/gfx/fuentes.h w3d/opengl.h w3d/ui/w3d_ui.h \
  w3d/engine/engine.h
	gcc $(CFLAGS) -c ./w3d/main.c -o ./w3d/main.o
w3d_ui.o: w3d/ui/w3d_ui.cpp w3d/ui/libgli/include/gli.h \
  w3d/ui/libgli/include/gli_types.h w3d/ui/libgli/include/gli_object.h \
  w3d/ui/libgli/include/gli_glf.h w3d/ui/libgli/include/gli_button.h \
  w3d/ui/libgli/include/gli_text.h w3d/ui/libgli/include/gli_editbox.h \
  w3d/ui/libgli/include/gli_progress.h w3d/ui/libgli/include/gli_image.h \
  w3d/ui/libgli/include/gli_frame.h w3d/ui/libgli/include/gli_window.h \
  w3d/ui/libgli/include/gli_interface.h \
  w3d/ui/libgli/include/gli_texture.h w3d/opengl.h w3d/global.h \
  w3d/bios/bios.h w3d/definiciones.h
	g++ $(CXXFLAGS) -c ./w3d/ui/w3d_ui.cpp -o ./w3d/ui/w3d_ui.cpp
gli_model.o: w3d/ui/libgli/gli_model.cpp \
  w3d/ui/libgli/include/gli_model.h w3d/ui/libgli/include/gli_object.h \
  w3d/ui/libgli/include/gli_types.h w3d/ui/libgli/include/gli_glf.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_model.cpp -o ./w3d/ui/libgli/gli_model.cpp
gli_texture_rgb.o: w3d/ui/libgli/gli_texture_rgb.cpp \
  w3d/ui/libgli/include/gli_texture_rgb.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_texture_rgb.cpp -o ./w3d/ui/libgli/gli_texture_rgb.cpp
gli_texture.o: w3d/ui/libgli/gli_texture.cpp \
  w3d/ui/libgli/include/gli_texture.h \
  w3d/ui/libgli/include/gli_texture_rgb.h \
  w3d/ui/libgli/include/gli_texture_tga.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_texture.cpp -o ./w3d/ui/libgli/gli_texture.cpp
gli_image.o: w3d/ui/libgli/gli_image.cpp \
  w3d/ui/libgli/include/gli_image.h w3d/ui/libgli/include/gli_object.h \
  w3d/ui/libgli/include/gli_types.h w3d/ui/libgli/include/gli_glf.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_image.cpp -o ./w3d/ui/libgli/gli_image.cpp
gli_window.o: w3d/ui/libgli/gli_window.cpp \
  w3d/ui/libgli/include/gli_window.h w3d/ui/libgli/include/gli_frame.h \
  w3d/ui/libgli/include/gli_object.h w3d/ui/libgli/include/gli_types.h \
  w3d/ui/libgli/include/gli_glf.h w3d/ui/libgli/include/gli_button.h \
  w3d/ui/libgli/include/gli_text.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_window.cpp -o ./w3d/ui/libgli/gli_window.cpp
gli_texture_tga.o: w3d/ui/libgli/gli_texture_tga.cpp \
  w3d/ui/libgli/include/gli_texture_tga.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_texture_tga.cpp -o ./w3d/ui/libgli/gli_texture_tga.cpp
gli_glf.o: w3d/ui/libgli/gli_glf.cpp w3d/ui/libgli/include/gli_glf.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_glf.cpp -o ./w3d/ui/libgli/gli_glf.cpp
gli_editbox.o: w3d/ui/libgli/gli_editbox.cpp \
  w3d/ui/libgli/include/gli_editbox.h w3d/ui/libgli/include/gli_object.h \
  w3d/ui/libgli/include/gli_types.h w3d/ui/libgli/include/gli_glf.h \
  w3d/ui/libgli/include/gli_text.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_editbox.cpp -o ./w3d/ui/libgli/gli_editbox.cpp
gli_interface.o: w3d/ui/libgli/gli_interface.cpp \
  w3d/ui/libgli/include/gli_object.h w3d/ui/libgli/include/gli_types.h \
  w3d/ui/libgli/include/gli_glf.h w3d/ui/libgli/include/gli_interface.h \
  w3d/ui/libgli/include/gli_texture.h \
  w3d/ui/libgli/include/gli_standard_font.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_interface.cpp -o ./w3d/ui/libgli/gli_interface.cpp
gli_frame.o: w3d/ui/libgli/gli_frame.cpp \
  w3d/ui/libgli/include/gli_frame.h w3d/ui/libgli/include/gli_object.h \
  w3d/ui/libgli/include/gli_types.h w3d/ui/libgli/include/gli_glf.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_frame.cpp -o ./w3d/ui/libgli/gli_frame.cpp
gli_text.o: w3d/ui/libgli/gli_text.cpp w3d/ui/libgli/include/gli_text.h \
  w3d/ui/libgli/include/gli_object.h w3d/ui/libgli/include/gli_types.h \
  w3d/ui/libgli/include/gli_glf.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_text.cpp -o ./w3d/ui/libgli/gli_text.cpp
gli_object.o: w3d/ui/libgli/gli_object.cpp \
  w3d/ui/libgli/include/gli_object.h w3d/ui/libgli/include/gli_types.h \
  w3d/ui/libgli/include/gli_glf.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_object.cpp -o ./w3d/ui/libgli/gli_object.cpp
gli_progress.o: w3d/ui/libgli/gli_progress.cpp \
  w3d/ui/libgli/include/gli_progress.h w3d/ui/libgli/include/gli_object.h \
  w3d/ui/libgli/include/gli_types.h w3d/ui/libgli/include/gli_glf.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_progress.cpp -o ./w3d/ui/libgli/gli_progress.cpp
gli_button.o: w3d/ui/libgli/gli_button.cpp \
  w3d/ui/libgli/include/gli_button.h w3d/ui/libgli/include/gli_object.h \
  w3d/ui/libgli/include/gli_types.h w3d/ui/libgli/include/gli_glf.h \
  w3d/ui/libgli/include/gli_text.h
	g++ $(CXXFLAGS) -c ./w3d/ui/libgli/gli_button.cpp -o ./w3d/ui/libgli/gli_button.cpp

w3d_x86.exe :./w3d/gfx/fuentes.o ./w3d/gfx/gfx_carga_img.o ./w3d/bios/bios.o ./w3d/display/display.o ./w3d/display/init_gl.o ./w3d/display/logo.o ./w3d/input/teclado.o ./w3d/engine/espacio.o ./w3d/engine/mad.o ./w3d/engine/texturas.o ./w3d/engine/engine.o ./w3d/main.o ./w3d/ui/w3d_ui.o ./w3d/ui/libgli/gli_model.o ./w3d/ui/libgli/gli_texture_rgb.o ./w3d/ui/libgli/gli_texture.o ./w3d/ui/libgli/gli_image.o ./w3d/ui/libgli/gli_window.o ./w3d/ui/libgli/gli_texture_tga.o ./w3d/ui/libgli/gli_glf.o ./w3d/ui/libgli/gli_editbox.o ./w3d/ui/libgli/gli_interface.o ./w3d/ui/libgli/gli_frame.o ./w3d/ui/libgli/gli_text.o ./w3d/ui/libgli/gli_object.o ./w3d/ui/libgli/gli_progress.o ./w3d/ui/libgli/gli_button.o 
	g++ -I./w3d/ui/libgli/include -o w3d_x86.exe $(LIBS) $(LDFLAGS)  ./w3d/gfx/fuentes.o ./w3d/gfx/gfx_carga_img.o ./w3d/bios/bios.o ./w3d/display/display.o ./w3d/display/init_gl.o ./w3d/display/logo.o ./w3d/input/teclado.o ./w3d/engine/espacio.o ./w3d/engine/mad.o ./w3d/engine/texturas.o ./w3d/engine/engine.o ./w3d/main.o ./w3d/ui/w3d_ui.o ./w3d/ui/libgli/gli_model.o ./w3d/ui/libgli/gli_texture_rgb.o ./w3d/ui/libgli/gli_texture.o ./w3d/ui/libgli/gli_image.o ./w3d/ui/libgli/gli_window.o ./w3d/ui/libgli/gli_texture_tga.o ./w3d/ui/libgli/gli_glf.o ./w3d/ui/libgli/gli_editbox.o ./w3d/ui/libgli/gli_interface.o ./w3d/ui/libgli/gli_frame.o ./w3d/ui/libgli/gli_text.o ./w3d/ui/libgli/gli_object.o ./w3d/ui/libgli/gli_progress.o ./w3d/ui/libgli/gli_button.o 
clean:
	find -name '*.o'|xargs rm -f ;rm  w3d_x86.exe
