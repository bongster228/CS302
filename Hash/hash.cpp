#include <iostream>
#include <string>
using namespace std;

class LinkedHashEntry {

private:

    int key;
    int value;
    LinkedHashEntry *next;

public:
    LinkedHashEntry(int key, int value){
        this -> key = key;
        this -> value = value;
        this -> next = NULL;
    }

    int getKey() {
        return key;
    }

    int getValue() {
        return value;
    }

    void setValue(int value) {
        this -> value = value;
    }

    LinkedHashEntry *getNext() {
        return next;
    }

    void setNext(LinkedHashEntry *next) {
        this -> next = next;
    }
};

const int TABLE_SIZE = 128;

class HashMap {

private:
    LinkedHashEntry **table;

public:
    HashMap() {
        table = new LinkedHashEntry*[TABLE_SIZE];       // Create and initialize hash table.
        for(int i = 0; i < TABLE_SIZE; ++i)
            table[i] = NULL;
    }

    int get(int key) {
        int hash = (key % TABLE_SIZE);
        if (table[hash] == NULL)
            return -1;
        else {
            LinkedHashEntry *entry = table[hash];
            while (entry != NULL && entry -> getKey() != key)
                entry = entry -> getNext();
            if (entry == NULL)
                return -1;
            else
                return entry -> getValue();
        }

};