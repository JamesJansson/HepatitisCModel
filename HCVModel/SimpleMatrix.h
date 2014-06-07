// Developed by James Jansson

// This library is essentially compiler candy, designed to reduce the size of matrix operations from several lines down to a single line.
// At this stage, all operations are done elementwise.
// Please note that none of these functions have been security tested as they are intended for scientific computing.
// This library will likely require c++11 setting turned on in your compiler.

#include <stdarg.h>

//Settings
int SMThreadsToUse=1;//will be used for multithreading in a future life
int SMMaxEntries=10000000;//used to prevent memory explosions


// Class declarations

template <typename TemplateType>
class SimpleMatrix {
    vector<int> DimSize;
    int TotalArraySize;//equals the dimensions of the array multiplied together
    bool Extendable=false;//determines if adding values to areas outside the matrix is allowed. At the moment, only predefined sized Matrices will be allowed for simplicity. In future releases this may be allowed, but will require a cleaver method to extend teh vector size
    TemplateType ValueArray;

    int FindIndex(int n, ...);//used privately to determine the internal index value of the

public:
    //this is a recursive argument counter, as described here: http://stackoverflow.com/a/16338804/1275985
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

    template<int... Args>
    SimpleMatrix(int&&... args);//constructor: n, the number of ints in the constructor
    SimpleMatrix(vector<int> v);//alows a vector to be used to specify the dimensions of the matrix
    //SimpleMatrix(SimpleMatrix<int> v);
    SimpleMatrix(void);//allows the quick defintion of a single value to be represented as a SimpleMatrix type to making pointer functions a whole heap easier




    vector<int> Dimensions(void);
    //SimpleMatrix<int> Dimensions(void);//to allow operations on dimensions, it will be amazing!
    int NumberOfDimensions(void);//a simple integer value of the number of dimensions
    string DimSizeString(void);

    //Future functions
    void Set(TemplateType n, ...);//allows a vector to be set for easy use of the matrix
    TemplateType Value(int n, ...);//returns the value of the function given the arguments
    TemplateType UnitaryValue(int n, ...);//this is used to reurn a value that lies outside the dimension of the matrix in the singular dimension
    SimpleMatrix Resize(int n, ...);//increases dimensions by specified amount
    SimpleMatrix Transpose(void);//takes 1 or 2 dimension matrices only


    // Overloading, pointer and template functions
    //SimpleMatrix SimpleMatrix::Apply(&FunctionPointer, int n, ...);


    //Testing functions
    void TestConstructor(void);
};
//Error: Index is larger than matrix size
//exit(-1);



/*template <typename CountTemplateType>
int CountArgs(CountTemplateType t)
{
    NumArgs++;
    return NumArgs;
}

template<typename CountTemplateType, typename... ArgType>
int CountArgs(CountTemplateType t, ArgType... args)
{
    NumArgs++;
    return CountArgs(args...);
}*/

//Contructors
template <typename TemplateType>
SimpleMatrix<TemplateType>::SimpleMatrix(int&&... args)//constructor: n, the number of ints in the constructor
{
    va_list args;
    //Determine number of args
    NumArgs=0;
    int TotalArgs=CountArgs(args);


    va_start(args, TotalArgs);//Initialize a variable argument list

    //Load all the relevant parameters
    //va_list vl;
    //va_start(vl,n);//Initialize a variable argument list

    int val;
    for (int i=0; i<TotalArgs; i++)//cycle through each of the arguments
    {
        //load the next argument
        val=va_arg(args,int);
        //store next
        DimSize.push_back(val);

        cout<< val <<", ";
    }
    cout<<endl;

    va_end(args);//End using variable argument list

    //Create the necessary array of values
}

template <typename TemplateType>
SimpleMatrix<TemplateType>::SimpleMatrix(void)
{
    DimSize.push_back(1);
}

template <typename TemplateType>
void SimpleMatrix<TemplateType>::TestConstructor(void)
{
    for (int val : DimSize )
        cout<< val <<", ";
    cout<<endl;
}






// Operator overloading
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading
// In particular, we will be looking to overload the assignment operator to allow straighforward assignment of values
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading#Assignment_operator
// we will also make use of the subscript operator []
// we may be able to use the subscript operator [][][] by iterating over the subscript operator multiple times
// http://stackoverflow.com/questions/6969881/operator-overload

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
    //check that all other dimensions are equal (except the dimension that we want to join along
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

/*
// ALTERNATIVE: to allow multiple matrices to work together in a function
SimpleMatrix Apply(&FunctionPointer, SimpleMatrix A)
{
    //for all the elements of A

}

SimpleMatrix Apply(&FunctionPointer, SimpleMatrix A, SimpleMatrix B)//this will allow the operator overloading to occur, especially + - * / % ^

SimpleMatrix Apply(&FunctionPointer, SimpleMatrix n, ...) // for an arbitrary number of simple matrices.
*/

// From this point on are the declarations of template functions that allow the operator overloads to work
template <typename TemplateType>
TemplateType SMMultiply(TemplateType a, TemplateType b)
{
    return a*b;
}


