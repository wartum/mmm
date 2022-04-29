CC=g++
CFLAGS=-Wall -Werror -std=c++11
LFLAGS=-ltag
SOURCES=main.cpp params.cpp
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLE=mmm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

