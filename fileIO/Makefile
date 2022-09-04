CC = gcc
CFLAGS = -std=c11 -Wall -g

EXECS: main

all: $(EXECS)

main: fileio.o main.o
	$(CC) $(CFLAGS) main.o fileio.o -o main

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) fileio.o main.o