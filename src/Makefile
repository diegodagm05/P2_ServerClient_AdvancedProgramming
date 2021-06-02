
CC = gcc
CFLAGS = -g -Wall -fopenmp -lpthread

server.out: func.o server.o
	$(CC) $(CFLAGS) -o ../bin/server.out ../bin/func.o ../bin/server.o

func.o: func.c func.h
	$(CC) $(CFLAGS) -c func.c -o ../bin/func.o

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o ../bin/server.o

clean:
	rm ../bin/func.o ../bin/server.o ../bin/server.out