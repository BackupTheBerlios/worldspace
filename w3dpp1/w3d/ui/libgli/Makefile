CFLAGS = -pedantic -ansi -Wall -I./include
LFLAGS = -ldl -shared
C++ = g++

all: libgli.so

uninstall:
	rm -f $(prefix)/lib/libgli-$(VERSION).so
	rm -f $(prefix)/lib/libgli.so
	rm -f $(prefix)/include/gli*.h

install: libgli.so
	cp libgli.so $(prefix)/lib/libgli-$(VERSION).so
	ln -sf $(prefix)/lib/libgli-$(VERSION).so $(prefix)/lib/libgli.so
	cp include/gli*.h $(prefix)/include

gli_button.o: gli_button.cpp
	$(C++) $(CFLAGS) -c gli_button.cpp

gli_editbox.o: gli_editbox.cpp
	$(C++) $(CFLAGS) -c gli_editbox.cpp

gli_frame.o: gli_frame.cpp
	$(C++) $(CFLAGS) -c gli_frame.cpp

gli_glf.o: gli_glf.cpp
	$(C++) $(CFLAGS) -c gli_glf.cpp

gli_image.o: gli_image.cpp
	$(C++) $(CFLAGS) -c gli_image.cpp

gli_interface.o: gli_interface.cpp
	$(C++) $(CFLAGS) -c gli_interface.cpp

gli_object.o: gli_object.cpp
	$(C++) $(CFLAGS) -c gli_object.cpp

gli_progress.o: gli_progress.cpp
	$(C++) $(CFLAGS) -c gli_progress.cpp

gli_text.o: gli_text.cpp
	$(C++) $(CFLAGS) -c gli_text.cpp

gli_texture.o: gli_texture.cpp
	$(C++) $(CFLAGS) -c gli_texture.cpp

gli_window.o: gli_window.cpp
	$(C++) $(CFLAGS) -c gli_window.cpp

gli_texture_rgb.o: gli_texture_rgb.cpp
	$(C++) $(CFLAGS) -c gli_texture_rgb.cpp

gli_texture_tga.o: gli_texture_tga.cpp
	$(C++) $(CFLAGS) -c gli_texture_tga.cpp

libgli.so: gli_button.o gli_frame.o gli_glf.o gli_interface.o gli_object.o \
	gli_text.o gli_texture.o gli_window.o gli_texture_rgb.o \
	gli_texture_tga.o gli_editbox.o gli_image.o gli_progress.o
	$(C++) $(CFLAGS) gli*.o -o libgli.so $(LFLAGS)

clean:
	rm -f *.o
	rm -f libgli.so
