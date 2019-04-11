//  CS 302, Assignment #10
//  Implement a concordance.
//  Main program for word counting.

#include <iostream>
#include <fstream>
#include <string>

#include "wordCount.h"

using namespace std;

int main(int argc, char *argv[])
{

// *****************************************************************
//  Headers, declarations...

	string	bars, stars;
	string	docFile;			// input document file name
	string	outFile;			// output file name
	bool	showHash=false;			// display tree flag

	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";
	const char* green   = "\033[32m";

	bars.append(60, '-');
	stars.append(60, '*');

	cout << bold << bars << endl << "CS 302 - Assignment #10" << unbold << endl;
	cout << endl;

// *****************************************************************
//  Get command line information...

	wordCount	myDocument;
	unsigned int	maxCount = 0;
	string		maxWord = "";

	if (!myDocument.getArguments(argc, argv, docFile, showHash))
		exit(1);

//  Get document concordance (if file is OK).

	if (myDocument.readDocument(docFile) ) {
		cout << bold << green << "Document Information:" << endl;
		cout << "---------------------" << unbold << endl;

		myDocument.showDocumentFileName();
		cout << endl;
		myDocument.showTotalWordCount();
		myDocument.showUniqueWordCount();
		myDocument.showStats();
		myDocument.getMaxWord(maxCount, maxWord);

		cout << endl;
		cout << "Most Frequent Word is: '" << maxWord <<
			"' occurring " << maxCount << " times." << endl;

		if (showHash)
			myDocument.printWordCounts();
	} else {
		cout << "Error, unable to open file: " << docFile << endl;
	}

	cout << endl;

// *****************************************************************
//  All done.

	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}

