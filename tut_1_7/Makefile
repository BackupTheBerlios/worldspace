INCLUDE = -I/usr/include/   -I/usr/X11R6/include -I/usr/include/SDL
LIBDIR  =  -L/usr/X11R6/lib -L/usr/lib
COMPILERFLAGS =  -g -ggdb    -Wall -D_LINUX
#COMPILERFLAGS =  -O3  -Wall -D_LINUX -fexpensive-optimizations -fPIC -DFECHA=$(VERSION)
CC = gcc

CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu  -lGL -lGLU -lm -lpthread -lSDL -lXxf86dga -lXv -lXxf86vm

FUENTES= ini_sys.c main.c

CABECERAS= estructuras.h opengl.h sys_data.h w3d_api.h

OBJS= ini_sys.o main.o

all:tut_1_7
	
	
tut_1_7:$(OBJS)
	$(CC) $(OBJS) -o ../tut_1_7.exe $(LIBDIR) $(LIBRARIES)

ini_sys.o:ini_sys.c estructuras.h w3d_api.h sys_data.h
	$(CC) -c ini_sys.c $(CFLAGS)

main.o:main.c estructuras.h w3d_api.h sys_data.h
	$(CC) -c main.c $(CFLAGS)

clean:	
	rm -f *.o
	rm -f ../*.exe

