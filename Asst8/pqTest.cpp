//  Main program for testing

#include <iostream>
#include <string>
#include <cstdlib>

#include "priorityQueue.h"

using namespace std;

int main()
{

// *****************************************************************
//  Headers...

	string	stars, bars, dashes;
	stars.append(65, '*');
	bars.append(65, '=');
	dashes.append(40,'-');
	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";

	int	currPriority;

	cout << stars << endl << bold << "CS 302 - Assignment #8" << endl;
	cout << "Priority Queue Tester" << unbold << endl;
	cout << endl;

// ------------------------------------------------------------------
//  Initial testing, very small heap.
//	Always prints...

	priorityQueue<string>	myHeap0;
	string	currName;

	cout << endl << bars << endl << bold <<
		"Test Set #0" << unbold << endl;

	myHeap0.insert("google", 1);
	myHeap0.insert("amazon", 2);
	myHeap0.insert("newegg", 3);
	myHeap0.insert("apple", 4);
	myHeap0.insert("dell", 5);
	myHeap0.insert("oracle", 6);
	myHeap0.insert("cisco", 7);
	myHeap0.insert("jupiter", 8);
	myHeap0.insert("belkin", 9);
	myHeap0.insert("ebay", 10);

	cout << dashes << endl << "PQ Heap (level order):" << endl;
	myHeap0.printHeap();

	cout << dashes << endl << "PQ Heap Size: " << myHeap0.entries() << endl;
	cout << "Priority Order:" << endl;
	while (!myHeap0.isEmpty()) {
		myHeap0.deleteMin(currName, currPriority);
		cout << currName << "  " << currPriority << endl;
	}

// ------------------------------------------------------------------
//  Some very basic testing.

	priorityQueue<char>	myHeap1;
	char	currChar;

	cout << endl << bars << endl << bold <<
		"Test Set #1" << unbold << endl;

	myHeap1.insert('g', 1);
	myHeap1.insert('x', 1);
	myHeap1.insert('y', 1);
	myHeap1.insert('a', 3);
	myHeap1.insert('n', 5);
	myHeap1.insert('p', 7);
	myHeap1.insert('d', 9);
	myHeap1.insert('o', 2);
	myHeap1.insert('c', 4);
	myHeap1.insert('j', 6);
	myHeap1.insert('b', 8);
	myHeap1.insert('e', 11);
	myHeap1.insert('f', 12);
	myHeap1.insert('h', 13);
	myHeap1.insert('k', 14);
	myHeap1.insert('m', 15);

	cout << dashes << endl << "PQ Heap (level order):" << endl;
	myHeap1.printHeap();

	cout << dashes << endl << "PQ Heap Size: " << myHeap1.entries() << endl;
	cout << "Priority Order:" << endl;
	while (!myHeap1.isEmpty()) {
		myHeap1.deleteMin(currChar, currPriority);
		cout << currChar << "  " << currPriority << endl;
	}

// ------------------------------------------------------------------
//  Testing for addresses.
//	DOes not print addresses since they can change between executions...

	int	**arrs;
	arrs = new int *[10];
	for (int i=0; i<10; i++)
		arrs[i] = new int[9];
	int	*currArr;

	priorityQueue<int *>	myHeap2;

	cout << endl << bars << endl << bold <<
		"Test Set #2" << unbold << endl;

	for (int i=0; i<10; i++)
		myHeap2.insert(arrs[i], i+10);

	cout << dashes << endl << "PQ Heap Size: " << myHeap2.entries()
		<< endl;

	while (!myHeap2.isEmpty())
		myHeap2.deleteMin(currArr, currPriority);

// ------------------------------------------------------------------
//  Large testing...

	priorityQueue<int>	myHeap3;
	int	size=1000000;
	bool	passed=true;
	int	j, k;

	cout << endl << bars << endl << bold <<
		"Test Set #3" << unbold << endl;

	for (int i=size-1; i>=0; i--)
		myHeap3.insert(i, i);

	for (int i=0; i<size; i++) {
		myHeap3.deleteMin(j, k);
		if (i != j) {
			passed = false;
			cout << "Error, deleteMin() fail." << endl;
		}
	}

	if (passed)
		cout << "Large test successful." << endl;
	else
		cout << "Large test fail." << endl;


// ------------------------------------------------------------------
//  File testing.
//	reads file, which tests the buildHeap() function.

	priorityQueue<string>	myHeap4;
	int	limit=10;
	string	currEmail;
	int	p;

	cout << endl << bars << endl << bold <<
		"Test Set #4" << unbold << endl;

	myHeap4.readData("emails.csv");

	for (int i=0; i<limit; i++) {
		myHeap4.deleteMin(currEmail, p);
		cout << "Email (" << p << "):  " << currEmail << endl;
	}


// *****************************************************************
//  All done.

	cout << endl << stars << endl <<
		"Game Over, thank you for playing." << endl;

	return 0;
}

