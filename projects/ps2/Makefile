CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
INCLUDEDIR = -I/opt/homebrew/Cellar/sfml/2.6.1/include
LIBDIR = -L/opt/homebrew/Cellar/sfml/2.6.1/lib
# Your .hpp files
DEPS = PTree.hpp
# Your compiled .o files
OBJECTS = PTree.o
# The name of your program
PROGRAM = PTree

TEST = test

.PHONY: all clean lint

all: $(PROGRAM)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): $(OBJECTS) main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp