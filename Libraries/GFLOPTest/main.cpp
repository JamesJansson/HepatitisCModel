#include <iostream>
#include <ctime>

#include <time.h>
using namespace std;

int main()
{

    cout<<"Gigaflop test"<<endl;
    clock_t startTime;
    double millisecondsPassed;
    float FloatOperand=0.9;
    int TotalLoops=250000000;
    float TotalCalculations, GFLOPS;


    startTime=clock();
    for (int j=1; j<TotalLoops; j++)
    {
        FloatOperand=(FloatOperand+ 1.1*(3.1 - FloatOperand))/2.1; //4 FLOP occur here, implying at 250000000 loops 1GFLOP
        //cout<<"    Result "<<FloatOperand<<"Count"<<j<<endl;
    }
    millisecondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);

    TotalCalculations=TotalLoops*4;
    GFLOPS=((TotalCalculations/millisecondsPassed)*1000)/1000000000;

    cout<<"    Milliseconds: "<<millisecondsPassed<<endl;
    cout<<"    Total calculations: "<<TotalCalculations<<endl;
    cout<<"    GFLOPS: "<<GFLOPS<<endl;
    //this result gives a theoretical 200 MFLOPS per core (1 000 000 000 FLOPS runs in 5000 ms)
    char buffer;
    cin>>buffer;

    return 0;

}
