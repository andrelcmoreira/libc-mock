.PHONY: lib

all: lib tests

tests:
	make -C samples/file/tests/ all
	make -C samples/sockets/tests/client all

lib:
	make -C src/ all

clean:
	make -C src/ clean
	make -C samples/file/tests/ clean
	make -C samples/sockets/tests/client clean
