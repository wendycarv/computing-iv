CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = 
# Your .hpp files
DEPS = Complex.hpp
# Your compiled .o files
OBJECTS = 
# The name of your program
PROGRAM = Complex

.PHONY: all clean lint


all: $(PROGRAM)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
