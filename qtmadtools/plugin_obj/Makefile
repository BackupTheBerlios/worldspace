all:
	gcc -shared -Wl,-soname,obj.so -o obj.so obj.c -DLINUX
	cp obj.so ../bin/plugins
clean:
	rm *.so

