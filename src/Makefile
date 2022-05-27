CC=g++
CFLAGS=-g -Wall -Werror -std=c++11 -Winvalid-pch
LFLAGS=-ltag
SOURCES=main.cpp params.cpp tags.cpp groups.cpp
PRECOMPILED_HEADER=pch.h.gch
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLE=../mmm

.PHONY: all
.PHONY: clean
.PHONY: install
.PHONY: uninstall

all: $(PRECOMPILED_HEADER) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(PRECOMPILED_HEADER)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(PRECOMPILED_HEADER): pch.h
	$(CC) $(CFLAGS) $^

install: $(EXECUTABLE)
	cp $(EXECUTABLE) /usr/bin

uninstall:
	rm /usr/bin/mmm
