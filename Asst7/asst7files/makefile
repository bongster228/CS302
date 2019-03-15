OBJ = wordHash.o main.o
DEPS = wordHash.h
CC = g++ -Wall -pedantic -Wextra -std=c++11 -g

all: hash

hash: $(OBJ) $(DEPS)
	$(CC) $(OBJ) -o hash
	cp hash test/

main.o: main.cpp $(DEPS)
	$(CC) -c main.cpp

wordHash.o: wordHash.cpp $(DEPS)
	$(CC) -c wordHash.cpp

.PHONY: clean
clean:
	-rm $(OBJ)