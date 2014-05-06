#include <iostream>


using namespace std;

int Parameters[10];
int Output[10];




struct ParameterStruct
{
 int x;
};

struct StorageStruct
{
 int y;
};


void RunASim(ParameterStruct Parameter, StorageStruct Output)
{
    cout << "Running parameter yep" << Parameter.x << endl;

};


#include "Simthread.h"





int main()
{
    cout << "Hello world!" << endl;

    //ThreadSim(RunASim, 10, Parameters, Output);
    //ThreadSim(&RunASim, 10);

    ParameterStruct A[10];

    for (int i=1; i<10; i++){
        A[i].x=i*2;
    }


    StorageStruct B[10];

    ThreadSim(RunASim, 10, A, B);
    //thread t1(RunASim, A[1], B[1]);

    //t1.join();

    return 0;
}
