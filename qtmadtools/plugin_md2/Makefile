all:
	gcc -shared -Wl,-soname,md2.so -o md2.so md2.c -DLINUX
	cp md2.so ../bin/plugins
clean:
	rm *.so

