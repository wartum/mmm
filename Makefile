.PHONY: all
.PHONY: compile
.PHONY: test
.PHONY: clean

all: compile test

compile:
	make all -C src

test:
	make all -C tests

clean:
	make $@ -C src
	make $@ -C tests
