# Tristan Hilberrt
# 3/9/18
# Making a makefile for this amazing game
#

CC = g++
FLAGS = -lncurses
EXECUTABLE = bin/yahtzee
D_EXECUTABLE = bin/debugYahtzee
SOURCE_FILES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCE_FILES:%.cpp=%.o)

all: $(EXECUTABLE)

$(EXECUTABLE): bin $(OBJECTS)
	
	$(CC) $(FLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
	rm -rf bin


.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@

bin:
	mkdir bin

debug: bin
	$(CC) $(FLAGS) -g $(SOURCE_FILES) -o $(D_EXECUTABLE)
