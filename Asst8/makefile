OBJ = main.o
DEPS = priorityQueue.h
CC = g++ -Wall -pedantic -Wextra -std=c++11 -g

all: heapTest

heapTest: $(OBJ) $(DEPS)
	$(CC) $(OBJ) -o heapTest

main.o: main.cpp $(DEPS)
	$(CC) -c main.cpp