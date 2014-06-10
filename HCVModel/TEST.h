
#include "TESTcsvread.h"
#include "TESTEventVector.h"
#include "TESTSimpleMatrix.h"





void TESTFunctions(void)
{
    //TESTSimpleMatrixIndices();
    TESTSimpleMatrixSetAll();


    TESTSimpleMatrixLinearIndexAccess();

    TESTSimpleMatrixApplyFunctionPointer();

    TESTSimpleMatrixApplyMultiDimension();

    //TESTDimensionsCompatible();

    TESTSimpleMatrixOverloading();

    //TESTcsvreadstring();
    //TESTCSVGetInt();
    //EVRangeTestMultiple();
    //EVSetSomeEvents();
    //EVSpeedTest();

}


