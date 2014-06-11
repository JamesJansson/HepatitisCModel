
#include "TESTcsvread.h"
#include "TESTEventVector.h"
#include "TESTSimpleMatrix.h"
//#include "Matrix.h"




void TESTFunctions(void)
{
    //TESTSimpleMatrixIndices();
    TESTSimpleMatrixSetAll();


    TESTSimpleMatrixLinearIndexAccess();

    TESTSimpleMatrixApplyFunctionPointer();

    TESTSimpleMatrixApplyMultiDimension();

    //TESTDimensionsCompatible();

    TESTSimpleMatrixOverloading();

    //TESTMatrixh();

    TESTIndexOverloading();


    //TESTcsvreadstring();
    //TESTCSVGetInt();
    //EVRangeTestMultiple();
    //EVSetSomeEvents();
    //EVSpeedTest();

}


