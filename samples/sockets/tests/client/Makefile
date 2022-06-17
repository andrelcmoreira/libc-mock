CC = gcc
LDFLAGS = -Wl,--rpath=$(PWD)/src -L$(PWD)/src -lc-mock
SRC = client_test.c $(PWD)/samples/sockets/app/client.c
INCLUDE = -I$(PWD)/samples/sockets/app/ -I$(PWD)/src
OUTPUT = client_test

all:
	$(CC) $(LDFLAGS) $(INCLUDE) -o $(OUTPUT) $(SRC)

clean:
	-rm $(OUTPUT)
