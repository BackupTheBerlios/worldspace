all:
	g++ -shared -Wl,-soname,3ds.so -o 3ds.so 3ds.c l3ds.cpp -DLINUX
	cp 3ds.so ../bin/plugins
clean:
	rm *.so

