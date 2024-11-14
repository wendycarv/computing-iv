CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
INCLUDEDIR = -I/opt/homebrew/Cellar/sfml/2.6.1/include
LIBDIR = -L/opt/homebrew/Cellar/sfml/2.6.1/lib
# Your .hpp files
DEPS = Pong.hpp Paddle.hpp Ball.hpp Breakout.hpp Brick.hpp
# Your compiled .o files
OBJECTS = Pong.o Paddle.o Ball.o Breakout.o Brick.o
# The name of your program
PROGRAM = Pong

.PHONY: all clean lint

all: Pong Breakout

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

Pong: PongGame.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

Breakout: BreakoutGame.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp
