CC=gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs glib-2.0`


program: 
	$(CC) $(CFLAGS) $(LIBS) -O2 -c ./user.c ./hashuser.c ./user.c ./post.c ./common.c ./date.c ./pair.c
	$(CC) $(CFLAGS) $(LIBS) -O2 -o Prog ./*.o 

clean:
	rm ./*.o
	rm ./Prog