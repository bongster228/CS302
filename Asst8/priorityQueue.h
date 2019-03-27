#include <string>

template <class myType>
class priorityQueue {

public:

    priorityQueue(int heapSize = 1000);         // Initialize the binary heap to at least 1000.
    ~priorityQueue();

    int entries() const;                        // Return the total count of elements in the heap.

    void insert(const myType, const int);       // Insert an emtry into the binary heap. If the count of heap
                                                // entries exceeds the heap size, the heap must be expanded via
                                                // private resize(). The heap properties must be maintained via 
                                                // private reheapUp(). The count should be updated.

    bool deleteMin(myType &, int &);            // Should remove the minimum entry from the heap. The heap properties
                                                // must be maintained via private reheapDown(). The count should be
                                                // updated. If the heap is alraedy empty, function should return false.
                                                // Otherwise return the minimum priority info via ref and return true.

    bool isEmtpy() const;                       // Return true if there are not elements inthe heap and flase otherwise.

    void printHeap() const;                     // Print the courrent heap in the level order with a blank line between
                                                // each level. 

    bool readData(const std::string);           // Read data form the passed file. The file format will be <dataItem> and
                                                // then <priority>. If the fir cannot be opned or read, then return false.
                                                // If file can be read, data should be palced into the heap in the order
                                                // read, then buildHeap() is called and return true.


private:

    struct heapNode{
        int priority;
        myType name;
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
