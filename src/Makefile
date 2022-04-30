CC=g++
CFLAGS=-Wall -Werror -std=c++11
LFLAGS=-ltag
SOURCES=main.cpp params.cpp
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLE=../mmm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

