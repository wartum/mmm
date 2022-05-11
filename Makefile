.PHONY: all
.PHONY: compile
.PHONY: test
.PHONY: clean
.PHONY: install
.PHONY: uninstall

all: compile test

compile:
	make all -C src

test:
	make all -C tests

clean:
	make $@ -C src
	make $@ -C tests

install:
	make install -C src

uninstall:
	make uninstall -C src
