
#include "TESTcsvread.h"
#include "TESTEventVector.h"
#include "SimpleMatrix.h"

void TESTFunctions(void)
{
    SimpleMatrix<int> A(2,3,4);
    A.TestConstructor();

    SimpleMatrix<int> B(5,4,5, 6, 7);
    B.TestConstructor();
//    std::cout<<<<endl;

    //TESTcsvreadstring();
    //TESTCSVGetInt();
    //EVRangeTestMultiple();
    //EVSetSomeEvents();
    //EVSpeedTest();

}


