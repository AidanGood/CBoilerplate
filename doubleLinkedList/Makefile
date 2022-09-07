CC = gcc
CFLAGS = -std=c11 -Wall -g

EXECS = dlist_tb

all: $(EXECS)

node.o: node.c node.h 
	$(CC) $(CFLAGS) -c node.c -o node.o

dlist.o: dlist.h dlist.c node.h
	$(CC) $(CFLAGS) -c  dlist.c -o dlist.o
	
dlist_tb: dlist_tb.c node.o dlist.o
	$(CC) $(CFLAGS) dlist_tb.c node.o dlist.o -o dlist_tb

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) node.o dlist.o
