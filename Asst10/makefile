OBJ = main.o
DEPS = skipList.h
CC = g++ -Wall -Wextra -std=c++11 -g

all: main

main: $(OBJ) $(DEPS)
	$(CC) $(OBJ) -o main

main.o: main.cpp $(DEPS)
	$(CC) -c main.cpp

.PHONY:clean
clean:
	-rm $(OBJ)