#!/bin/bash
# Configurando y creando Makefile

CC=gcc
CCPP=g++
INCLUDE=./w3d/ui/libgli/include
BINARY=w3d_x86.exe


C_SOURCES=`find -name *.c`
echo "Fuentes en C : " $C_SOURCES

CPP_SOURCES=`find -name *.cpp`
echo "Fuentes en C++: " $CPP_SOURCES

echo "#">Makefile.kk
cat Makefile.conf >>Makefile.kk
echo CXXFLAGS := "\$(CXXFLAGS)" "\$(CFLAGS)" -I./w3d/ui/libgli/include>>Makefile.kk
echo "ALL: "$BINARY>>Makefile.kk

for i in $C_SOURCES
do

        echo "Calculando dependencias para $i"
        $CC -I$INCLUDE -MM $i -I$INCLUDE 2>aguconf.log >>Makefile.kk
        echo -n -e "\t">>Makefile.kk
        echo $CC "\$(CFLAGS)" -c $i -o `echo $i|sed s/.c$/.o/`>>Makefile.kk

done

for i in $CPP_SOURCES
do
        echo "Calculando dependencias para $i"
        $CCPP -MM $i -I$INCLUDE 2>aguconf.log >>Makefile.kk
        echo -n -e "\t">>Makefile.kk
        echo $CCPP "\$(CXXFLAGS)"  -c $i -o `echo $i|sed s/.c$/.o/`>>Makefile.kk
done
echo >>Makefile.kk
echo -n $BINARY \:>>Makefile.kk
for i in $C_SOURCES 
do
	echo -n $i  |sed s/.c$/.o/ >>Makefile.kk
	echo -n " ">>Makefile.kk
done
for i in $CPP_SOURCES
do
        echo -n $i  |sed s/.cpp$/.o/ >>Makefile.kk
        echo -n " ">>Makefile.kk
done
echo>>Makefile.kk
echo -n -e "\t">>Makefile.kk
echo -n $CCPP -I$INCLUDE -o $BINARY "\$(LIBS)" "\$(LDFLAGS)" " " >>Makefile.kk
for i in $C_SOURCES
do
        echo -n $i  |sed s/.c$/.o/ >>Makefile.kk
	        echo -n " ">>Makefile.kk
		done
		for i in $CPP_SOURCES
		do
		        echo -n $i  |sed s/.cpp$/.o/ >>Makefile.kk
			        echo -n " ">>Makefile.kk
				done
echo "">>Makefile.kk
echo "clean:">>Makefile.kk
echo -n -e "\t">>Makefile.kk
echo "find -name '*.o'|xargs rm -f ;rm  $BINARY">>Makefile.kk
cp Makefile.kk Makefile
