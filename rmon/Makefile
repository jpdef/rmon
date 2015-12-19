CC=g++
CFLAGS=-c -Wall -std=c++11
LIBS=
all : rmonclient

rmonclient : rmonclient.o rsocket.o
	$(CC) rmonclient.o rsocket.o -o  rmonclient $(LIBS)

rmonclient.o : rmonclient.c
	$(CC) $(CFLAGS) rmonclient.c 

rsocket.o : rsocket.c
	$(CC) $(CFLAGS) rsocket.c 

clean:
	rm *o rsocket rmonclient
