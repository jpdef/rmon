CC=g++
CFLAGS=-Wall -std=c++11
LIBS=-lncurses
DEPS= rmonclient.h rsocket.h nwindow.c nwindow.h
OBJ = gpibmon.o rmonclient.o rsocket.o nwindow.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gpibmon : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean :
	rm *.o gpibmon
