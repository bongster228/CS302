OBJ = elbonia.o undirectedGraph.o
DEPS = priorityQueue.h undirectedGraph.h
CC = g++ -Wall -pedantic -Wextra -std=c++11 -g

all: elbonia

elbonia: $(OBJ) $(DEPS)
	$(CC) $(OBJ) -o elbonia

undirectedGraph.o: undirectedGraph.cpp $(DEPS)
	$(CC) -c undirectedGraph.cpp

elbonia.o: elbonia.cpp $(DEPS)
	$(CC) -c elbonia.cpp

.PHONY: clean
clean:
	-rm $(OBJ)