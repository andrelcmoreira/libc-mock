CC = gcc
LDFLAGS = -Wl,--rpath=$(PWD)/lib -L$(PWD)/lib -lpreload
SRC = test.c $(PWD)/app/app.c
INCLUDE = -I$(PWD)/app -I$(PWD)/lib
OUTPUT = test

all:
	$(CC) $(LDFLAGS) $(INCLUDE) -o $(OUTPUT) $(SRC)

clean:
	-rm $(OUTPUT)
