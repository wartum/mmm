CC=g++
CFLAGS=-g -Wall -Werror -std=c++11
LFLAGS=-ltag -lgtest -lgmock
SOURCES=main.cpp \
	params_test.cpp ../src/params.cpp \
	tags_test.cpp ../src/tags.cpp
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLE=../run_ut

.PHONY: all
.PHONY: clean
.PHONY: run

all: $(EXECUTABLE)
	$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

