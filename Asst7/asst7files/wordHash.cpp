#include <iostream>
#include "wordHash.h"
using namespace std;

//----------------------------------------------------------------------------------

wordHash::wordHash(){

    // Size and count Variables
    hashSize = initialHashSize;
    reSizeCount = 0;
    collisionCount = 0;
    uniqueWordCount = 0;

    wordList = new string[hashSize];
    wordCounts = new unsigned int[hashSize];


    // Initialize hash table of strings
    for(unsigned int i = 0; i < hashSize; ++i)
        wordList[i] = "";

    // Initialize the wordCounts hash table
    for(unsigned int j = 0; j < hashSize; ++j)
        wordCounts[j] = 0;
}

//----------------------------------------------------------------------------------

wordHash::~wordHash(){
    delete[] wordList;
    delete[] wordCounts;
}

//----------------------------------------------------------------------------------

unsigned int wordHash::hash(string word) const{
    
    unsigned int hash = 0;

    for(unsigned int i = 0; i < word.length(); ++i){
        hash += static_cast<int>(word[i]);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

//----------------------------------------------------------------------------------

void wordHash::insert(string word){


    // Insert if the word is not in the hash table. 
    // Just return if the word is already in the hash table.
    if(!incCount(word)){
        uniqueWordCount++;      // Insert only occurs when the word is not a duplicate.
        insert(word, 1);
    }
    
    return;
}

//----------------------------------------------------------------------------------

void wordHash::insert(string word, unsigned int count){

    // Check for rehashing condition.
    double currLoadFactor = static_cast<double>(uniqueWordCount) / static_cast<double>(hashSize);
    if(currLoadFactor > loadFactor) rehash();

    cout << "Load Factor: " << currLoadFactor << endl;

    // Hash the word.
    unsigned int hashIndex = hash(word) % hashSize;

    // Used for quadratic probing.
    unsigned int newHashIndex = hashIndex;
    int probe = 0;

    while(true){

        // If an empty spot is found, insert the word and count.
        if(wordList[newHashIndex] == ""){
            wordList[newHashIndex] = word;
            wordCounts[newHashIndex] = count;
            break;
        }

        // Start probing for empty location.
        if(wordList[newHashIndex] != ""){
            collisionCount++;
            probe++;
            newHashIndex = next(hashIndex, probe);
        }
        
    }// end while()

}

//----------------------------------------------------------------------------------

bool wordHash::incCount(string word){

    // Get the hash value of the word.
    unsigned int hashIndex = hash(word) % hashSize;

    // Use newHashIndx to probe for a new index.
    unsigned int newHashIndex = hashIndex;
    int probe = 0;


    while(wordList[newHashIndex] != ""){

    // If the word exists at the hash value increment count and return true.
    if(wordList[newHashIndex] == word){
        wordCounts[newHashIndex]++;
        return true;
    }

    // Probe for the word quadratically, the position at which the probing starts
    // should stay the same.
    ++probe;
    newHashIndex = next(hashIndex, probe);

    } // end while()

    // Word was not found.
    return false;

}

//----------------------------------------------------------------------------------

// The original hash value(first located index) and the counter will be passed in
// so that the function can be called multiple times so that it can probe further.
unsigned int wordHash::next(unsigned int position, unsigned int counter) const{
    
    unsigned int newHash = 0;

    newHash = (position + (counter * counter)) % hashSize;

    return newHash;
}

//----------------------------------------------------------------------------------

void wordHash::rehash(){

    if(reSizeCount > 12){
        cout << "Resizing has exceeded the limit" << endl;
        return;
    }

    reSizeCount++;

    static const unsigned int hashSizes[12] = {
    30011, 60013, 120017, 240089, 480043, 960017, 1920013,
    3840037, 7680103, 30720299, 15360161, 61440629
    };


    // Store the memory location of previous array and create a new bigger array.
    string *prvWordList = wordList;
    unsigned int *prvWordCounts = wordCounts;


    wordList = new string[hashSizes[reSizeCount]];
    wordCounts = new unsigned int[hashSizes[reSizeCount]];


    // Initialize new hash table.
    for(unsigned int i = 0; i < hashSizes[reSizeCount]; ++i)
        wordList[i] = "";


    // Extract all entries from the old hash table and insert them into new table.
    for(unsigned int i = 0; i < hashSize; ++i){
        if(prvWordList[i] != "")
            insert(prvWordList[i], prvWordCounts[i]);
    }

    // Update to new hash table size.
    hashSize = hashSizes[reSizeCount];

    delete[] prvWordList;
    delete[] prvWordCounts;
}

//----------------------------------------------------------------------------------

void wordHash::printHash() const{

    for(unsigned int i = 0; i < hashSize; ++i){
        if(wordList[i] != "")
            cout << wordList[i] << " " << wordCounts[i] << endl;
    }
}

//----------------------------------------------------------------------------------

unsigned int wordHash::getUniqueWordCount() const{
    return uniqueWordCount;
}

//----------------------------------------------------------------------------------

unsigned int wordHash::getWordCount(string word) const{

    unsigned int hashIndex = hash(word) % hashSize;

    // Used for probing for checking in case of collision.
    unsigned int probeIndex = hashIndex;
    int probeCntr = 0;

    while(wordList[probeIndex] != ""){

        // Return the count if a match is found.
        if(wordList[probeIndex] == word){
            return wordCounts[probeIndex];
        }

        probeCntr++;
        probeIndex = next(hashIndex, probeCntr);
    }

    // Word is not found in the hash table.
    return 0;
}

//----------------------------------------------------------------------------------

void wordHash::getMaxNode(unsigned int &count, string &word) const{

    unsigned int maxNodeIndex = 0;

    // Look through every element in the wordCounts and find the
    // index value of the greatest word count.
    for(int i = 0; i < hashSize; ++i){
        if(wordCounts[maxNodeIndex] < wordCounts[i])
            maxNodeIndex = i;
    }

    // Return the values via reference.
    word = wordList[maxNodeIndex];
    count = wordCounts[maxNodeIndex];
}

//----------------------------------------------------------------------------------