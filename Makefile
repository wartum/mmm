EXECUTABLE=mmm

all: $(EXECUTABLE) test

$(EXECUTABLE):
	make -C src

test:
	make -C tests

clean:
	make $@ -C src
	make $@ -C tests
