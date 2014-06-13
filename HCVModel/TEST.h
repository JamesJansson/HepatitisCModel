
#include "TESTcsvread.h"
#include "TESTEventVector.h"
//#include "TESTSimpleMatrix.h"

//#include "TESTSimpleMatrix2.h"



#include "TESTSimple2DMatrix.h"
#include <time.h>
//#include "Matrix.h"




void TESTFunctions(void)
{
    vector<vector <int>> A;

    vector <int> thisvector;
    A.resize(5);
    for (int i=0; i<5; i++)
    {
        A[i].resize(4);
    }


    A[1][3]=3;

    TESTSimple2DMatrix();




    //TESTDimensionsCompatible();
    //TESTSimpleMatrixGeneral();

    //TESTSimpleMatrixOverload();

    //TESTSimpleMatrixHeap();






    //TESTSimpleMatrixIndices();
    //TESTSimpleMatrixSetAll();
    //TESTSimpleMatrixLinearIndexAccess();
    //TESTSimpleMatrixApplyFunctionPointer();
    //TESTSimpleMatrixApplyMultiDimension();

    //TESTDimensionsCompatible();

    //TESTSimpleMatrixOverloading();

    //TESTMatrixh();

    //TESTIndexOverloading();


    //TESTcsvreadstring();
    //TESTCSVGetInt();
    //EVRangeTestMultiple();
    //EVSetSomeEvents();
    //EVSpeedTest();

}


