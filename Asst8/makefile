OBJ1 = pqTest.o
OBJ2 = puzzle.o solver.o
DEPS = priorityQueue.h puzzle.h
CC = g++ -Wall -pedantic -Wextra -std=c++11 -g

all: solver pqTest

pqTest: $(OBJ1) $(DEPS)
	$(CC) $(OBJ1) -o pqTest

solver: $(OBJ2) $(DEPS)
	$(CC) $(OBJ2) -o solver

pqTest.o: pqTest.cpp $(DEPS)
	$(CC) -c pqTest.cpp

puzzle.o: puzzle.cpp $(DEPS)
	$(CC) -c puzzle.cpp

solver.o: solver.cpp $(DEPS)
	$(CC) -c solver.cpp


.PHONY: clean
clean:
	-rm $(OBJ1) $(OBJ2)