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
    usedStates = 0;


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

    delete[] goalState;

    for(int i = 0; i < usedStates; ++i){
        delete[] states[i];
    }

    delete[] states;

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
        for(int i = 0; i < numOfTiles + 2; ++i){
            initialState[i] = 0;
        }


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

    for(int i = 0; i <= numOfTiles; ++i){

        if(i % order == 0){
            if(i == 0) cout << "   ____ ____ ____";
            else cout << endl << "  |____|____|____|";

            if(i == numOfTiles) continue;

            cout << endl << "  |    |    |    |" << endl;
            cout << "  |";
        }

        if(initialState[i]) cout << "  " << initialState[i] << " |";
        else cout << "    |";
    
    }
}

//--------------------------------------------------------------------------------------------

void puzzle::printPuzzle(unsigned int puzzleArr[]) const{


    for(int i = 0; i <= numOfTiles; ++i){

        if(i % order == 0){
            if(i == 0) cout << "   ____ ____ ____";
            else cout << endl << "  |____|____|____|";

            if(i == numOfTiles) continue;

            cout << endl << "  |    |    |    |" << endl;
            cout << "  |";
        }

        if(puzzleArr[i]) cout << "  " << puzzleArr[i] << " |";
        else cout << "    |";
    
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


    // the initialState is put into the priority queue with 0 priority value.
    priorityStates.insert(statesIndex, 0);


    // The initialState in the 0th index of the states array.
    states[statesIndex] = initialState;


    unsigned int *intermeidateState = nullptr;
    int priority = 0, level = 0;


    while(!priorityStates.isEmpty() && statesIndex <= stateSize){

        priorityStates.deleteMin(dequeuedIndex, dequeuedPriority);

        // Break out of the loop if solution is found.
        if(isGoal(states[dequeuedIndex])){
            usedStates = statesIndex;            // Used to deallocate memory in the destructor.
            printSolution(dequeuedIndex, 0);
            return true;
        }

        level++;

        // Move the blank tile in the array.
        // 1 is up, 2 is down, 3 is left, 4 is right
        for(int i = 1; i < 5; ++i){

            intermeidateState = new unsigned int[numOfTiles + 3];


            // Get the copy of current state. Make deep copy.
            deepCopyArr(states[dequeuedIndex], intermeidateState, numOfTiles + 2);


            // Passed in intermediateState is modified inside the moveTile function.
            if(moveTile(intermeidateState, i)){

                if(isRepeat(intermeidateState)) delete[] intermeidateState;
                else{

                    statesIndex++;
        
                    // Store the parent index.
                    intermeidateState[numOfTiles + 1] = dequeuedIndex;
                    states[statesIndex] = intermeidateState;

                    if(isGoal(intermeidateState)) {
                        usedStates = statesIndex;
                        printSolution(statesIndex, 0);
                        return true;
                    }

                    priority = manhattan(intermeidateState) + level;
                    priorityStates.insert(statesIndex, priority);
                
                } // end else{}

            } // end if()

        } // end for()

    } // end while()

    return false;
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

bool puzzle::isRepeat(unsigned int puzzleArr[]) const{

    int parentIndex = puzzleArr[numOfTiles + 1];

    // Check for duplicate board with initial state.
    if(isSameArr(puzzleArr, states[0])) return true;

    // Repeat check up to the inital state of index 0;
    while(parentIndex > 0){

        // Check all the tiles of the same path to see if the board is
        // a repeat of previous move.
        if(isSameArr(puzzleArr, states[parentIndex])) return true;

        // Move the parentIndex up the path to initial state.
        parentIndex = states[parentIndex][numOfTiles + 1];

    }
    
    // Return false if the move is not a repeat.
    return false;

}

//--------------------------------------------------------------------------------------------

bool puzzle::isSameArr(unsigned int arr1[], unsigned int arr2[]) const{

    for(int i = 0; i < numOfTiles; ++i){
        if(arr1[i] != arr2[i]) return false;
    }

    return true;

}

//--------------------------------------------------------------------------------------------

void puzzle::printSolution(unsigned int index, int step) const{

    if(index == 0){
        cout << "Solution in " << step << " steps." << endl << endl;
        cout << "Initial:" << endl;
        printPuzzle();
        cout << "     move: initial";
        cout << endl << endl;
        return;
    }

    printSolution(states[index][numOfTiles + 1], step + 1);

    printPuzzle(states[index]);

    cout << "     move: ";

    switch(states[index][numOfTiles + 2]){
        case 1:
            cout << "up";
            break;
        case 2:
            cout << "down";
            break;
        case 3:
            cout << "left";
            break;
        case 4:
            cout << "right";
            break;
    }
    cout << endl << endl << endl << endl;

}

//--------------------------------------------------------------------------------------------

bool puzzle::checkMoves(unsigned int puzzleArrp[]) const{

    

}

//--------------------------------------------------------------------------------------------
bool puzzle::moveTile(unsigned int puzzleArr[], unsigned int direction){

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


//--------------------------------------------------------------------------------------------

void puzzle::deepCopyArr(unsigned int original[], unsigned int copy[], int size){

    for(int i = 0; i < size; ++i){
        copy[i] = original[i];
    }

}

