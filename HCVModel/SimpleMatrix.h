// Developed by James Jansson

// Class declarations
{
template <class T>
class SimpleMatrix {
    vector<int> DimSize;
    bool Extendable=true;//determines if adding values to areas outside the

    public:
    void SimpleMatrix(int n, ...);
    void TestConstructor(void);
    void Resize(int n, ...);//

    vector<int> Dimensions(void);
    int NumberOfDimensions(void);
    string DimSizeString();

    //v();
};
//Error: Index is larger than matrix size
//exit(-1);

void SimpleMatrix::SimpleMatrix(int n, ...)//constructor: n, the number of ints in the constructor
{
    //Load all the relevant parameters
    va_list vl;
    va_start(vl,n);//Initialize a variable argument list
    for (int i=0; i<n; i++)//cycle through each of the arguments
    {
        //load the next argument
        val=va_arg(vl,int);
        //store next
    }
    va_end(vl);//End using variable argument list
}

void TestConstructor(void)
{
    for (int val : DimSize )
        cout<< val <<", ";
    cout<<endl;
}


}

// Operator overloading
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading
// In particular, we will be looking to overload the assignment operator to allow straighforward assignment of values
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading#Assignment_operator
// we may also make use of the subscript operator []
// we may be able to use the subscript operator [][][] by iterating over the subscript operator multiple times
// http://stackoverflow.com/questions/6969881/operator-overload


SimpleMatrix Multiply(SimpleMatrix A, SimpleMatrix B)//performs an element by element multiplication
{
    // Check the the dimensions are equal,
    // A.NumberOfDimensions()==B.NumberOfDimensions()
    // Then check that there are an equal number of each dimension
    // A.Dimensions(void);

    // Note that one (only) of the matrices are allowed to swap out one of more of the dimensions with '1',
    // and every time that dimension is called it uses the [0] value
    // e.g. A has dimensions 5,4,6 and B has 5,1,6, it will always look up the 0 for the 2nd dimension.
    CheckDimsEqual(SimpleMatrix, SimpleMatrix);//returns a vector indicating the number of dimensions that are equal
    SimpleMatrix
}

template
//

InsertMatrix

Join(SimpleMatrix A, SimpleMatrix B, int Dimension)
{
    //check that all other dimensions are equal
}


// this is a method to allow function pointer, to let any function to be applied to the whole matrix
SimpleMatrix SimpleMatrix::Apply(&FunctionPointer, int n, ...)//feed in an arbitrary number of args to the function pointer
{
    //cycle through all of the elements of the entire function
}




