CC = gcc
CFLAGS = -std=c11 -Wall -g

EXECS = helloWorld

all: $(EXECS)

helloWorld: helloWorld.c
	$(CC) $(CFLAGS) helloWorld.c -o helloWorld

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) helloWorld.o