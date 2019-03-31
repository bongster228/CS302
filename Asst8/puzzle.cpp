#include "puzzle.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

//--------------------------------------------------------------------------------------------
// Public Members

puzzle::puzzle(){
    
    order = 0;
    title = "Puzzle";
    numOfTiles = 0;


    initialState = nullptr;
    goalState = nullptr;
    states = nullptr; 
}

//--------------------------------------------------------------------------------------------

puzzle::puzzle(int puzzleOrder = 0, string puzzleTitle = "Puzzle"){

    if(puzzleOrder <= ORDER_MIN || puzzleOrder >= ORDER_MAX){
        cout << "Invalid order size. Must be between " << ORDER_MIN << " and " << ORDER_MAX << "." << endl;
    }

    order = puzzleOrder;
    title = puzzleTitle;
    numOfTiles = 0;

    initialState = nullptr;
    goalState = nullptr;
    states = nullptr;    
}

//--------------------------------------------------------------------------------------------

puzzle::~puzzle(){

}

//--------------------------------------------------------------------------------------------

string puzzle::getTitle() const{
    return title;
}

//--------------------------------------------------------------------------------------------

void puzzle::setInitialState(unsigned int puzzleArr[]){


    if(isValid(puzzleArr)){

        // Create new initial state based on puzzle order.
        initialState = new unsigned int[numOfTiles + 2];

        // The move and the parent index value are initialized.        
        initialState[numOfTiles + 1] = 0;
        initialState[numOfTiles + 2] = 0;

        // Make deep copy of initialState from passed in array.
        for(int i = 0; i < numOfTiles; ++i){
            initialState[i] = puzzleArr[i];
        }

    }

}

//--------------------------------------------------------------------------------------------

void puzzle::setGoalState(unsigned int goalArr[]){


    if(isValid(goalArr)){

        goalState = new unsigned int[numOfTiles + 2];

        // Make deep copy to goalState from passed in array.
        for(int i = 0; i < numOfTiles + 2; ++i){
            goalState[i] = goalArr[i];
        }

    }

}

//--------------------------------------------------------------------------------------------

void puzzle::printPuzzle() const{


    if(isValid(initialState)){

        for(int i = 0; i < numOfTiles; ++i){

            if(i % order == 0) cout << endl;

            cout << initialState[i] << " ";
        }
    }
}

//--------------------------------------------------------------------------------------------

void puzzle::printPuzzle(unsigned int puzzleArr[]) const{


    if(isValid(puzzleArr)){
        
        for(int i = 0; i < numOfTiles; ++i){

            if(i % order == 0) cout << endl;

            cout << initialState[i] << " ";
        }
    }
}

//--------------------------------------------------------------------------------------------

bool puzzle::readPuzzle(string fileName){

    fstream puzzleFile;
    
    puzzleFile.open(fileName);
    if(!puzzleFile.is_open()){
        cout << "File cannot be opened" << endl;
        return false;
    }

    getline(puzzleFile, title);

    puzzleFile >> order;

    numOfTiles = order * order;

    unsigned int puzzleFromFile[ORDER_MAX];

    for(int i = 0; i < numOfTiles; ++i){
        puzzleFile >> puzzleFromFile[i];
    }

    if(isValid(puzzleFromFile)){
        setInitialState(puzzleFromFile);
    }


    return true;
}


//--------------------------------------------------------------------------------------------
// Private Members

bool puzzle::isValid(unsigned int puzzleArr[]) const{


    // Check for duplicates
    int *duplicate = new int[numOfTiles];

    for(int j = 0; j < numOfTiles; ++j){
        duplicate[j] = 0;
    }


    for(int i = 0; i < numOfTiles; ++i){

        // Check each element in the array to make sure the tile values are in range
        if(puzzleArr[i] < 0 || puzzleArr[i] > numOfTiles - 1){
            return false;
        }

        // Increment using elements in the puzzleArr as index.
        duplicate[puzzleArr[i]]++;
    }

    // Return false if any elements in the puzzleArry appear more than once.
    for(int k = 0; k < numOfTiles; ++k){
        if(duplicate[k] != 1) return false;
    }

    delete[] duplicate;


    return true;

}