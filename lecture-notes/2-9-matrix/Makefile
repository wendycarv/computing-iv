CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system #-lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/sfml/2.6.1/include # -I/opt/homebrew/Cellar/boost/1.83.0/include
LIBDIR = -L/opt/homebrew/Cellar/sfml/2.6.1/lib #-L/opt/homebrew/Cellar/boost/1.83.0/lib 
# Your .hpp files
DEPS = matrix.hpp
# Your compiled .o files
OBJECTS = matrix.o
# The name of your program
PROGRAM = matrix 

TEST = test

.PHONY: all clean lint

all: $(PROGRAM)

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
