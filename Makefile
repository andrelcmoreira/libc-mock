.PHONY: lib

all: lib test

test:
	make -C tests/ all

lib:
	make -C lib/ all

clean:
	make -C lib/ clean
	make -C tests/ clean
