#include <string>
#include "skipList.h"
using namespace std;

int main(){

    skipList<int> sk;

    for(int i = 1; i < 50; ++i){
        sk.insert(i);
    }


    sk.insert(50);
    sk.insert(4);
    sk.insert(5);
    sk.insert(60);




   sk.printSkipList();
   sk.showSkipListStats();

    return 0;
}