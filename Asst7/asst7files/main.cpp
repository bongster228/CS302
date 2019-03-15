#include <iostream>
#include "wordHash.h"
using namespace std;

int main(){

    wordHash hash;

    hash.insert("hello");
    hash.insert("hello");
    hash.insert("hello");
    hash.insert("hello");
    hash.insert("byye");

    cout << "How many Hello: " << hash.getWordCount("hello") << endl;
    hash.printHash();

    return 0;

}