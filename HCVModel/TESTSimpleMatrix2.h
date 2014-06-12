
#include <math.h>

double Add1(double A)
{
    //A++;
    return A++;
}
double Mult2(double A){return A*2;}

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
                StoreCount=(i+1)+(j+1)*10+(k+1)*100;
                TestingIndex[0]=i;
                TestingIndex[1]=j;
                TestingIndex[2]=k;
                A(TestingIndex)=StoreCount;
            }
        }
    }

    cout<<"Following set up..."<<endl;
    A.Display();

    SimpleMatrix<double> C;
    C=A;
    cout<<"Change one item of C ..."<<endl;
    C(5)=999;
    C.Display();

    cout<<"Displaying item 4: "<<C(3)<<endl;

    cout<<"After applying add1 to C..."<<endl;
    SimpleMatrix<double> D;
    D=Apply(Add1, C);
    cout<<"Note C should be the same..."<<endl;
    C.Display();
    cout<<"But D should be +1..."<<endl;
    D.Display();

    cout<<"Directly applying the functino to C changes C..."<<endl;
    C.Apply(Mult2);
    C.Display();


    cout<<"Breaking time..."<<endl;
    cout<<"A*2"<<endl;
    C=A*2;
    C.Display();
        cout<<"2*A"<<endl;
    C=A*2;
    C.Display();

    cout<<"Adding A and C=(A*2)"<<endl;
    D=C+A;
    D.Display();

    cout<<"Accessing illegal memory positions"<<endl;

    D(1)=0;
    D.Display();
    D(1, 1, 1)=0;
    D.Display();
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



