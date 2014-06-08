

#include "SimpleMatrix.h"

void TESTSimpleMatrixIndices(void)
{
    SimpleMatrix<int> A(2,3,4);
    A.TestConstructor();
    A.TestIndexingFunctions();

    vector<int> TestingIndex;
    TestingIndex.push_back(1); TestingIndex.push_back(0); TestingIndex.push_back(2);
    A.TestIndexingFunctions(TestingIndex);

    for (int k=0; k<4; k++)
    {
        for (int j=0; j<3; j++)
        {
            for (int i=0; i<2; i++)
            {
                TestingIndex.clear();
                TestingIndex.push_back(i); TestingIndex.push_back(j); TestingIndex.push_back(k);
                A.TestIndexingFunctions(TestingIndex);
            }
        }
    }

    TestingIndex.clear();
    //TestingIndex.push_back(1); TestingIndex.push_back(1); TestingIndex.push_back(1); TestingIndex.push_back(1);//wrong size
    //TestingIndex.push_back(-1); TestingIndex.push_back(1); TestingIndex.push_back(1);//negative
    //TestingIndex.push_back(2); TestingIndex.push_back(1); TestingIndex.push_back(1);//too big
    //TestingIndex.push_back(1); TestingIndex.push_back(4); TestingIndex.push_back(1);//too big
    TestingIndex.push_back(1); TestingIndex.push_back(1); TestingIndex.push_back(1);
    A.TestIndexingFunctions(TestingIndex);


    SimpleMatrix<int> B(5);
    B.TestConstructor();

}


void TESTSimpleMatrixSetAll(void)
{
    SimpleMatrix<int> A(2,3,4);
    A.TestDisplayAll();
    A.SetAll(3);
    A.TestDisplayAll();

    vector<int> TestingIndex;
    TestingIndex.push_back(0); TestingIndex.push_back(0); TestingIndex.push_back(0);

    A.Set(TestingIndex, 5);
    A.TestDisplayAll();

    TestingIndex[0]=1; TestingIndex[1]=0; TestingIndex[2]=2;
    A.Set(TestingIndex, 5);
    A.TestDisplayAll();
}





























void simpleprintf(const char *s)
{
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                //throw std::runtime_error("invalid format string: missing arguments");
            }
        }
        std::cout << "2: here"<<endl;
        std::cout << *s++;
    }
}

template<typename T, typename... Args>
void simpleprintf(const char *s, T value, Args... args)
{
    std::cout << "3: here"<<endl;
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                std::cout << value << "1: here"<<endl;
                simpleprintf(s + 1, args...); // call even when *s == 0 to detect extra arguments
                return;
            }
        }
        std::cout << *s++;
    }
    //throw std::logic_error("extra arguments provided to simpleprintf");
}



    int NumArgs; //should be set to zero when using CountArgs
    template <typename CountTemplateType>
    int CountArgs(CountTemplateType t)
    {
        NumArgs++;
        cout<<"End: "<<NumArgs<<endl;
        return NumArgs;
    }
    template<typename CountTemplateType, typename... Args>
    int CountArgs(CountTemplateType t, Args... args)
    {
        NumArgs++;
        cout<<"Splitter: "<<NumArgs<<endl;
        return CountArgs(args...);
    }

template< typename... Args>
void ProxyCount(Args... args)
{
    NumArgs=0;
    CountArgs(args...);
}




    int CountIntArgs(int t)
    {
        NumArgs++;
        cout<<"End: "<<NumArgs<<": "<< t <<endl;
        return NumArgs;
    }
    template<typename... Args>
    int CountIntArgs(int t, Args... args)
    {
        NumArgs++;
        cout<<"Splitter: "<<NumArgs<<": "<< t <<endl;
        return CountIntArgs(args...);
    }




void TESTSimpleMatrixOld(void)
{
    /*cout<<"started simplepf"<<endl;

    simpleprintf("This % then % and again", "A1", "B2", "C3", "D4");
    cout<<"end simplepf"<<endl;
    cout<<"end simplepf"<<endl;

    NumArgs=0;
    CountArgs(3, 4, 5);

    NumArgs=0;
    CountIntArgs(3, 4, 5);

    NumArgs=0;
    float sss=3.5;
    CountIntArgs(sss, 4, 5);*/

    //string AA, BB, CC;
    //NumArgs=0;
    //CountIntArgs(AA, BB, CC); doesn't work, as planned


    SimpleMatrix<int> A(2,3,4);
    A.TestConstructor();
    A.TestIndexingFunctions();


    SimpleMatrix<int> B(5);
    B.TestConstructor();
    //A.TestConstructor();


    //ProxyCount(3, 4, 5);


    /*SimpleMatrix<int> A(2,3,4);
    A.TestConstructor();

    SimpleMatrix<int> B(5,4,5, 6, 7);
    B.TestConstructor();
    cout<<endl;

    A.NumArgs=0;
    A.CountArgs((int)12, (int)23, (int)34);*/
//    std::cout<<<<endl;

    //TESTcsvreadstring();
    //TESTCSVGetInt();
    //EVRangeTestMultiple();
    //EVSetSomeEvents();
    //EVSpeedTest();

}


