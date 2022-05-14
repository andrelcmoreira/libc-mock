CC = gcc
CFLAGS = -fPIC -shared -ldl
SRC = preload.c
OUTPUT = libpreload.so

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

clean:
	-rm $(OUTPUT)
