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

    // Create states array to store intermediate states and initialize.
    states = new unsigned int*[stateSize];
    
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

    // Array created to store puzzle from file.
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

bool puzzle::findSolution(){

    // Ensure initialState and goalState are valid.
    if(!isValid(initialState) || !isValid(goalState)) return false;

    priorityQueue<unsigned int> priorityStates;
    unsigned int statesIndex = 0;

    unsigned int dequeuedIndex = 0;
    int dequeuedPriority = 0;

    // initialState is stored at index 0 in the states array.
    priorityStates.insert(statesIndex, initialState[numOfTiles + 1]);
    
    // The initialState in put in the 0th index of the states array.
    states[statesIndex] = initialState;

    unsigned int *moveUp, *moveDown, *moveLeft, *moveRight, *intermeidateState;

    while(!priorityStates.isEmpty() && statesIndex <= stateSize){

        priorityStates.deleteMin(dequeuedIndex, dequeuedPriority);

        // Break out of the loop if solution is found.
        if(isGoal(states[dequeuedIndex])) break;

        // Get the copy of current state. Make deep copy.
        intermeidateState = states[dequeuedIndex];

        // Check for legal moves using moveTile function. If move is legal, create new state.
        // Also check for repeated state, 


        // Move the blank tile in the array.
        // 1 is up, 2 is down, 3 is left, 4 is right

        // Move up
        


    }


}

//--------------------------------------------------------------------------------------------

int puzzle::manhattan(unsigned int puzzleArr[]) const{

    int x0, y0, x1, y1, val;
    int sum = 0;

    for(int i = 0; i < numOfTiles; ++i){

        x0 = i % order;
        y0 = i / order;
        val = puzzleArr[i];
        if(val == 0) continue;

        for(int j = 0; j < numOfTiles; ++j){
            if(val == goalState[j]){
                x1 = j % order;
                y1 = j / order;
            }
        }
        
        sum += (abs(x1 - x0) + abs(y1 - y0));
    }

    return sum;
}


//############################################################################################
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

//--------------------------------------------------------------------------------------------

bool puzzle::isGoal(unsigned int puzzleArr[]) const{

    for(int i = 0; i < numOfTiles; ++i){
        if(puzzleArr[i] != goalState[i]) return false;
    }

    return true;

}

//--------------------------------------------------------------------------------------------

bool puzzle::isRepeat(unsigned int puzzleArrp[]) const{

}

//--------------------------------------------------------------------------------------------

void puzzle::printSolution(int num, int num2) const{

}

//--------------------------------------------------------------------------------------------

bool puzzle::moveTile(unsigned int puzzleArr[], int direction){

    // 1 is up, 2 is down, 3 is left, 4 is right

    unsigned int blankTileIndex = 0;
    int moveChecker = 0;            // Used to check for legal moves.
    unsigned int temp = 0;

    // Find the location of the blank tile.
    for(int i = 0; i < numOfTiles; ++i){
        if(puzzleArr[i] == 0) blankTileIndex = i;
    }

    // Move tile up. Checks move if its legal
    moveChecker = blankTileIndex - order;
    if(direction == 1 && moveChecker > 0){

        // Swap the tiles
        temp = puzzleArr[blankTileIndex - order];
        puzzleArr[blankTileIndex - order] = 0;
        puzzleArr[blankTileIndex] = temp;

        // Store movement info in the array.
        puzzleArr[numOfTiles + 2] = direction;

        return true;
    }

    // Move tile down. 
    moveChecker = blankTileIndex + order;
    if(direction == 2 && moveChecker < numOfTiles){

        temp = puzzleArr[blankTileIndex + order];
        puzzleArr[blankTileIndex + order] = 0;
        puzzleArr[blankTileIndex] = temp;

        puzzleArr[numOfTiles + 2] = direction;

        return true;
    }

    // Move tile left.
    if(direction == 3 && blankTileIndex % order != 0){

        temp = puzzleArr[blankTileIndex - 1];
        puzzleArr[blankTileIndex - 1] = 0;
        puzzleArr[blankTileIndex] = temp;

        puzzleArr[numOfTiles + 2] = direction;

        return true;
    }

    // Move tile right.
    moveChecker = blankTileIndex + 1;
    if(direction == 4 && moveChecker % order != 0){
        temp = puzzleArr[blankTileIndex + 1];
        puzzleArr[blankTileIndex + 1] = 0;
        puzzleArr[blankTileIndex] = temp;

        puzzleArr[numOfTiles + 2] = direction;

        return true;
    }    

    return false;
}

