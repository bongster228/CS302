#include "priorityQueue.h"
using namespace std;


int main(){

    priorityQueue<string> myq;

    string name;
    int priority;


    myq.insert("a", 1);
    myq.insert("b", 0);
    myq.insert("c", 2);
    myq.insert("d", 0);
    myq.insert("e", 3);

    myq.printHeap();

    if(myq.deleteMin(name, priority)){
        cout << "name: " << "  " << "priority: " << priority << endl;
    }

    myq.printHeap();
}