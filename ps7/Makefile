CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/boost/1.84.0/include -I/opt/homebrew/Cellar/sfml/2.6.1/include
LIBDIR = -L/opt/homebrew/Cellar/boost/1.84.0/lib -L/opt/homebrew/Cellar/sfml/2.6.1/lib
# Your .hpp files
DEPS =
# Your compiled .o files
OBJECTS =
# The name of your program
PROGRAM = ps7

.PHONY: all clean lint

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): $(OBJECTS) main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

$(PROGRAM).a: $(OBJECTS)
	ar rcs $@ $^

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
