CC = gcc
CFLAGS = -fPIC -shared -ldl
SRC = libc_mock.c
OUTPUT = libc-mock.so

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

clean:
	-rm $(OUTPUT)
