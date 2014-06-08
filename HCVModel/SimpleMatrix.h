// Developed by James Jansson

// This library is essentially compiler candy, designed to reduce the size of matrix operations from several lines down to a single line.
// At this stage, all operations are done elementwise.
// Please note that none of these functions have been security tested as they are intended for scientific computing.
// This library will likely require c++11 setting turned on in your compiler.

#include <stdarg.h>

//Settings
//int SMThreadsToUse=1;//will be used for multithreading in a future life
//int SMMaxEntries=10000000;//used to prevent memory explosions


// Class declarations

template <typename TemplateType>
class SimpleMatrix {
    vector<int> DimSize;
    int NDimSize;
    int TotalArraySize;//equals the dimensions of the array multiplied together
    bool Extendable=false;//determines if adding values to areas outside the matrix is allowed. At the moment, only predefined sized Matrices will be allowed for simplicity. In future releases this may be allowed, but will require a cleaver method to extend teh vector size
    //Data is stores in the value array
    vector<TemplateType> ValueArray;
    vector<int> Base;//used to reference cells in the matrix



    //This is a recursive argument counter, as described here: http://stackoverflow.com/a/16338804/1275985
    int TempArgsNum; //should be set to zero when using CountArgs
    vector<int> TempArgStorage;
    int CountIntArgs(int t)
    {
        TempArgStorage.push_back(t);
        TempArgsNum++;
        //cout<<"End: "<<TempArgsNum<<endl; //will want to make these functions save the Args to a vector for use later
        return TempArgsNum;
    }
    template<typename... Args>
    int CountIntArgs(int t, Args... args)
    {
        TempArgStorage.push_back(t);
        TempArgsNum++;
        //cout<<"Splitter: "<<TempArgsNum<<endl;
        return CountIntArgs(args...);
    }

    //Look up functions designed to references to the correct memory locations
    bool InRange(vector<int> Index);//used privately to determine that the index is in the range sepcified
    int IndexPos(vector<int> Index);//used privately to determine the linear array
    int IndexPosCheck(vector<int> Index);
    public:
    //Constructors
    template <typename... ArgType>
    SimpleMatrix(int FirstIndex, ArgType... args);//constructor should force all in specified matrices pass through this function while not diverting other defintitions such as vector<int>
    SimpleMatrix(vector<int> TempDimSize);//alows a vector to be used to specify the dimensions of the matrix
    SimpleMatrix(const SimpleMatrix<int>& TempDimSize);
    SimpleMatrix(void);//allows the quick defintion of a single value to be represented as a SimpleMatrix type to making pointer functions a whole heap easier
    void CreateValueArray(void);



    //vector<int> Dimensions(void);
    SimpleMatrix<int> Dimensions(void);//to allow operations on dimensions, it will be amazing!
    int NumberOfDimensions(void);//a simple integer value of the number of dimensions
    //string DimSizeString(void);

    //Future functions
    void Set(vector<int> Index, TemplateType SetValue);//this version should represent an array of indices
    void Set(const SimpleMatrix<int>& Index, TemplateType SetValue);
    template <typename... ArgType>
    void Set( TemplateType SetValue, int FirstIndex, ArgType... args);//allows a vector to be set for easy use of the matrix
    void Set(bool CheckDimension, vector<int> Index, TemplateType SetValue);//to allow faster execution without checking
    void SetAll(vector<TemplateType> VectorOfValues);//Allows the user to set the matrix to be a vector
    void SetAll(TemplateType SetValue);

    TemplateType Value(vector<int> Index);//returns the value of the matrix given the arguments
    TemplateType Value(int FirstIndex, ...);//returns the value of the matrix given the arguments
    template <typename... ArgType>
    TemplateType Value(int FirstIndex, ArgType... args);//special user specified version
    TemplateType UnitaryValue(int FirstIndex, ...);//this is used to return all values including those that lies outside the dimension of the matrix in the singular dimension
    SimpleMatrix Resize(int FirstIndex, ...);//increases dimensions by specified amount
    SimpleMatrix Transpose(void);//takes 1 or 2 dimension matrices only


    // Overloading, pointer and template functions
    //SimpleMatrix SimpleMatrix::Apply(&FunctionPointer, int n, ...);


    //Testing functions
    void TestConstructor(void);
    void TestIndexingFunctions(void);
    void TestIndexingFunctions(vector<int> Index);
    void TestDisplayAll(void);
};

// Indexing functions
template <typename TemplateType>
bool SimpleMatrix<TemplateType>::InRange(vector<int> Index) //used privately to determine that the index is in the range sepcified
{
    //Check the size of dimension vectors (want to avoid [4][5][6] vs [1][2])
    if (NDimSize<Index.size())
    {
        return false;
    }
    //Check each of the individual dim
    int DimCount=0;
    for (int CurrentDim : DimSize)
    {
        if (Index[DimCount]<0||(Index[DimCount]>CurrentDim-1))//because the indicies got from 0 to i-1
        {
            return false;
        }
        DimCount++;
    }
    return true;
}

template <typename TemplateType>
int SimpleMatrix<TemplateType>::IndexPos(vector<int> Index)//used privately to determine the linear array
{
    int ReturnIndexValue=0;
    int IndexCount=0;
    for (int ThisIndex: Index)
    {
        ReturnIndexValue=ReturnIndexValue+ThisIndex*Base[IndexCount];
        IndexCount++;
    }
    return ReturnIndexValue;
}

template <typename TemplateType>
int SimpleMatrix<TemplateType>::IndexPosCheck(vector<int> Index)
{
    //Determine if in range
    if (InRange(Index)==false)
    {
        //Error: Index is larger than matrix size
        cout<<"Error: Index is larger than matrix size";
        exit(-1);
    }
    return IndexPos(Index);
}

// Contructors
template <typename TemplateType> template <typename... ArgType>
SimpleMatrix<TemplateType>::SimpleMatrix(int FirstIndex, ArgType... args)//constructor should force all in specified matrices pass through this function while not diverting other defintitions such as vector<int>
{
    //Determine number of args
    TempArgsNum=0;
    TempArgStorage.clear();
    NDimSize=CountIntArgs(FirstIndex, args...);
    DimSize=TempArgStorage;

    //Assign memory size of matrix
    CreateValueArray();

}

template <typename TemplateType>
SimpleMatrix<TemplateType>::SimpleMatrix(vector<int> TempDimSize)
{
    DimSize=TempDimSize;
    NDimSize=DimSize.size();
    //Assign memory size of matrix
    CreateValueArray();
}


template <typename TemplateType>
SimpleMatrix<TemplateType>::SimpleMatrix(void)//used to define a variable extremely quickly
{
    DimSize.push_back(1);
    TotalArraySize=1;
    ValueArray.resize(1);
    Base.push_back(1);
}


template <typename TemplateType>
void SimpleMatrix<TemplateType>::CreateValueArray(void)
{
    TotalArraySize=1;
    for (int val : DimSize )
    {
        TotalArraySize=TotalArraySize*val;
    }
    //extend the memory space of the storage array
    ValueArray.resize(TotalArraySize);
    //Determine the base for indexing the array
    int BaseMultiplier=1;
    for (int val : DimSize )
    {
        Base.push_back(BaseMultiplier);
        BaseMultiplier=BaseMultiplier*val;
    }
}


// Setting functions
template <typename TemplateType>
void SimpleMatrix<TemplateType>::Set( vector<int> Index, TemplateType SetValue)
{
    ValueArray[IndexPosCheck(Index)]=SetValue;
}

template <typename TemplateType>
void SimpleMatrix<TemplateType>::SetAll(TemplateType SetValue)
{
    for (int i=0; i< TotalArraySize; i++)
        ValueArray[i]=SetValue;
}
template <typename TemplateType> template <typename... ArgType>
void SimpleMatrix<TemplateType>::Set( TemplateType SetValue, int FirstIndex, ArgType... args)
{
    TempArgsNum=0;
    TempArgStorage.clear();
    CountIntArgs(FirstIndex, args...);
    Set(TempArgStorage, SetValue);
}

// Value functions
template <typename TemplateType>
TemplateType SimpleMatrix<TemplateType>:: Value(vector<int> Index)
{
    //Check the index is right
    return ValueArray[IndexPosCheck(Index)];
}

template <typename TemplateType> template <typename... ArgType>
TemplateType SimpleMatrix<TemplateType>::Value(int FirstIndex, ArgType... args)
{
    TempArgsNum=0;
    TempArgStorage.clear();
    CountIntArgs(FirstIndex, args...);
    return ValueArray[IndexPosCheck(TempArgStorage)];//Check then look up the linear index specificed by TempArgStorage, find the associated value then return.
}




//Testing functions
template <typename TemplateType>
void SimpleMatrix<TemplateType>::TestConstructor(void)
{
    //Basic constructor of variable index size appears to be working well
    for (int val : DimSize )
        cout<< val <<", ";
    cout<<endl;
}

template <typename TemplateType>
void SimpleMatrix<TemplateType>::TestIndexingFunctions(void)
{
    //Display the base: base construction works
    cout<<"Base construction"<<endl;
    for (int val : Base )
        cout<< val <<", ";
    cout<<endl;
}

template <typename TemplateType>
void SimpleMatrix<TemplateType>::TestIndexingFunctions(vector<int> Index)
{
    cout<<"Value of index specified: "<< IndexPosCheck(Index)<<endl;
}

template <typename TemplateType>
void SimpleMatrix<TemplateType>::TestDisplayAll(void)
{
    cout<<"Contents: ";
    for (int i=0; i< TotalArraySize; i++)
        cout<<ValueArray[i]<<", ";
    cout<<endl;
}


// Operator overloading
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading
// In particular, we will be looking to overload the assignment operator to allow straighforward assignment of values
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading#Assignment_operator
// we will also make use of the subscript operator []
// we may be able to use the subscript operator [][][] by iterating over the subscript operator multiple times
// http://stackoverflow.com/questions/6969881/operator-overload

// This source code has the basis for the overwhelming marjority of the operators that we wish to work on. Just search for "operator"
// https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01115_source.html

//We will also look to overload all of the regular

template <typename TemplateType>
SimpleMatrix<TemplateType> Multiply(SimpleMatrix<TemplateType> A, SimpleMatrix<TemplateType> B)//performs an element by element multiplication
{
    SimpleMatrix<TemplateType> ReturnMatrix;
    // Check the the dimensions are equal,
    // A.NumberOfDimensions()==B.NumberOfDimensions()
    // Then check that there are an equal number of each dimension
    // A.Dimensions(void);

    // Note that one (only) of the matrices are allowed to swap out one of more of the dimensions with '1',
    // and every time that dimension is called it uses the [0] value
    // e.g. A has dimensions 5,4,6 and B has 5,1,6, it will always look up the 0 for the 2nd dimension to make a matrix of 5, 4, 6
    //CheckDimsEqual(SimpleMatrix, SimpleMatrix);//returns a vector indicating the number of dimensions that are equal
    //SimpleMatrix

    return ReturnMatrix;
}

template <typename TemplateType>
SimpleMatrix<TemplateType> Join(SimpleMatrix<TemplateType> A, SimpleMatrix<TemplateType> B, int Dimension)
{
    SimpleMatrix<TemplateType> ReturnMatrix;
    //check that all other dimensions are equal (except the dimension that we want to join along)
    //for (int ThisDim :A.Dimensions)
    return ReturnMatrix;
}

/*
// this is a method to allow function pointer, to let any function to be applied to the whole matrix
SimpleMatrix SimpleMatrix::Apply(&FunctionPointer, int n, ...)//feed in an arbitrary number of args to the function pointer
{
    SimpleMatrix<> ResultMatrix;
    //cycle through all of the elements of the entire function
    FunctionPointer(remainingargs);

    return ResultMatrix;
}*/


// ALTERNATIVE: to allow multiple matrices to work together in a function
/*template <typename TemplateType>
SimpleMatrix Apply(&FunctionPointer, SimpleMatrix<TemplateType> A)
{
    SimpleMatrix<TemplateType> C=A;
    //for all the elements of A

    return C;
}*/

/*
SimpleMatrix Apply(&FunctionPointer, SimpleMatrix A, SimpleMatrix B);//this will allow the operator overloading to occur, especially + - * / % ^

SimpleMatrix Apply(&FunctionPointer, SimpleMatrix n, ...);// for an arbitrary number of simple matrices.
*/

// From this point on are the declarations of template functions that allow the operator overloads to work


template <typename TemplateType>
TemplateType Add(TemplateType a, TemplateType b)
{
    return a+b;
}

template <typename TemplateType>
TemplateType Minus(TemplateType a, TemplateType b)
{
    return a-b;
}

template <typename TemplateType>
TemplateType Multiply(TemplateType a, TemplateType b)
{
    return a*b;
}

template <typename TemplateType>
TemplateType Divide(TemplateType a, TemplateType b)
{
    return a/b;
}



    //Use this in in countintargs to only run if ints
    //http://www.cplusplus.com/reference/type_traits/enable_if/
