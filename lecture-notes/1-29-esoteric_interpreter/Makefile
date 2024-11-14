CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -I/opt/homebrew/Cellar/sfml/2.6.1/include -o sfml-app -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/boost/1.84.0/include 
LIBDIR = -L/opt/homebrew/Cellar/boost/1.84.0/lib
# Your .hpp files
DEPS = brainfuck.hpp
# Your compiled .o files
OBJECTS = brainfuck.o
# The name of your program
PROGRAM = 

TEST = test

.PHONY: all clean lint


all: $(PROGRAM) $(TEST)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

$(TEST): testo. $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
