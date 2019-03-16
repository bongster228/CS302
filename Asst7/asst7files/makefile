OBJ1 = wordHash.o
OBJ2 = wordCount.o concordance.o
DEPS = wordHash.h wordCount.h
CC = g++ -Wall -pedantic -Wextra -std=c++11 -g

all: concordance

concordance: $(OBJ1) $(OBJ2) $(DEPS)
	$(CC) $(OBJ1) $(OBJ2) -o concordance
	cp concordance test/

wordHash.o: wordHash.cpp $(DEPS)
	$(CC) -c wordHash.cpp

wordCount.o: wordCount.cpp $(DEPS)
	$(CC) -c wordCount.cpp

concordance.o: concordance.cpp $(DEPS)
	$(CC) -c concordance.cpp


.PHONY: clean
clean:
	-rm $(OBJ1) $(OBJ2)