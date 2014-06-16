
#include <math.h>
#include <time.h>
#include <stdio.h>

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
    //D(1, 1)=0;
    //D(2, 1, 1)=0;
    //D.Display();


    D=D*D;
    D.Display();

    int MatrixSize=20;
    SimpleMatrix<double> E(MatrixSize, MatrixSize);
    SimpleMatrix<double> F(MatrixSize, MatrixSize);
    E.DisplayInfo();

    clock_t startTime;
    double secondsPassed;

    MatrixSize=2000;



    cout<<"Setting with loops and checks"<<endl;
    startTime=clock();
    E.Resize(MatrixSize, MatrixSize);
    for (int i=0; i<(MatrixSize); i++)
        for (int j=0; j<(MatrixSize); j++)
            E(i, j)=i+MatrixSize*j;

    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"    Milliseconds "<<secondsPassed<<endl;

    cout<<"Adding with loops and checks"<<endl;
    startTime=clock();
    for (int i=0; i<(MatrixSize*MatrixSize); i++)
        E(i)=E(i)+1;
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"    Milliseconds "<<secondsPassed<<endl;

    cout<<"Adding as a matrix"<<endl;
    startTime=clock();
    E=E+1;
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"    Milliseconds "<<secondsPassed<<endl;

    cout<<"Sin"<<endl;
    startTime=clock();
    E.Apply(sin);
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"    Milliseconds "<<secondsPassed<<endl;

    cout<<"Sin 2nd application"<<endl;
    startTime=clock();
    E.Apply(sin);
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"    Milliseconds "<<secondsPassed<<endl;

    cout<<"E times E"<<endl;
    startTime=clock();
    F=E*E;
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"    Milliseconds "<<secondsPassed<<endl;

    //matlab version of the above
//    MatrixSize=2000;
//disp('Setting with loops and checks');
//    tic
//        E=zeros(MatrixSize, MatrixSize);
//        for i=1:MatrixSize
//            for j=1:MatrixSize
//                E(i,j)=i+j*MatrixSize;
//            end
//        end
//        E=1:(MatrixSize*MatrixSize);
//    toc
//disp('Adding with loops and checks');
//    tic
//    for i=1:(MatrixSize*MatrixSize)
//        E(i)=E(i)+1;
//    end
//    toc
//disp('Adding as a matrix');
//    tic
//    E=E+1;
//    toc
//disp('Sin');
//    tic
//    E=sin(E);
//    toc
//disp('Sin 2nd application');
//    tic
//    E=sin(E);
//    toc
//disp('E times E');
//tic
//F=E.*E;
//toc


//matlab version of the above
//    MatrixSize=4000;
//disp('Setting with loops and checks');
//    tic
//        E=1:(MatrixSize*MatrixSize);
//    toc
//disp('Adding with loops and checks');
//    tic
//    for i=1:(MatrixSize*MatrixSize)
//        E(i)=E(i)+1;
//    end
//    toc
//disp('Adding as a matrix');
//    tic
//    E=E+1;
//    toc
//disp('Sin');
//    tic
//    E=sin(E);
//    toc
//disp('Sin 2nd application');
//    tic
//    E=sin(E);
//    toc
//disp('E times E');
//tic
//F=E.*E;
//toc

    cout<<"Setting with loops and checks"<<endl;
    startTime=clock();
    vector<double> VecOnly;
    VecOnly.resize(MatrixSize*MatrixSize);
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"Milliseconds "<<secondsPassed<<endl;

    startTime=clock();
    for (int i=0; i<(MatrixSize*MatrixSize); i++)
        VecOnly[i]=i;
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"Milliseconds "<<secondsPassed<<endl;




    char buffer;
    cin>>buffer;
}



SimpleMatrix<double> HeapSMA;
SimpleMatrix<double> HeapSMB;


void TESTSimpleMatrixHeap(void)
{
    int MatrixSize=10000;
    HeapSMA.Resize(MatrixSize, MatrixSize);

    clock_t startTime;
    double secondsPassed;

    startTime=clock();
    for (int i=0; i<(MatrixSize*MatrixSize); i++)
        HeapSMA(i)=i;

    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"Allocating values in a loop "<<secondsPassed<<endl;

    startTime=clock();
    HeapSMB=HeapSMA+HeapSMA;
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
    cout<<"Adding matrices "<<secondsPassed<<endl;


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



