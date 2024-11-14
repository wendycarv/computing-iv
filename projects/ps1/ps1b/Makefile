CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/boost/1.83.0/include -I/opt/homebrew/Cellar/sfml/2.6.1/include
LIBDIR = -L/opt/homebrew/Cellar/boost/1.83.0/lib -L/opt/homebrew/Cellar/sfml/2.6.1/lib# Your .hpp files
DEPS = FibLFSR.hpp PhotoMagic.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o PhotoMagic.o
# The name of your program
PROGRAM = PhotoMagic

.PHONY: all clean lint

all: $(PROGRAM) test $(PROGRAM).a 

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): $(OBJECTS) main.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

$(PROGRAM).a: $(OBJECTS)
	ar rcs $@ $^ $(LIBDIR) $(LIB)
	
test: $(OBJECTS) test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm *.o $(PROGRAM) test

lint:
	cpplint *.cpp *.hpp

