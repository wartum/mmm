CC=g++
CFLAGS=-g -Wall -Werror -std=c++11
LFLAGS=-ltag -lgtest
SOURCES=main.cpp \
	params_test.cpp ../src/params.cpp \
	tags_test.cpp ../src/tags.cpp
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLE=../run_ut
SAMPLE_MP3=mine_sample.mp3

.PHONY: all
.PHONY: clean
.PHONY: run

all: $(SAMPLE_MP3) $(EXECUTABLE)
	$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

$(SAMPLE_MP3):
	ffmpeg -f alsa -i hw:0,0 -t 1 $(SAMPLE_MP3)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

