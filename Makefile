CC=gcc
CFLAGS = -Wall -std=c11 -g -O2 `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`


program: 
	$(CC) $(CFLAGS) $(LIBS) -O2 -o Prog ./*.c

clean:
	rm ./Prog