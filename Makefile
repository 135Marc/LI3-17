CC=gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`


program: post.o user.o hashuser.o hashuser.h
	$(CC) $(CFLAGS) hashuser.c post.o user.o -o program $(LIBS)

hashuser.o: hashtable.c hashtable.h
	$(CC) $(CFLAGS) -c hashtable.c -o hashtable.o $(LIBS)

post.o: post.c post.h
	$(CC) $(CFLAGS) -c post.c -o post.o $(LIBS)

user.o: user.c user.h
	$(CC) $(CFLAGS) -c user.c -o user.o $(LIBS)

date.o: date.c date.h
	$(CC) $(CFLAGS) -c date.c -o date.o $(LIBS) 