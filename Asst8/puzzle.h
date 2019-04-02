#include "priorityQueue.h"
#include <string>

class puzzle{

public:

    puzzle();

    puzzle(int, std::string);                       // If order parameter is not zero, it must check to ensure it is between
                                                    // ORDER_MIN and ORDER_MAX, if not error message should be displayed.
    ~puzzle();

    void setInitialState(unsigned int[]);           // Verify that the passed int array is valid by calling isValid(). If valid
                                                    // create and populate initial state array.

    void setGoalState(unsigned int[]);              // Verify the passed in array using isValid(). If valid, create and populate
                                                    // the goal state array.

    void printPuzzle(unsigned int[]) const;         // Display the formatted puzzle of the passed puzzle state array. Function should
                                                    // use the isValid() to ensure the array is valid.  
                                                    
    void printPuzzle() const;                       // Should, if it exists, print the initial state by using printPuzzle().
   
    bool readPuzzle(std::string);                   // Read a puzzle from the passed file name. Return false if file cannot be opened,
                                                    // or contained puzzle is not valid return false. Use isValid(). If the puzzle is
                                                    // valid, contents should be placed in the initialState(after it is created).

    bool findSolution();                            // Find a solution to the current puzzle(initial state to goal state). This includes
                                                    // ensuring that the order, initial state, and goal state array have been set and valid.

    int manhattan(unsigned int[]) const;            // Compute the sum of the manhattan distance between each tile in passed state and goal
                                                    // state (excluding blank tile).


    void setTitle(std::string);                     // Set the current tile to the passed value.
    std::string getTitle() const;                   // Return the current puzzle title.


private:

    std::string title;
    int order;
    int numOfTiles;
    unsigned int usedStates;
    unsigned int *initialState;
    unsigned int *goalState;
    unsigned int **states;


    static const int stateSize = 80000000;
    static const int ORDER_MIN = 3;
    static const int ORDER_MAX = 25;

    bool isValid(unsigned int[]) const;         // Should verify that the passed array is valid by ensuring that the initial order
                                                // entries are between 0 and order - 1 with each appearing only once.

    bool isGoal(unsigned int[]) const;          // Compare the passed state to the goal state and return true if they match and false
                                                // otherwise. Function should only check tile positions(i.e 0-8 for 8 puzzle with order 3)
    
    bool isRepeat(unsigned int[]) const;        // Compare the passed state to all of its parent (via the parent index pointer in the
                                                // state arrays) and return true if a copy was found and return false otherwise. 
                                                // Only chekc the approriate tile positions(i.e. 0-8 for the 8 puzzle with order 3)

    void printSolution(unsigned int, int) const;         // Recursively print the formatted solution using the parent state array index pointers
                                                // and the printPuzzle().

    void deepCopyArr(unsigned int[], unsigned int[], int);

    bool isSameArr(unsigned int[], unsigned int[]) const;

    bool checkMoves(unsigned int[]) const;

    bool moveTile(unsigned int[], unsigned int);

};