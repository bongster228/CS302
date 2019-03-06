OBJ = palNums.o
CC = g++ -Wall -pedantic -Wextra -std=c++11 -g -pthread

all: palNums

palNums: $(OBJ)
	$(CC) $(OBJ) -o palNums
	cp palNums test/

palNums.o: palNums.cpp
	$(CC) -c palNums.cpp

.PHONY: clean
clean:
	-rm $(OBJ)
