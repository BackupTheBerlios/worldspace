BUILD= `cat VERSION`
UPDATEV= $(BUILD)+1
CC := gcc
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
CFLAGS := $(CFLAGS) -g -ggdb    -Wall -D_LINUX -DBUILD=$(UPDATEV)
LDFLAGS := -L/usr/X11R6/lib -L/usr/lib $(LDFLAGS)


.PHONY: all clean distclean binaries static shared install install-binaries install-conf install-headers install-shared install-static install-man1 install-man2 install-man3 install-man4 install-man5 install-man6 install-man7 install-man8 install-man9

all: binaries static shared

install: install-binaries install-headers install-shared install-conf install-static install-man1 install-man2 install-man3 install-man4 install-man5 install-man6 install-man7 install-man8 install-man9

distclean: clean
	rm -f Makefile firemake.h install.sh

bios.o: w3d/bios/bios.c w3d/global.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h w3d/bios/bios.h \
  w3d/definiciones.h
	$(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/bios/bios.o -c ./w3d/bios/bios.c

init_gl.o: w3d/display/init_gl.c w3d/opengl.h /usr/include/GL/gl.h \
  /usr/include/GL/glext.h /usr/include/GL/glu.h /usr/include/SDL/SDL.h \
  /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_types.h \
  /usr/include/SDL/SDL_getenv.h /usr/include/SDL/SDL_error.h \
  /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h \
  /usr/include/SDL/SDL_rwops.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_audio.h \
  /usr/include/SDL/SDL_byteorder.h /usr/include/SDL/SDL_cdrom.h \
  /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_events.h \
  /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
  /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
  /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_mutex.h \
  /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_version.h w3d/global.h \
  w3d/bios/bios.h w3d/definiciones.h w3d/display/logo.h
	$(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/display/init_gl.o -c ./w3d/display/init_gl.c

display.o: w3d/display/display.c w3d/display/display.h \
  w3d/display/init_gl.h w3d/opengl.h /usr/include/GL/gl.h \
  /usr/include/GL/glext.h /usr/include/GL/glu.h /usr/include/SDL/SDL.h \
  /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_types.h \
  /usr/include/SDL/SDL_getenv.h /usr/include/SDL/SDL_error.h \
  /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h \
  /usr/include/SDL/SDL_rwops.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_audio.h \
  /usr/include/SDL/SDL_byteorder.h /usr/include/SDL/SDL_cdrom.h \
  /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_events.h \
  /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
  /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
  /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_mutex.h \
  /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_version.h w3d/global.h \
  w3d/bios/bios.h w3d/definiciones.h
	$(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/display/display.o -c ./w3d/display/display.c

logo.o: w3d/display/logo.c w3d/opengl.h /usr/include/GL/gl.h \
  /usr/include/GL/glext.h /usr/include/GL/glu.h /usr/include/SDL/SDL.h \
  /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_types.h \
  /usr/include/SDL/SDL_getenv.h /usr/include/SDL/SDL_error.h \
  /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h \
  /usr/include/SDL/SDL_rwops.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_audio.h \
  /usr/include/SDL/SDL_byteorder.h /usr/include/SDL/SDL_cdrom.h \
  /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_events.h \
  /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
  /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
  /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_mutex.h \
  /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_version.h
	$(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/display/logo.o -c ./w3d/display/logo.c

main.o: w3d/main.c w3d/global.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h w3d/bios/bios.h \
  w3d/definiciones.h w3d/display/display.h
	$(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/main.o -c ./w3d/main.c

gfx_carga_img.o: w3d/gfx/gfx_carga_img.c w3d/opengl.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/GL/glu.h \
  /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h \
  /usr/include/SDL/SDL_types.h /usr/include/SDL/SDL_getenv.h \
  /usr/include/SDL/SDL_error.h /usr/include/SDL/begin_code.h \
  /usr/include/SDL/close_code.h /usr/include/SDL/SDL_rwops.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_audio.h \
  /usr/include/SDL/SDL_byteorder.h /usr/include/SDL/SDL_cdrom.h \
  /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_events.h \
  /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
  /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
  /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_mutex.h \
  /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_version.h w3d/global.h \
  w3d/bios/bios.h w3d/definiciones.h /usr/include/string.h \
  /usr/include/bits/string.h /usr/include/bits/string2.h \
  /usr/include/endian.h /usr/include/bits/endian.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h
	$(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/gfx/gfx_carga_img.o -c ./w3d/gfx/gfx_carga_img.c

fuentes.o: w3d/gfx/fuentes.c
	$(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/gfx/fuentes.o -c ./w3d/gfx/fuentes.c

w3d.x86: ./w3d/bios/bios.o ./w3d/display/init_gl.o ./w3d/display/display.o ./w3d/display/logo.o ./w3d/main.o ./w3d/gfx/gfx_carga_img.o ./w3d/gfx/fuentes.o
	$(CC) $(LDFLAGS) -o w3d.x86 ./w3d/bios/bios.o ./w3d/display/init_gl.o ./w3d/display/display.o ./w3d/display/logo.o ./w3d/main.o ./w3d/gfx/gfx_carga_img.o ./w3d/gfx/fuentes.o $(LIBS)

binaries:  w3d.x86

shared: 

static: 

clean:
	find -name '*.o'|xargs rm -f ;rm  w3d.x86
install-binaries:  w3d.x86
	./install.sh w3d.x86 $(BINDIR) $(INSTALL_USER) $(INSTALL_GROUP) 0755

install-static: 

install-shared: 

install-headers: 

install-man1: 

install-man2: 

install-man3: 

install-man4: 

install-man5: 

install-man6: 

install-man7: 

install-man8: 

install-man9: 

install-conf: 

