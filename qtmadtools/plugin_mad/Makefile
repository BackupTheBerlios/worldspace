all:
	gcc -shared -Wl,-soname,mad.so -o mad.so mad.c -DLINUX
	cp mad.so ../bin/plugins
clean:
	rm *.so

