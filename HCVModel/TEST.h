
#include "TESTcsvread.h"
#include "TESTEventVector.h"
#include "TESTSimpleMatrix.h"





void TESTFunctions(void)
{
    //TESTSimpleMatrixIndices();
    TESTSimpleMatrixSetAll();

    vector<int> a;
    a=TESTVector();

    cout<<"Got to the creation of this simple matrix"<<endl;
    SimpleMatrix<int> b;
    int val=1;
    b=TESTSimpleMatrixReturn(val);
    b.TestDisplayAll();

    SimpleMatrix<float> c;
    float val2=1;
    c=TESTSimpleMatrixReturn2(val2);
    //cout<<c.Value(0)<<endl;//NOTE: THIS CURRENTLY DOES NOT WORK FOR 1-D MATRICES
    c.TestDisplayAll();

    //SimpleMatrix<string> c;
    //c=TESTSimpleMatrixReturn();

    //TESTcsvreadstring();
    //TESTCSVGetInt();
    //EVRangeTestMultiple();
    //EVSetSomeEvents();
    //EVSpeedTest();

}


