
#include <math.h>
#include <time.h>
#include <stdio.h>

double Add1(double A)
{
    //A++;
    return A++;
}
//double Mult2(double A){return A*2;}

void TESTSimple2DMatrix(void)
{
    clock_t startTime;
    double secondsPassed;


    /// Constructors
//    SimpleMatrix(int xsize, int ysize);//alows a vector to be used to specify the dimensions of the matrix
//    SimpleMatrix(void);
//    SimpleMatrix(vector<int> dimensions);//alows a vector to be used to specify the dimensions of the matrix
//    void Resize(int xsize, int ysize);
//    void Resize(vector<int> dimensions);
//
    /// Dimensions
//    vector<int> dim(void);
//    int xsize(void);
//    int ysize(void);
//    template <typename OtherType>
//    bool DimensionsCompatible( SimpleMatrix<OtherType> Other);
//    template <typename OtherType>
//    void StopIfDimensionsIncompatible(SimpleMatrix<OtherType> Other);
//    // void StopIfDimensionsIncompatible( SimpleMatrix<OtherType> Other);
//    void SetAll(TemplateType SetValue);
//    SimpleMatrix<TemplateType> Transpose(void);
//
//
//
//
    /// Overloading, pointer and template functions
//    // Good tutorial on how this works: http://www.cprogramming.com/tutorial/operator_overloading.html
//    // Index overloading
//    // use () instead http://stackoverflow.com/questions/2533235/operator-c
    ///Getting values
//        TemplateType operator()(int i, int j)const{ return values[i][j];};
//
    ///Setting Values
//        TemplateType & operator()(int i, int j){ return values[i][j];};
//
//
    //Plus
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator+(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator+(const OtherType& Other);
    //Minus
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator-(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator-(const OtherType& Other);
//        //Unary minus
//        SimpleMatrix<TemplateType> operator-(void);
    //Times
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator*(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator*(const OtherType& Other);
    //Divide
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator/(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator/(const OtherType& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> DivideByMatrix(const OtherType& Other);
    //Modulus
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator%(const SimpleMatrix<OtherType>& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> operator%(const OtherType& Other);
//        template <typename OtherType>
//        SimpleMatrix<TemplateType> ModulusByMatrix(const OtherType& Other);
//

//    //Changes this matrix
//    void Apply(TemplateType (*FunctionPointer)(TemplateType));
//    //returns a new matrix
//    template <typename ReturnTemplateType>
//    friend SimpleMatrix<ReturnTemplateType> Apply(ReturnTemplateType (*FunctionPointer)(TemplateType), const SimpleMatrix<TemplateType> A);
//    //returns a new matrix, two input matrices
//    template <typename ReturnTemplateType>
//    friend SimpleMatrix<ReturnTemplateType> Apply(ReturnTemplateType (*FunctionPointer)(TemplateType, TemplateType), const SimpleMatrix<TemplateType> A, const SimpleMatrix<TemplateType> B);
//
//    //Display functions
//    void Display(void);
//    void DisplayInfo(void);










    int MatrixSize=4;
    SimpleMatrix<double> E(MatrixSize, MatrixSize);
    SimpleMatrix<double> F(MatrixSize, MatrixSize);
    E.DisplayInfo();

    //Construtors


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



//SimpleMatrix<double> HeapSMA;
//SimpleMatrix<double> HeapSMB;
//
//
//void TESTSimpleMatrixHeap(void)
//{
//    int MatrixSize=10000;
//    HeapSMA.Resize(MatrixSize, MatrixSize);
//
//    clock_t startTime;
//    double secondsPassed;
//
//    startTime=clock();
//    for (int i=0; i<(MatrixSize*MatrixSize); i++)
//        HeapSMA(i)=i;
//
//    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
//    cout<<"Allocating values in a loop "<<secondsPassed<<endl;
//
//    startTime=clock();
//    HeapSMB=HeapSMA+HeapSMA;
//    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/1000);
//    cout<<"Adding matrices "<<secondsPassed<<endl;
//
//
//}
//
//
//
//
//
//
//
//
//
//
//
//void TESTSimpleMatrixGeneral(void)
//{
//    SimpleMatrix<double> A(2,3,4);
//
//    vector<int> TestingIndex;
//    TestingIndex.push_back(1); TestingIndex.push_back(0); TestingIndex.push_back(2);
//    A.DisplayInfo();
//
//    double StoreCount=-3.2;
//    for (int k=0; k<4; k++)
//    {
//        for (int j=0; j<3; j++)
//        {
//            for (int i=0; i<2; i++)
//            {
//                StoreCount++;
//
//                TestingIndex.clear();
//                TestingIndex.push_back(i); TestingIndex.push_back(j); TestingIndex.push_back(k);
//                A(TestingIndex)=StoreCount;
//            }
//        }
//    }
//
//    cout<<"Following set up..."<<endl;
//    A.Display();
//    SimpleMatrix<double> B;
//    B=Apply(Add1, A);
//    //B=Apply(sin, A);
//    cout<<"After applying add 1 to B..."<<endl;
//    B.Display();
//
//
//
//}
//
//
//
//
//
//
//void TESTDimensionsCompatible(void)
//{
//    //Tested, works
//    cout<<"Starting DimensionsCompatible test"<<endl;
//    SimpleMatrix<double> A(2,3,4);
//    SimpleMatrix<double> B(2,3,4);
//    SimpleMatrix<double> C(2,1,4);
//    if (A.DimensionsCompatible(B))
//        cout<<"Dimensions compatible"<<endl;
//    else
//        cout<<"Dimensions NOT compatible"<<endl;
//
//    if (A.DimensionsCompatible(C))
//        cout<<"Dimensions compatible"<<endl;
//    else
//        cout<<"Dimensions NOT compatible"<<endl;
//
//
//
//}



