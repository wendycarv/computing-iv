CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I/opt/homebrew/Cellar/boost/1.84.0/include
LIB = -lboost_unit_test_framework -L/opt/homebrew/Cellar/boost/1.84.0/lib
# Your .hpp files
DEPS = bracket.hpp
# Your compiled .o files
OBJECTS = bracket.o
# The name of your program
PROGRAM = bracket

.PHONY: all clean lint

all: $(PROGRAM) test

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM) test

lint:
	cpplint *.cpp *.hpp
