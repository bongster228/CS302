#include "wordCount.h"
#include <iostream>
#include <fstream>
using namespace std;

//--------------------------------------------------------------------------
// Constructor
wordCount::wordCount(): totalWordCount{}, docFileName{}{}

//--------------------------------------------------------------------------

bool wordCount::getArguments(int argc, char *argv[], string &docName, bool &printOption){

    // Prints if no argument is entered.
    if(argc == 1){
        cout << "Usage: ./concordance -i <documentName> [-p]" << endl;
        return false;
    }

    // Check for invalid arguments.
    if(argc < 3 || argc > 4){
        cout << "Error, command line arguments invalid." << endl;
        return false;
    }

    if(string(argv[1]) != "-i"){
        cout << "Error, missing -i." << endl;
        return false;
    }

    if(string(argv[2]) == ""){
        cout << "Error, missing document name." << endl;
        return false;
    }

    // Store the document name.
    docName = string(argv[2]);
    docFileName = docName;
    
    // Set print option to true if -p is passed in.
    if(argc == 4)
        if(string(argv[3]) == "-p") printOption = true;

    return true;
}

//--------------------------------------------------------------------------

void wordCount::showDocumentFileName() const{
    cout << "Document File Name: " << docFileName << endl;
}

//--------------------------------------------------------------------------

bool wordCount::readDocument(const string docName){

    // Check if the file can be opened.
    fstream document;
    document.open(docName);
    if(!document.is_open()){
        cout << "File could not be opened." << endl;
        return false;
    } // end if()

    string word = "";

    while(document >> word){

    // Validate the word or return empty string if the word is invalid.
    word = wordCheck(word);

    // Insert only if the word is valid.
    if(word != ""){
        insert(word);
        totalWordCount++;
    }

    

    } // end while()

    document.close();

    return true;

} // end readDocument()

//--------------------------------------------------------------------------

string wordCount::wordCheck(string chkedWord){


    // Erase non alpha in the beginning of the string.
    for(unsigned int i = 0; i < chkedWord.size(); ++i){
        if(isalpha(chkedWord[i])){
            chkedWord.erase(0,i);
            break;
        }
    }

    // Erase the non alpha at the end of the string.
    for(int j = chkedWord.size(); j > 0; --j){
        if(isalpha(chkedWord[j-1]))     // Break out of the loop when an alpha in the string is reached.
            break;
        
       if(!isalpha(chkedWord[j])){      // Pop each non alpha characters at the end of the string.
           chkedWord.pop_back();
        }
    }

    // Check for non alpha in the middle of the string and convert to lowercase.
    for(unsigned int k = 0; k < chkedWord.size(); ++k){
        if(!isalpha(chkedWord[k])) return "";
        chkedWord[k] = tolower(chkedWord[k]);
    }

    return chkedWord;

} // end wordCheck()

//--------------------------------------------------------------------------

void wordCount::showTotalWordCount() const{
    
    cout << "Total Word Count: " << totalWordCount << endl;

}

//--------------------------------------------------------------------------

void wordCount::showUniqueWordCount() const{

    cout << "Unique Word Count: " << getUniqueWordCount() << endl;

}

//--------------------------------------------------------------------------

void wordCount::showStats() const{

    showHashStats();

}

//--------------------------------------------------------------------------

void wordCount::getMaxWord(unsigned int &count, string &word){

    getMaxNode(count, word);

}

//--------------------------------------------------------------------------

void wordCount::printWordCounts() const{

    printHash();

}

//--------------------------------------------------------------------------

unsigned int wordCount::getWordCount(string word) const{

    // Convert the string to lowercase.
    for(unsigned int i = 0; i < word.length(); ++i)
        word[i] = tolower(word[i]);

    return getWordCount(word);

}

