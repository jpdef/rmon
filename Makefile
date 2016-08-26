CC        = g++
CFLAGS    = -Wall -std=c++0x 
LIBS      = -lncurses
SRCDIR1   = src/rmon
SRCDIR2   = src/nwin
OBJDIR    = build/
VPATH     = $(SRCDIR1):$(SRCDIR2)
SRCS      = $(shell find -name "*.cpp" -printf "%f\n") 
OBJS      = $(addprefix build/,$(patsubst %.cpp, %.o,$(SRCS)))
BIN       = rmon

print-% :
	@echo '$*=$($*)'

$(BIN) : $(OBJS)
	@echo $SRCS
	$(CC) -o $@ $^ $(LIBS)

$(OBJDIR)%.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean :
	rm build/*.o
	rm $(BIN)
