
CC = gcc
CFLAGS = -g -Wall

server.out: func.o server.o
	$(CC) $(CFLAGS) -o ../bin/server.out ../bin/func.o ../bin/server.o

func.o: func.c func.h
	$(CC) $(CFLAGS) -c func.c

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

clean:
	rm ../bin/func.o ../bin/server.o ../bin/server.out