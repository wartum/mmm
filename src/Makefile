CC=g++
CFLAGS=-g -Wall -Werror -std=c++11
LFLAGS=-ltag
SOURCES=main.cpp params.cpp tags.cpp
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLE=../mmm

.PHONY: all
.PHONY: clean
.PHONY: install
.PHONY: uninstall

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

install: $(EXECUTABLE)
	cp $(EXECUTABLE) /usr/bin

uninstall:
	rm /usr/bin/mmm
