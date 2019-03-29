OBJ = pqTest.o
DEPS = priorityQueue.h
CC = g++ -Wall -pedantic -Wextra -std=c++11 -g

all: heapTest

heapTest: $(OBJ) $(DEPS)
	$(CC) $(OBJ) -o heapTest

	cp heapTest test/

pqTest.o: pqTest.cpp $(DEPS)
	$(CC) -c pqTest.cpp

.PHONY: clean
clean:
	-rm $(OBJ)