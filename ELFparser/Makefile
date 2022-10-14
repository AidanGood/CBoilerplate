CC = gcc
CFLAGS = -std=c11 -Wall -g

EXECS = main

all: $(EXECS)

helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c -o helper.o

main: helper.o main.c
	$(CC) $(CFLAGS) main.c helper.o -o main

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) main.o helper.o