CC = gcc
LDFLAGS = -Wl,--rpath=$(PWD)/src -L$(PWD)/src -lc-mock
SRC = test.c $(PWD)/samples/file/app/app.c
INCLUDE = -I$(PWD)/samples/file/app -I$(PWD)/src
OUTPUT = test

all:
	$(CC) $(LDFLAGS) $(INCLUDE) -o $(OUTPUT) $(SRC)

clean:
	-rm $(OUTPUT)
