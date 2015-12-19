CC=g++
CFLAGS=-Wall -std=c++11
LIBS=-lncurses
DEPS= rmonclient.h rsocket.h
OBJ = gpibmon.o rmonclient.o rsocket.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gpibmon : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean :
	rm *.o gpibmon
