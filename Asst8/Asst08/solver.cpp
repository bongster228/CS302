//  CS 302 Provided Main

#include <iostream>
#include <iomanip>
#include <string>

#include "puzzle.h"

using namespace std;

// *****************************************************************

int main(int argc, char *argv[])
{

// ---------------------------------------
//  Headers...

	string	bars, stars;
	bars.append(65, '-');
	stars.append(65, '*');
	string	fileName="";

	cout << bars << endl << "CS 302 - Assignment #8" << endl;
	cout << endl;

// ---------------------------------------
//  Read puzzle file from command line.

	puzzle	myPuzzle;
	unsigned int	goal[] = {1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0};

	switch (argc) {
		case 1:
			cout << "Usage: solver <puzzle file>" << endl;
			break;

		case 2:
			if (myPuzzle.readPuzzle(string(argv[1]))) {
				myPuzzle.setGoalState(goal);
				cout << "Puzzle: " << myPuzzle.getTitle()
					<< endl << endl;
				if (!myPuzzle.findSolution()) {
					myPuzzle.printPuzzle();
					cout << "No solution exists." << endl;
				}
			}
			break;

		default:
			cout << "Error, invalid command line options." << endl;
			break;
	}

	cout << stars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}

