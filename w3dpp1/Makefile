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


.PHONY: all clean distclean binaries static shared install install-binaries install-conf install-headers install-shared install-static install-man1 install-man2 install-man3 install-man4 install-man5 install-man6 install-man7 install-man8 install-man9

all: binaries static shared

install: install-binaries install-headers install-shared install-conf install-static install-man1 install-man2 install-man3 install-man4 install-man5 install-man6 install-man7 install-man8 install-man9

distclean: clean
	rm -f Makefile firemake.h install.sh

gli_model.o: w3d/ui/libgli/gli_model.cpp /usr/include/gli_model.h \
  /usr/include/gli_object.h /usr/include/GL/gl.h /usr/include/GL/glext.h \
  /usr/include/gli_types.h /usr/include/gli_glf.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_model.o -c ./w3d/ui/libgli/gli_model.cpp

gli_texture.o: w3d/ui/libgli/gli_texture.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/stdlib.h /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/xlocale.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h /usr/include/GL/gl.h /usr/include/GL/glext.h \
  /usr/include/GL/glu.h /usr/include/gli_texture.h \
  /usr/include/gli_texture_rgb.h /usr/include/gli_texture_tga.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_texture.o -c ./w3d/ui/libgli/gli_texture.cpp

gli_window.o: w3d/ui/libgli/gli_window.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/gli_window.h /usr/include/gli_frame.h \
  /usr/include/gli_object.h /usr/include/GL/gl.h /usr/include/GL/glext.h \
  /usr/include/gli_types.h /usr/include/gli_glf.h \
  /usr/include/gli_button.h /usr/include/gli_text.h \
  /usr/include/c++/3.2/string \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/c++config.h \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/os_defines.h \
  /usr/include/c++/3.2/bits/stringfwd.h \
  /usr/include/c++/3.2/bits/char_traits.h /usr/include/c++/3.2/cstring \
  /usr/include/c++/3.2/cstddef /usr/include/string.h \
  /usr/include/xlocale.h /usr/include/c++/3.2/bits/fpos.h \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/c++io.h \
  /usr/include/c++/3.2/cstdio \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/gthr.h \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/gthr-default.h \
  /usr/include/pthread.h /usr/include/sched.h /usr/include/time.h \
  /usr/include/bits/time.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/initspin.h \
  /usr/include/bits/sigthread.h /usr/include/c++/3.2/cwchar \
  /usr/include/c++/3.2/ctime /usr/include/c++/3.2/memory \
  /usr/include/c++/3.2/bits/stl_algobase.h /usr/include/c++/3.2/climits \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/limits.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/bits/xopen_lim.h \
  /usr/include/bits/wordsize.h /usr/include/c++/3.2/cstdlib \
  /usr/include/stdlib.h /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/c++/3.2/new /usr/include/c++/3.2/exception \
  /usr/include/c++/3.2/iosfwd /usr/include/c++/3.2/bits/functexcept.h \
  /usr/include/c++/3.2/exception_defines.h \
  /usr/include/c++/3.2/bits/stl_pair.h \
  /usr/include/c++/3.2/bits/type_traits.h \
  /usr/include/c++/3.2/bits/stl_iterator_base_types.h \
  /usr/include/c++/3.2/bits/stl_iterator_base_funcs.h \
  /usr/include/c++/3.2/bits/concept_check.h \
  /usr/include/c++/3.2/bits/stl_iterator.h \
  /usr/include/c++/3.2/bits/stl_alloc.h /usr/include/c++/3.2/cassert \
  /usr/include/assert.h /usr/include/c++/3.2/bits/stl_threads.h \
  /usr/include/c++/3.2/bits/stl_construct.h \
  /usr/include/c++/3.2/bits/stl_uninitialized.h \
  /usr/include/c++/3.2/bits/stl_raw_storage_iter.h \
  /usr/include/c++/3.2/bits/stl_function.h \
  /usr/include/c++/3.2/bits/basic_string.h \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/atomicity.h \
  /usr/include/c++/3.2/algorithm /usr/include/c++/3.2/bits/stl_algo.h \
  /usr/include/c++/3.2/bits/stl_heap.h \
  /usr/include/c++/3.2/bits/stl_tempbuf.h \
  /usr/include/c++/3.2/bits/basic_string.tcc
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_window.o -c ./w3d/ui/libgli/gli_window.cpp

gli_glf.o: w3d/ui/libgli/gli_glf.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/stdlib.h /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/xlocale.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h /usr/include/math.h /usr/include/bits/huge_val.h \
  /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
  /usr/include/bits/mathcalls.h /usr/include/bits/mathinline.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/GL/glu.h \
  /usr/include/gli_glf.h /usr/include/c++/3.2/string \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/c++config.h \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/os_defines.h \
  /usr/include/c++/3.2/bits/stringfwd.h \
  /usr/include/c++/3.2/bits/char_traits.h /usr/include/c++/3.2/cstring \
  /usr/include/c++/3.2/cstddef /usr/include/string.h \
  /usr/include/c++/3.2/bits/fpos.h \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/c++io.h \
  /usr/include/c++/3.2/cstdio \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/gthr.h \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/gthr-default.h \
  /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
  /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
  /usr/include/c++/3.2/cwchar /usr/include/c++/3.2/ctime \
  /usr/include/c++/3.2/memory /usr/include/c++/3.2/bits/stl_algobase.h \
  /usr/include/c++/3.2/climits \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/limits.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/bits/xopen_lim.h \
  /usr/include/bits/wordsize.h /usr/include/c++/3.2/cstdlib \
  /usr/include/c++/3.2/new /usr/include/c++/3.2/exception \
  /usr/include/c++/3.2/iosfwd /usr/include/c++/3.2/bits/functexcept.h \
  /usr/include/c++/3.2/exception_defines.h \
  /usr/include/c++/3.2/bits/stl_pair.h \
  /usr/include/c++/3.2/bits/type_traits.h \
  /usr/include/c++/3.2/bits/stl_iterator_base_types.h \
  /usr/include/c++/3.2/bits/stl_iterator_base_funcs.h \
  /usr/include/c++/3.2/bits/concept_check.h \
  /usr/include/c++/3.2/bits/stl_iterator.h \
  /usr/include/c++/3.2/bits/stl_alloc.h /usr/include/c++/3.2/cassert \
  /usr/include/assert.h /usr/include/c++/3.2/bits/stl_threads.h \
  /usr/include/c++/3.2/bits/stl_construct.h \
  /usr/include/c++/3.2/bits/stl_uninitialized.h \
  /usr/include/c++/3.2/bits/stl_raw_storage_iter.h \
  /usr/include/c++/3.2/bits/stl_function.h \
  /usr/include/c++/3.2/bits/basic_string.h \
  /usr/include/c++/3.2/i586-mandrake-linux-gnu/bits/atomicity.h \
  /usr/include/c++/3.2/algorithm /usr/include/c++/3.2/bits/stl_algo.h \
  /usr/include/c++/3.2/bits/stl_heap.h \
  /usr/include/c++/3.2/bits/stl_tempbuf.h \
  /usr/include/c++/3.2/bits/basic_string.tcc
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_glf.o -c ./w3d/ui/libgli/gli_glf.cpp

gli_image.o: w3d/ui/libgli/gli_image.cpp /usr/include/gli_image.h \
  /usr/include/gli_object.h /usr/include/GL/gl.h /usr/include/GL/glext.h \
  /usr/include/gli_types.h /usr/include/gli_glf.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_image.o -c ./w3d/ui/libgli/gli_image.cpp

gli_object.o: w3d/ui/libgli/gli_object.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/string.h /usr/include/xlocale.h /usr/include/gli_object.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/gli_types.h \
  /usr/include/gli_glf.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_object.o -c ./w3d/ui/libgli/gli_object.cpp

gli_frame.o: w3d/ui/libgli/gli_frame.cpp /usr/include/GL/gl.h \
  /usr/include/GL/glext.h /usr/include/gli_frame.h \
  /usr/include/gli_object.h /usr/include/gli_types.h \
  /usr/include/gli_glf.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_frame.o -c ./w3d/ui/libgli/gli_frame.cpp

gli_texture_rgb.o: w3d/ui/libgli/gli_texture_rgb.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/stdlib.h /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/xlocale.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h /usr/include/string.h \
  /usr/include/gli_texture_rgb.h /usr/include/GL/gl.h \
  /usr/include/GL/glext.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_texture_rgb.o -c ./w3d/ui/libgli/gli_texture_rgb.cpp

gli_progress.o: w3d/ui/libgli/gli_progress.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/gli_progress.h /usr/include/gli_object.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/gli_types.h \
  /usr/include/gli_glf.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_progress.o -c ./w3d/ui/libgli/gli_progress.cpp

gli_button.o: w3d/ui/libgli/gli_button.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/string.h /usr/include/xlocale.h /usr/include/GL/gl.h \
  /usr/include/GL/glext.h /usr/include/gli_button.h \
  /usr/include/gli_object.h /usr/include/gli_types.h \
  /usr/include/gli_glf.h /usr/include/gli_text.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_button.o -c ./w3d/ui/libgli/gli_button.cpp

gli_text.o: w3d/ui/libgli/gli_text.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/string.h /usr/include/xlocale.h /usr/include/math.h \
  /usr/include/bits/huge_val.h /usr/include/bits/nan.h \
  /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
  /usr/include/bits/mathinline.h /usr/include/gli_text.h \
  /usr/include/gli_object.h /usr/include/GL/gl.h /usr/include/GL/glext.h \
  /usr/include/gli_types.h /usr/include/gli_glf.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_text.o -c ./w3d/ui/libgli/gli_text.cpp

gli_texture_tga.o: w3d/ui/libgli/gli_texture_tga.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/stdlib.h /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/xlocale.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h /usr/include/gli_texture_tga.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_texture_tga.o -c ./w3d/ui/libgli/gli_texture_tga.cpp

gli_interface.o: w3d/ui/libgli/gli_interface.cpp \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/GL/glu.h \
  /usr/include/gli_object.h /usr/include/gli_types.h \
  /usr/include/gli_glf.h /usr/include/gli_interface.h \
  /usr/include/gli_texture.h /usr/include/gli_standard_font.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_interface.o -c ./w3d/ui/libgli/gli_interface.cpp

gli_editbox.o: w3d/ui/libgli/gli_editbox.cpp /usr/include/gli_editbox.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/stdlib.h /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/xlocale.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h /usr/include/gli_object.h /usr/include/GL/gl.h \
  /usr/include/GL/glext.h /usr/include/gli_types.h /usr/include/gli_glf.h \
  /usr/include/gli_text.h /usr/include/string.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/libgli/gli_editbox.o -c ./w3d/ui/libgli/gli_editbox.cpp

w3d_ui.o: w3d/ui/w3d_ui.cpp w3d/ui/libgli/include/gli.h \
  w3d/ui/libgli/include/gli_types.h w3d/ui/libgli/include/gli_object.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h \
  w3d/ui/libgli/include/gli_glf.h w3d/ui/libgli/include/gli_button.h \
  w3d/ui/libgli/include/gli_text.h w3d/ui/libgli/include/gli_editbox.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/stdlib.h /usr/include/bits/waitflags.h \
  /usr/include/bits/waitstatus.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/xlocale.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h w3d/ui/libgli/include/gli_progress.h \
  w3d/ui/libgli/include/gli_image.h w3d/ui/libgli/include/gli_frame.h \
  w3d/ui/libgli/include/gli_window.h \
  w3d/ui/libgli/include/gli_interface.h \
  w3d/ui/libgli/include/gli_texture.h w3d/opengl.h /usr/include/GL/glu.h \
  /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h \
  /usr/include/SDL/SDL_types.h /usr/include/SDL/SDL_getenv.h \
  /usr/include/SDL/SDL_error.h /usr/include/SDL/begin_code.h \
  /usr/include/SDL/close_code.h /usr/include/SDL/SDL_rwops.h \
  /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_audio.h \
  /usr/include/SDL/SDL_byteorder.h /usr/include/SDL/SDL_cdrom.h \
  /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_events.h \
  /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
  /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
  /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_mutex.h \
  /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_version.h w3d/global.h \
  w3d/bios/bios.h w3d/definiciones.h
	$(CCPP) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/ui/w3d_ui.o -c ./w3d/ui/w3d_ui.cpp

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

mad.o: w3d/engine/mad.c \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/libio.h /usr/include/_G_config.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
  /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
  /usr/include/endian.h /usr/include/bits/endian.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h /usr/include/bits/time.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/string.h /usr/include/bits/string.h \
  /usr/include/bits/string2.h w3d/engine/mad.h w3d/engine/estructuras.h \
  w3d/global.h w3d/bios/bios.h w3d/definiciones.h w3d/opengl.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/GL/glu.h \
  /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h \
  /usr/include/SDL/SDL_types.h /usr/include/SDL/SDL_getenv.h \
  /usr/include/SDL/SDL_error.h /usr/include/SDL/begin_code.h \
  /usr/include/SDL/close_code.h /usr/include/SDL/SDL_rwops.h \
  /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_audio.h \
  /usr/include/SDL/SDL_byteorder.h /usr/include/SDL/SDL_cdrom.h \
  /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_events.h \
  /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
  /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
  /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_mutex.h \
  /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_version.h
 $(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/engine/mad.o -c ./w3d/engine/mad.c

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
  w3d/bios/bios.h w3d/definiciones.h w3d/engine/mad.h \
  w3d/engine/estructuras.h w3d/display/logo.h
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
  w3d/definiciones.h w3d/display/display.h w3d/gfx/fuentes.h w3d/opengl.h \
  /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/GL/glu.h \
  /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h \
  /usr/include/SDL/SDL_types.h /usr/include/SDL/SDL_getenv.h \
  /usr/include/SDL/SDL_error.h /usr/include/SDL/begin_code.h \
  /usr/include/SDL/close_code.h /usr/include/SDL/SDL_rwops.h \
  /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_audio.h \
  /usr/include/SDL/SDL_byteorder.h /usr/include/SDL/SDL_cdrom.h \
  /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_events.h \
  /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
  /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
  /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_mutex.h \
  /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_version.h \
  w3d/ui/w3d_ui.h
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

fuentes.o: w3d/gfx/fuentes.c w3d/opengl.h /usr/include/GL/gl.h \
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
  w3d/bios/bios.h w3d/definiciones.h w3d/gfx/gfx_carga_img.h \
  w3d/gfx/fuentes.h /usr/include/string.h /usr/include/bits/string.h \
  /usr/include/bits/string2.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h
 $(CC) $(CFLAGS) -DCONFDIR=\"$(CONFDIR)\" -DBINDIR=\"$(BINDIR)\" -o ./w3d/gfx/fuentes.o -c ./w3d/gfx/fuentes.c

w3d_x86.exe: ./w3d/bios/bios.o ./w3d/engine/mad.o ./w3d/display/init_gl.o ./w3d/display/display.o ./w3d/display/logo.o ./w3d/main.o ./w3d/gfx/gfx_carga_img.o ./w3d/gfx/fuentes.o ./w3d/ui/libgli/gli_model.o ./w3d/ui/libgli/gli_texture.o ./w3d/ui/libgli/gli_window.o ./w3d/ui/libgli/gli_glf.o ./w3d/ui/libgli/gli_image.o ./w3d/ui/libgli/gli_object.o ./w3d/ui/libgli/gli_frame.o ./w3d/ui/libgli/gli_texture_rgb.o ./w3d/ui/libgli/gli_progress.o ./w3d/ui/libgli/gli_button.o ./w3d/ui/libgli/gli_text.o ./w3d/ui/libgli/gli_texture_tga.o ./w3d/ui/libgli/gli_interface.o ./w3d/ui/libgli/gli_editbox.o ./w3d/ui/w3d_ui.o
	$(CCPP) $(LDFLAGS) -o w3d_x86.exe ./w3d/bios/bios.o ./w3d/engine/mad.o ./w3d/display/init_gl.o ./w3d/display/display.o ./w3d/display/logo.o ./w3d/main.o ./w3d/gfx/gfx_carga_img.o ./w3d/gfx/fuentes.o ./w3d/ui/libgli/gli_model.o ./w3d/ui/libgli/gli_texture.o ./w3d/ui/libgli/gli_window.o ./w3d/ui/libgli/gli_glf.o ./w3d/ui/libgli/gli_image.o ./w3d/ui/libgli/gli_object.o ./w3d/ui/libgli/gli_frame.o ./w3d/ui/libgli/gli_texture_rgb.o ./w3d/ui/libgli/gli_progress.o ./w3d/ui/libgli/gli_button.o ./w3d/ui/libgli/gli_text.o ./w3d/ui/libgli/gli_texture_tga.o ./w3d/ui/libgli/gli_interface.o ./w3d/ui/libgli/gli_editbox.o ./w3d/ui/w3d_ui.o $(LIBS)

binaries:  w3d_x86.exe

shared: 

static: 

clean:
	find -name '*.o'|xargs rm -f ;rm  w3d_x86.exe
install-binaries:  w3d_x86.exe
	./install.sh w3d_x86.exe $(BINDIR) $(INSTALL_USER) $(INSTALL_GROUP) 0755

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

