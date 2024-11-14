CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB =
# Your .hpp files
DEPS = Concordance.hpp
# Your compiled .o files
OBJECTS = Concordance.o
# The name of your program
PROGRAM = Concord

.PHONY: all clean lint

all: $(PROGRAM)

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
