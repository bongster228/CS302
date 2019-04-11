#include <string>
#include "skipList.h"
using namespace std;

int main(){

    skipList<int> sk;

    for(int i = 0; i < 20; ++i){
        sk.insert(i);
    }

    sk.insert(4);
    sk.insert(4);




   sk.printSkipList();

    return 0;
}