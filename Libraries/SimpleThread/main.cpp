#include <iostream>
#include <thread>
using namespace std;

//inspired by: http://stackoverflow.com/questions/11352249/memory-sharing-between-c-threads

class Obj {
public:
    int x;
    Obj(){x = 0;}
};

int main() {
    Obj stackObj;
    Obj *heapObj = new Obj();
    cout<<"Starting value (stackObj): "<< stackObj.x<<endl;
    cout<<"Starting value (heapObj): "<< heapObj->x<<endl;
    thread t([&]{
        stackObj.x++;
        heapObj->x++;
    });
    t.join();

    cout<<"Starting value (stack): "<< stackObj.x<<endl;
    cout<<"Starting value (heapObj): "<< heapObj->x<<endl;

    return 0;
}
