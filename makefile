
readfile: readfile.c readfile.h
	$(CC) -o $(@) readfile.c $(CFLAGS)