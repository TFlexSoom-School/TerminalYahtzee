# Tristan Hilberrt
# 3/9/18
# Making a makefile for this amazing game
#

CC = g++
FLAGS = -lncurses
EXECUTABLE = bin/yahtzee
SOURCE_FILES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCE_FILES:%.cpp=%.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)

.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@
