VERSION=`date +%Y%m%d`
INCLUDE = -I/usr/include/   -I/usr/X11R6/include -I/usr/include/SDL
LIBDIR  =  -L/usr/X11R6/lib -L/usr/lib
COMPILERFLAGS =  -g -ggdb   -Wall -D_LINUX   -DFECHA=$(VERSION)
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu  -lGL -lGLU -lm -lpthread -lSDL -lXxf86dga -lXv -lXxf86vm

FUENTES= mad.c fuentes.c timer_linux.c timer_win32.c carga_tga.c render.c sys_linux.c sys_win32.c init_sys.c teclado.c

CABECERAS= mad.h fuentes.h timer.h estructuras.h render.h sys.h init_sys.h carga_tga.h timer.h teclado.h

all:madview
	
	
madview:$(FUENTES) $(CABECERAS)
	echo "Compilando Madview 3d en Linux!!"
	$(CC) -c $(FUENTES) $(CFLAGS)
	$(CC) *.o -o ../madview.exe $(LIBDIR) $(LIBRARIES)

