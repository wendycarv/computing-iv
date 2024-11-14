CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIBS = -lboost_unit_test_framework
DEPS = unique.hpp

SRCS = $(shell find src -name 'unique*.cpp')

PROGS = $(patsubst src/%.cpp,bin/%.out, $(SRCS))
RUNS = $(patsubst src/%.cpp,run-%, $(SRCS))

.PHONY: all run clean lint

all: $(PROGS)

run: $(RUNS)

run-%: bin/%.out
	-$<

obj/%.o: src/%.cpp src/$(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

bin/%.out: obj/%.o obj/tests.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm obj/*.o bin/*.out
