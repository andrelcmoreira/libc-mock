.PHONY: lib

all: lib tests

tests:
	make -C samples/file/tests/ all

lib:
	make -C src/ all

clean:
	make -C src/ clean
	make -C samples/file/tests/ clean
