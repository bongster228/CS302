#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>


// Node struct for linked list
template<class myType>
struct nodeType{

    myType keyValue = {};
    int isSent = 0;
    unsigned int count = 0;

    // Pointers
    nodeType<myType> *up = nullptr, *down = nullptr, *left = nullptr, *right = nullptr;
};


template<class myType>
class skipList{

public:

skipList();                                         // Initialize skipList to an empty state.
~skipList();
void insert(myType);                                // Increment the word count if the item is already in the skip list. If not use the
                                                    // private insert function to pass item into skip list.
unsigned int getUniqueWordCount() const;
unsigned int getWordCount(myType item) const;
void getMaxNode(unsigned int&, myType&) const;
void printSkipList() const;                         // Print all entries in the base layer of the skip list and their counts, one per line.

void showSkipListStats() const;                     // Utility function to print the current skip list height, expected height, the number
                                                    // of nodes in each level, and the % of nodes in each layer relative to the number of
                                                    // nodes in the base layer.

private:


// Private variables
unsigned int nodeCount;
unsigned int totalCount;
unsigned int height;
nodeType<myType> *head;
nodeType<myType> *tail;

// Private Functions
int coinFlip() const;                               // Return either 0 or 1 (i.e. rand() % 2)

void addLayer();                                    // Initialize a new topmost layer in the skip list with left and right sentinel nodes.

nodeType<myType>* findEntry(myType k) const;              // Search the skip list for a given key, k, and return a node in the base layer with
                                                    // a key equal to k or greatest key in the skip list less than k.

bool insert(myType, nodeType<myType>*);             // Create a tower of nodes with 50% chance to increase the tower height by one each
                                                    // time. THe coinFLip() should be called to determine whether new node in the tower
                                                    // should be created. Additional layers in the list should be initialized as
                                                    // necessary if the tower becomes larger than the skip list.

};

//-----------------------------------------------------------------------------------
// Public Members

template<class myType>
skipList<myType>::skipList(){
    nodeCount = 0;
    totalCount = 0;
    height = 0;

    // Create and link sentinel head and tail.
    // Left sentinel node has isSent -1 and right sentinel node has isSent 1.
    head = new nodeType<myType>;
    head -> isSent = -1;
    tail = new nodeType<myType>;
    tail -> isSent = 1;

    head -> right = tail;
    tail -> left = head;
}

//-----------------------------------------------------------------------------------

template<class myType>
skipList<myType>::~skipList(){

    nodeType<myType> *curr;

    // Delete all nodes in each level.
    while(head != nullptr){
    
    curr = head;
    head = head -> down;

        // Move curr to right and delete previous node.
        while(curr -> right != nullptr){
            curr = curr -> right;
            delete curr -> left;
        }

    // Lastly delete the sentinel node at the end.
    delete curr;
    
    }
}

//-----------------------------------------------------------------------------------

template<class myType>
void skipList<myType>::insert(myType item){

    // If item is already in the skip list, increment the counts.
    nodeType<myType> *entry = findEntry(item);

    if(entry -> keyValue == item){
        entry -> count++;
        totalCount++;
        return;
    }

    // Else insert new node into the list
    else{
        insert(item, entry);
    }
}

//-----------------------------------------------------------------------------------
template<class myType>
unsigned int skipList<myType>::getUniqueWordCount() const{
    return nodeCount;
}

//-----------------------------------------------------------------------------------

template<class myType>
unsigned int skipList<myType>::getWordCount(myType item) const{
    
    // Search the skip list for the item. If found return the count else return 0.
    nodeType<myType> *searchNode = findEntry(item);

    if(searchNode -> keyValue == item){
        return searchNode -> count;
    }
    else{
        return 0;
    }
}

//-----------------------------------------------------------------

template<class myType>
void skipList<myType>::getMaxNode(unsigned int &count, myType &item) const{

    nodeType<myType> *searchNode = head;
    nodeType<myType> *maxNode = nullptr;

    // Move the searchNode down to the base layer.
    while(searchNode -> down != nullptr){
        searchNode = searchNode -> down;
    }

    maxNode = searchNode;

    // Search through the entire base list to get the maxNode.
    while(searchNode -> isSent != 1){

        if(searchNode -> count > maxNode -> count){
            maxNode = searchNode;
        }
        else{
            searchNode = searchNode -> right;
        }
    }



    item = maxNode -> keyValue;
    count = maxNode -> count;

}

//-----------------------------------------------------------------------------------

template<class myType>
void skipList<myType>::printSkipList() const{

    nodeType<myType> *curr = head;


    // Move curr down to the base.
    while(curr -> down != nullptr){
        curr = curr -> down;
    }

    while(curr -> right -> isSent != 1){
        curr = curr -> right;
        std::cout << curr -> keyValue << " " << curr -> count << std::endl;   
    }

}

//-----------------------------------------------------------------------------------

template<class myType>
void skipList<myType>::showSkipListStats() const{

    std::cout << "Skip List Stats" << std::endl;
    std::cout << "\tCurrent Height: " << height << std::endl;
    std::cout << "\tExpected Height: " << ceil(log2(nodeCount)) << std::endl;
    std::cout << "\tNumber of nodes in each level: " << std::endl;

    // Use loop to traverse each layer down to the base list. Keep a counter to count
    // the number of nodes in each layer.
    nodeType<myType> *lvlPtr, *lvlCounter;
    double nodeCounter;
    lvlPtr = head;

    for(int listLvl = height; listLvl >= 0; --listLvl){
        nodeCounter = 0;

        // Start from the beginning of the level and count until right sentinel is reached.
        lvlCounter = lvlPtr -> right;
        while(lvlCounter -> isSent != 1){
            nodeCounter++;
            lvlCounter = lvlCounter -> right;
        }
        
        // % of nodes on each level compared to base list.
        unsigned long percent = 10000 * nodeCounter / nodeCount;

        std::cout << "\t\tLevel " << listLvl << ": " << nodeCounter << " nodes. " << "(" << percent/100 << "." << percent%100 << "%)" << std::endl;

        // Move down one level.
        lvlPtr = lvlPtr -> down;        
    }
}


//-----------------------------------------------------------------------------------
// Private Members

template<class myType>
int skipList<myType>::coinFlip() const{
    return rand() % 2;
}

//-----------------------------------------------------------------------------------

// Add a top layer to the skip list by creating a new node on top of the head and
// moving head up one level.
template<class myType>
void skipList<myType>::addLayer(){

    // Create new top sentinel nodes.
    nodeType<myType> *newHead = new nodeType<myType>;
    nodeType<myType> *newTail = new nodeType<myType>;
    newHead -> isSent = -1;
    newTail -> isSent = 1;


    // Connect previous sentinel nodes to new sentinel nodes.
    head -> up = newHead;
    newHead -> down = head;
    head = newHead;

    tail -> up = newTail;
    newTail -> down = tail;
    tail = newTail;

    // Connect new sentinel nodes to each other.
    newHead -> right = tail;
    newTail -> left = head;
    
    height++;
}

//-----------------------------------------------------------------------------------

template<class myType>
nodeType<myType>* skipList<myType>::findEntry(myType k) const{

    // Node used to traverse thru the list.
    nodeType<myType> *curr = head;

    // Loop until the entry point is found.
    while(true){


        // Move right until tail is reached or a larger value is found.
        while(curr -> right -> isSent != 1 && curr -> right -> keyValue <= k){
            curr = curr -> right;

        } // end while()

        // Move down when cannot move right anymore. Do not move below base list.
        if(curr -> down != nullptr){
            curr = curr -> down;
        }
        // Break if base list is reached.
        else{
            break;
        }

    } // end while()

    return curr;

}

//-----------------------------------------------------------------------------------

template<class myType>
bool skipList<myType>::insert(myType item, nodeType<myType> *p){

    nodeType<myType> *q = new nodeType<myType>;
    q -> keyValue = item;
    q -> count++;

    unsigned int towerHeight = 0;


    // Insert q after p
    q -> left = p;
    q -> right = p -> right;
    p -> right -> left = q;
    p -> right = q;


    while(coinFlip() == 1){

        p = q;

        if(towerHeight >= height){
            addLayer();
        }

        // Find tower to the left.
        while(p -> up == nullptr)
            p = p -> left;
        
        // Move p up the tower.
        p = p -> up;

        nodeType<myType> *newTower = new nodeType<myType>;
        newTower -> keyValue = item;

        // Link new tower with other nodes.
        newTower -> left = p;
        newTower -> right = p -> right;
        newTower -> down = q;

        // Link other nodes to newTower
        p -> right -> left = newTower;
        p -> right = newTower;
        q -> up = newTower;

        // Move q up to set up for another iteration.
        q = q -> up;

        towerHeight++;
    }
    nodeCount++;
    totalCount++;

    return true;
}

//-----------------------------------------------------------------------------------

#endif