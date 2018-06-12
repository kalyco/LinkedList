CC=g++
CFLAGS=-std=c++0x -g
SRCS=main.cpp TaskList.cpp
EXEC=TaskList

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

clean: 
	rm TaskList *~ 
