VERSION=`date +%Y%m%d`
INCLUDE = -I/usr/include/
COMPILERFLAGS =  -g -ggdb    -Wall -D_LINUX  -DFECHA=$(VERSION)
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lm


all:md22mad
	
md22mad:md22mad.c estructuras.h
	$(CC) md22mad.c -o md22mad.exe $(CFLAGS) $(LIBRARIES)
	mv *.exe ..

