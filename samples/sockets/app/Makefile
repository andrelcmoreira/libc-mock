CC = gcc
FLAGS = -DMAIN

all: client server

client:
	$(CC) $(FLAGS) -o $@ $@.c

server:
	$(CC) $(FLAGS) -o $@ $@.c

clean:
	-rm client server
