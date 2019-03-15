#include <iostream>
#include <string>
using namespace std;

struct LinkedList {
    string data;
    LinkedList *next;
};

struct HashTable {
    int size;               // The size of the table.
    LinkedList **table;     // The table of elements.
};

HashTable *createHashTable (int size){

    HashTable *newTable;

    if(size < 1) return nullptr;            // Invalid size for table.

    // Attempt to allocate memeory for the table structure.
    if((newTable = malloc(sizeof(hash_value_t))) == NULL)
        return nullptr;

    
}
