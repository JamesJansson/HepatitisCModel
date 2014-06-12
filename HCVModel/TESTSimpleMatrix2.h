
#include <math.h>

double Add1(double A)
{
    return A++;
}


void TESTSimpleMatrixOverload(void)
{
    SimpleMatrix<double> A(2,3,4);

    vector<int> TestingIndex;
    TestingIndex.push_back(1); TestingIndex.push_back(0); TestingIndex.push_back(2);
    A.DisplayInfo();

    double StoreCount=-3.2;
    for (int k=0; k<4; k++)
    {
        for (int j=0; j<3; j++)
        {
            for (int i=0; i<2; i++)
            {
                StoreCount++;

                TestingIndex.clear();
                TestingIndex.push_back(i); TestingIndex.push_back(j); TestingIndex.push_back(k);
                A(TestingIndex)=StoreCount;
            }
        }
    }

    cout<<"Following set up..."<<endl;
    A.Display();

}










void TESTSimpleMatrixGeneral(void)
{
    SimpleMatrix<double> A(2,3,4);

    vector<int> TestingIndex;
    TestingIndex.push_back(1); TestingIndex.push_back(0); TestingIndex.push_back(2);
    A.DisplayInfo();

    double StoreCount=-3.2;
    for (int k=0; k<4; k++)
    {
        for (int j=0; j<3; j++)
        {
            for (int i=0; i<2; i++)
            {
                StoreCount++;

                TestingIndex.clear();
                TestingIndex.push_back(i); TestingIndex.push_back(j); TestingIndex.push_back(k);
                A(TestingIndex)=StoreCount;
            }
        }
    }

    cout<<"Following set up..."<<endl;
    A.Display();
    SimpleMatrix<double> B;
    B=Apply(Add1, A);
    //B=Apply(sin, A);
    cout<<"After applying add 1 to B..."<<endl;
    B.Display();


    SimpleMatrix<double> C;
    C=A;
    cout<<"After applying add 1 to C..."<<endl;
    C(5)=1000;
    C.Display();

    cout<<"Displaying item 4: "<<C(3)<<endl;
}






void TESTDimensionsCompatible(void)
{
    //Tested, works
    cout<<"Starting DimensionsCompatible test"<<endl;
    SimpleMatrix<double> A(2,3,4);
    SimpleMatrix<double> B(2,3,4);
    SimpleMatrix<double> C(2,1,4);
    if (A.DimensionsCompatible(B))
        cout<<"Dimensions compatible"<<endl;
    else
        cout<<"Dimensions NOT compatible"<<endl;

    if (A.DimensionsCompatible(C))
        cout<<"Dimensions compatible"<<endl;
    else
        cout<<"Dimensions NOT compatible"<<endl;



}



