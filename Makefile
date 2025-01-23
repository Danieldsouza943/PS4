CC = g++
CFLAGS = --std=c++17 -O3 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = Sokoban.hpp
# Your compiled .o files
OBJECTS = Sokoban.o
# The name of your program
PROGRAM = Sokoban
TEST = test

.PHONY: all clean lint


all: Sokoban.a $(PROGRAM) $(TEST)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

Sokoban.a: Sokoban.o
	ar rcs Sokoban.a Sokoban.o

$(PROGRAM): $(OBJECTS) main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(TEST): $(OBJECTS) test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f *.o *.a $(PROGRAM) $(TEST)

lint:
	cpplint *.cpp *.hpp
