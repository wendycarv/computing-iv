CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/boost/1.84.0/include 
LIBDIR = -L/opt/homebrew/Cellar/boost/1.84.0/lib
# Your .hpp files
DEPS = FibLFSR.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o 
# The name of your program
PROGRAM = PhotoMagic

.PHONY: all clean lint

all: $(PROGRAM) test # $(PROGRAM).a 

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): $(OBJECTS) main.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

# define test
test: $(OBJECTS) test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm *.o $(PROGRAM) test

lint:
	cpplint *.cpp *.hpp

