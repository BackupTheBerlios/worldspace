VERSION=`date +%Y%m%d`
INCLUDE =   -I/usr/X11R6/include -I/usr/local/include -I/usr/local/include/paragui -I/usr/include/freetype2 -I/usr/include/SDL -I/usr/include/
LIBDIR  =  -L/usr/X11R6/lib -L/usr/lib -L/usr/local/lib `/usr/local/bin/paragui-config --libs`
COMPILERFLAGS =   -D_LINUX -DFECHA="$(VERSION)"
#COMPILERFLAGS =  -O3  -Wall -D_LINUX -fexpensive-optimizations -fPIC -DFECHA=$(VERSION)
CC = gcc

CFLAGS = $(COMPILERFLAGS) $(INCLUDE)  -D_REENTRANT
LIBRARIES = -lX11 -lXi -lXmu  -lGL -lGLU -lm -lpthread -lSDL -lXxf86dga -lXv -lXxf86vm -lparagui

FUENTES=  madivs.cpp    pgglwidget.cpp

CABECERAS= pgglwidget.h paragl.h

all:madivs
	
	
madivs:$(FUENTES) $(CABECERAS)
	$(CC) -c $(FUENTES) $(CFLAGS)
	$(CC) *.o -o ../madivs.exe $(LIBDIR) $(LIBRARIES)
clean:	
	rm -f *.o
	rm -f ../*.exe
