#include <mutex>
#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include <string.h>
using namespace std;

static unsigned long long MIN_THREAD_COUNT = 1;
static unsigned long long MAX_THREAD_COUNT = 64;
static unsigned long long MIN_LIMIT = 10;
static unsigned long long MAX_LIMIT = 100000000000;
static unsigned long long PAL_STEP = 10000;

bool getArguments(int, char*[], unsigned long long&, unsigned long long&);

int main(int argc, char *argv[]){

    unsigned long long chosenThreadCnt = 0;
    unsigned long long chosenLimit = 0;

    if(!getArguments(argc, argv, chosenThreadCnt, chosenLimit))
        exit(1);

    cout << "thread count: " << chosenThreadCnt << endl;
    cout << "limit count: " << chosenLimit << endl;
    

    

    return 0;
}

// Looks at the main arugments passed in and check them for validity.
bool getArguments(int argc, char *argv[], unsigned long long &threadCnt, unsigned long long &limitVal){

    if(argc == 1){
        cout << "Usage: ./palNums -t <threadCount> -l <limitValue>" << endl;
        return false;
    }

    if(argc != 5){
        cout << "Invalid number of arguments" << endl;
        return false;
    }

    cout << argv[1] << endl;

    if(argv[1] != "-t"){
        cout << "missing -t(thread) indicator" << endl;
        return false;
    }

    // Convert the string value into unsigned long long
    string::size_type tsz = 0;
    threadCnt = stoull(argv[2], &tsz, 10);

    if (threadCnt < MIN_THREAD_COUNT || threadCnt > MAX_THREAD_COUNT){
        cout << "invalid thread count (" << threadCnt << ")" << endl;
        return false;
    }

    if(argv[3] != "-l"){
        cout << "missing -l(limit) indicator" << endl;
        return false;
    }

    // Convert the string value into unsinged long long
    string::size_type lsz = 0;
    limitVal = stoull(argv[4], &lsz, 10);

    if(limitVal  < MIN_LIMIT || limitVal > MAX_LIMIT){
        cout << "invalid number limit (" << limitVal << ")" << endl;
        return false;
    }

    return true;
}