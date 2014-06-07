// Developed by James Jansson

// This library is essentially compiler candy, designed to reduce the size of matrix operations from several lines down to a single line.
// At this stage, all operations are done elementwise.
// Please note that none of these functions have been security tested as they are intended for scientific computing.

//Settings
int SMThreadsToUse=1;//will be used for multithreading in a future life
int MaxEntries=100000000;


// Class declarations

template <class TemplateType>
class SimpleMatrix {
    vector<int> DimSize;
    int TotalArraySize;//equals the dimensions of the array multiplied together
    bool Extendable=false;//determines if adding values to areas outside the matrix is allowed. At the moment, only predefined sized Matrices will be allowed for simplicity. In future releases this may be allowed, but will require a cleaver method to extend teh vector size
    TemplateType ValueArray;

    int FindIndex(int n, ...);//used privately to determine the internal index value of the

    public:
    SimpleMatrix(int n, ...);//constructor: n, the number of ints in the constructor
    //SimpleMatrix(vector<int> v);//alows a vector to be used to specify the dimensions of the matrix
    SimpleMatrix(SimpleMatrix<int> v);
    SimpleMatrix(void);//allows the quick defintion of a single value to be represented as a SimpleMatrix type to making pointer functions a whole heap easier

    //vector<int> Dimensions(void);
    SimpleMatrix<int> Dimensions(void);//to allow operations on dimensions, it will be amazing!
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

template <class TemplateType>
SimpleMatrix<TemplateType>::SimpleMatrix(int n, ...)//constructor: n, the number of ints in the constructor
{
    //Load all the relevant parameters
    va_list vl;
    va_start(vl,n);//Initialize a variable argument list

    int val;
    for (int i=0; i<n; i++)//cycle through each of the arguments
    {
        //load the next argument
        val=va_arg(vl,int);
        //store next
        DimSize.push_back(val);
    }
    va_end(vl);//End using variable argument list

    //Create the necessary array of values
}

template <class TemplateType>
SimpleMatrix<TemplateType>::SimpleMatrix(void)
{
    DimSize.push_back(1);
}

template <class TemplateType>
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

SimpleMatrix Multiply(SimpleMatrix A, SimpleMatrix B)//performs an element by element multiplication
{
    // Check the the dimensions are equal,
    // A.NumberOfDimensions()==B.NumberOfDimensions()
    // Then check that there are an equal number of each dimension
    // A.Dimensions(void);

    // Note that one (only) of the matrices are allowed to swap out one of more of the dimensions with '1',
    // and every time that dimension is called it uses the [0] value
    // e.g. A has dimensions 5,4,6 and B has 5,1,6, it will always look up the 0 for the 2nd dimension to make a matrix of 5, 4, 6
    CheckDimsEqual(SimpleMatrix, SimpleMatrix);//returns a vector indicating the number of dimensions that are equal
    SimpleMatrix
}

SimpleMatrix SimpleMatrix::Join(SimpleMatrix A, SimpleMatrix B, int Dimension)
{
    //check that all other dimensions are equal (except the dimension that we want to join along
    return A;
}

// this is a method to allow function pointer, to let any function to be applied to the whole matrix
SimpleMatrix SimpleMatrix::Apply(&FunctionPointer, int n, ...)//feed in an arbitrary number of args to the function pointer
{
    SimpleMatrix<> ResultMatrix;
    //cycle through all of the elements of the entire function
    FunctionPointer(remainingargs);

    return ResultMatrix;
}

// ALTERNATIVE: to allow multiple matrices to work together in a function
SimpleMatrix Apply(&FunctionPointer, SimpleMatrix A)
{
    //for all the elements of A

}

SimpleMatrix Apply(&FunctionPointer, SimpleMatrix A, SimpleMatrix B)//this will allow the operator overloading to occur, especially + - * / % ^

SimpleMatrix Apply(&FunctionPointer, SimpleMatrix n, ...) // for an arbitrary number of simple matrices.


// From this point on are the declarations of template functions that allow the operator overloads to work
template <class TemplateType>
TemplateType SMMultiply(TemplateType a, TemplateType b)
{
    return a*b;
}


