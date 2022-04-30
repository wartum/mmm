
all: compile test

compile:
	make -C src

test:
	make -C tests

clean:
	make $@ -C src
	make $@ -C tests
