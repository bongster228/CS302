#include <string>
#include <iostream>
#include <fstream>

template <class myType>
class priorityQueue {

public:

    priorityQueue(int size = 1000);             // Initialize the binary heap to at least 1000.
    ~priorityQueue();

    int entries() const;                        // Return the total count of elements in the heap.

    void insert(const myType, const int);       // Insert an entry into the binary heap. If the count of heap
                                                // entries exceeds the heap size, the heap must be expanded via
                                                // private resize(). The heap properties must be maintained via 
                                                // private reheapUp(). The count should be updated.

    bool deleteMin(myType &, int &);            // Should remove the minimum entry from the heap. The heap properties
                                                // must be maintained via private reheapDown(). The count should be
                                                // updated. If the heap is alraedy empty, function should return false.
                                                // Otherwise return the minimum priority info via ref and return true.

    bool isEmpty() const;                       // Return true if there are not elements inthe heap and false otherwise.

    void printHeap() const;                     // Print the courrent heap in the level order with a blank line between
                                                // each level. 

    bool readData(const std::string);           // Read data form the passed file. The file format will be <dataItem> and
                                                // then <priority>. If the file cannot be opened or read, then return false.
                                                // If file can be read, data should be palced into the heap in the order
                                                // read, then buildHeap() is called and return true.

    void changePriority(myType, double);

    bool itemInHeap(myType);


private:

    struct heapNode{
        int priority = 0;
        myType name = {};
    };

    int count;
    int heapSize;
    heapNode *myHeap;

    void reheapUp(int);                          // Recursively ensure the heap order property is maintained. Starts at 
                                                 // tree leaf and works up to the root. Must be recusive.

    void reheapDown(int);                        // Recursively ensure the heap order property is maintained. Starts at tree
                                                 // root and works down to the applicable leaf.

    void buildHeap();                           // Should update the heap to apply the heap properties.

    void resize();                              // Create a new heap array twice the size of the existing heap, copy all
                                                // entries form the current heap into new heap, and delete old heap.
                                                // Update heapSize accordingly.

};


//----------------------------------------------------------------------------------------------------------------------
// Public Members

template<class myType>
priorityQueue<myType>::priorityQueue(int size){

    heapSize = size;
    count = 0;
                          
    myHeap = new heapNode[heapSize];        // Allocate memory for heap array.

}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
priorityQueue<myType>::~priorityQueue(){

    delete[] myHeap;
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
int priorityQueue<myType>::entries() const{
    return count;
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
void priorityQueue<myType>::insert(const myType item, const int priorityVal){

    if(count == heapSize - 1){
        resize();
    }

    // Create new node with the parameters given.


    count++;

    // Insert the new node in the last spot
    myHeap[count].name = item;
    myHeap[count].priority = priorityVal;
    

    reheapUp(count);

    return;
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
bool priorityQueue<myType>::deleteMin(myType &minEntry, int &minPriority){

    if(isEmpty()) return false;

    minEntry = myHeap[1].name;
    minPriority = myHeap[1].priority;


    // Place the last element in the heap in the root.
    myHeap[1] = myHeap[count];

    // Empty out the last spot and reduce count.
    myHeap[count].name = {};
    myHeap[count].priority = 0;
    count--;


    // reheapDown from the first index, which is the root.
    reheapDown(1);


    return true;
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
bool priorityQueue<myType>::isEmpty() const{

    if(count == 0) return true;
    else return false;
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
void priorityQueue<myType>::printHeap() const{

    for(int i = 1; i <= count; ++i){
        std::cout << myHeap[i].name << "  " << myHeap[i].priority << std::endl;
    }
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
bool priorityQueue<myType>::readData(const std::string fileName){

    std::fstream file;

    file.open(fileName);
    if(!file.is_open()) return false;

    std::string dataItem;
    int dataPriority;


    while(file >> dataItem >> dataPriority){

        count++;
        if(count == heapSize - 1) resize();
        
        myHeap[count].name = dataItem;
        myHeap[count].priority = dataPriority;
        
    }

    buildHeap();

    return true;
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
void priorityQueue<myType>::changePriority(myType vertex, double priorityVal){

    // Find the vertex node inside the heap array.
    for(int i = 1; i < heapSize; ++i){

        // If found change the priority and reheapUp. Only reheapUp because 
        // the priority will only be decreaseing if change is made.
        if(myHeap[i].name == vertex){
            myHeap[i].priority = priorityVal;
            reheapUp(i);
        }

    }// end for()
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
bool priorityQueue<myType>::itemInHeap(myType item){

    for(int i = 0; i < heapSize; ++i){

        if(myHeap[i].name == item) return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------
// Private Members

template<class myType>
void priorityQueue<myType>::reheapUp(int index){

    int parent = index / 2;
    heapNode temp;

    // If current index's has lower priority than parent, swap parent with current node.
    if(myHeap[index].priority < myHeap[parent].priority){
        
        temp = myHeap[index];
        
        // Swap
        myHeap[index] = myHeap[parent];
        myHeap[parent] = temp;


        // Repeat until parent node has min priority over all its children.
        reheapUp(parent);
    }

    // Base case. Return if parent node already has min priority.
    return;
}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
void priorityQueue<myType>::reheapDown(int index){


    int leftChild = index * 2;
    int rightChild = index * 2 + 1;
    int smallerIndex = index;               // Will have the index of the lowest priority node.
    heapNode temp;

    // Base case.
    if(index > count) return;

    // Compare current index with left child.
    if(leftChild <= count && myHeap[index].priority > myHeap[leftChild].priority){
        smallerIndex = leftChild;
    }
    

    // Compare with the right child.
    if(rightChild <= count && myHeap[smallerIndex].priority > myHeap[rightChild].priority){
        smallerIndex = rightChild;
    }


    // Swap the nodes if children nodes have lower priority. 
    if(smallerIndex != index){

        temp = myHeap[index];
        myHeap[index] = myHeap[smallerIndex];
        myHeap[smallerIndex] = temp;


        // Recurisively repeat the process until current node has lower priority than
        // all of its children.
        reheapDown(smallerIndex);
    }

    // Base case. Current node already has the lowest priority than all of its children.
    return;


}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
void priorityQueue<myType>::buildHeap(){

    for(int i = count / 2; i >= 1; --i){
        reheapDown(i);
    }

}

//----------------------------------------------------------------------------------------------------------------------

template<class myType>
void priorityQueue<myType>::resize(){

    // Double the heapSize and store old heap in temp.
    heapSize *= 2;
    heapNode *temp = myHeap;

    // Create new heap
    myHeap = new heapNode[heapSize];

    // Deep copy heap
    for(int i = 1; i <= count; ++i){
        myHeap[i] = temp[i];
    }

    delete[] temp;
}