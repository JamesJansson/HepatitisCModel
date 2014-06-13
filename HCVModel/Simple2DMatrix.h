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
    vector<vector<TemplateType>> values;//Data is stored in the value array
    int xdimsize;
    int ydimsize;
    //bool validref(int xindex, int yindex);

    public:
    /// Constructors
    SimpleMatrix(int xsize, int ysize);//alows a vector to be used to specify the dimensions of the matrix
    SimpleMatrix(void);
    SimpleMatrix(vector<int> dimensions);//alows a vector to be used to specify the dimensions of the matrix
    void Resize(int xsize, int ysize);
    void Resize(vector<int> dimensions);

    /// Dimensions
    vector<int> dim(void);
    int xsize(void);
    int ysize(void);
    template <typename OtherType>
    bool DimensionsCompatible( SimpleMatrix<OtherType> Other);
    template <typename OtherType>
    void StopIfDimensionsIncompatible(SimpleMatrix<OtherType> Other);
    // void StopIfDimensionsIncompatible( SimpleMatrix<OtherType> Other);
    void SetAll(TemplateType SetValue);
    SimpleMatrix<TemplateType> Transpose(void);




    /// Overloading, pointer and template functions
    // Good tutorial on how this works: http://www.cprogramming.com/tutorial/operator_overloading.html
    // Index overloading
    // use () instead http://stackoverflow.com/questions/2533235/operator-c
    ///Getting values
        TemplateType operator()(int i, int j)const{ return values[i][j];};

    ///Setting Values
        TemplateType & operator()(int i, int j){ return values[i][j];};


    //Plus
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator+(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator+(const OtherType& Other);
    //Minus
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator-(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator-(const OtherType& Other);
        //Unary minus
        SimpleMatrix<TemplateType> operator-(void);
    //Times
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator*(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator*(const OtherType& Other);
    //Divide
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator/(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator/(const OtherType& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> DivideByMatrix(const OtherType& Other);
    //Modulus
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator%(const SimpleMatrix<OtherType>& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> operator%(const OtherType& Other);
        template <typename OtherType>
        SimpleMatrix<TemplateType> ModulusByMatrix(const OtherType& Other);


    //Other operators
    //http://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B
    // http://www.thegeekstuff.com/2013/09/cpp-operator-overloading/

    //
    //Changes this matrix
    void Apply(TemplateType (*FunctionPointer)(TemplateType));
    //returns a new matrix
    template <typename ReturnTemplateType>
    friend SimpleMatrix<ReturnTemplateType> Apply(ReturnTemplateType (*FunctionPointer)(TemplateType), const SimpleMatrix<TemplateType> A);
    //returns a new matrix, two input matrices
    template <typename ReturnTemplateType>
    friend SimpleMatrix<ReturnTemplateType> Apply(ReturnTemplateType (*FunctionPointer)(TemplateType, TemplateType), const SimpleMatrix<TemplateType> A, const SimpleMatrix<TemplateType> B);

    //Display functions
    void Display(void);
    void DisplayInfo(void);



};



/// Contructors
    template <typename TemplateType>
    SimpleMatrix<TemplateType>::SimpleMatrix(int xsize, int ysize)
    {
        Resize(xsize, ysize);
    }

    template <typename TemplateType>
    SimpleMatrix<TemplateType>::SimpleMatrix(void)
    {
        xdimsize=1;
        ydimsize=1;
        values.resize(xdimsize);
        values[0].resize(ydimsize);
    }

    template <typename TemplateType>
    SimpleMatrix<TemplateType>::SimpleMatrix(vector<int> dimensions)
    {
        Resize(dimensions);
    }

    template <typename TemplateType>
    void SimpleMatrix<TemplateType>::Resize(int xsize, int ysize)
    {
        if (xsize<=0 || ysize<=0)
        {
            cout<<"Error: cannot create a matrix of size less than zero"<<endl;
            exit(-1);
        }
        xdimsize=xsize;
        ydimsize=ysize;
        values.resize(xdimsize);

        for (int i=0; i<xdimsize; i++)
        {
            values[i].resize(ydimsize);
        }
    }

    template <typename TemplateType>
    void SimpleMatrix<TemplateType>::Resize(vector<int> dimensions)
    {
        if (dimensions.size()!=2)
        {
            cout<<"Error: cannot create a matrix which is larger or smaller than 2 dimensions"<<endl;
            exit(-1);
        }
        Resize(dimensions[0], dimensions[1]);
    }





///Dimension checking
    template <typename TemplateType>
    vector<int> SimpleMatrix<TemplateType>::dim(void)
    {
        vector<int> DimSize;
        DimSize.push_back(xdimsize);
        DimSize.push_back(ydimsize);
        return DimSize;
    }

    template <typename TemplateType>
    int SimpleMatrix<TemplateType>::xsize(void)
    {
        return xdimsize;
    }

    template <typename TemplateType>
    int SimpleMatrix<TemplateType>::ysize(void)
    {
        return ydimsize;
    }

    template <typename TemplateType> template <typename OtherType>
    bool SimpleMatrix<TemplateType>::DimensionsCompatible(SimpleMatrix<OtherType> Other)
    {
        if (xdimsize!=Other.xdimsize || ydimsize!=Other.ydimsize)
            return false;

        return true;//no problems
    }

    template <typename TemplateType> template <typename OtherType>
    void SimpleMatrix<TemplateType>::StopIfDimensionsIncompatible(SimpleMatrix<OtherType> Other)
    {
        if (DimensionsCompatible(Other)==false)
        {
            cout<<"Error: dimensions incompatible ("<<xdimsize<<","<<ydimsize<<") and ("<<Other.xdimsize<<","<<Other.ydimsize<<")."<<endl;
            exit(-1);
        }
    }

///Matrix operations
    template <typename TemplateType>
    void SimpleMatrix<TemplateType>::SetAll(TemplateType SetValue)
    {
        for (int i=0; i<xdimsize; i++)
        {
            for (int j=0; j<ydimsize; j++)
            {
                values[i][j]=SetValue;
            }
        }
    }




/// Operator overloading
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading
// In particular, we will be looking to overload the assignment operator to allow straighforward assignment of values
// http://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading#Assignment_operator
// we will also make use of the subscript operator []
// we may be able to use the subscript operator [][][] by iterating over the subscript operator multiple times
// http://stackoverflow.com/questions/6969881/operator-overload

// This source code has the basis for the overwhelming marjority of the operators that we wish to work on. Just search for "operator"
// https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01115_source.html

// Good tutorial on how this works: http://www.cprogramming.com/tutorial/operator_overloading.html

    ///Plus
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator+(const SimpleMatrix<OtherType>& Other)
        {
            StopIfDimensionsIncompatible(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]+Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator+(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]+Other;
            return ResultSM;
        }

        //Swapping for a discrete set of functions
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(char Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(short Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(int Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(long Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(long long Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(float Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(double Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(long double Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator+(bool Other, SimpleMatrix<TemplateType> SMClass){return (SMClass + Other);}

    ///Minus
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator-(const SimpleMatrix<OtherType>& Other)
        {
            StopIfDimensionsIncompatible(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]-Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator-(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]-Other;
            return ResultSM;
        }


        //Unary minus
        template <typename TemplateType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator-(void)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=-values[i][j];
            return ResultSM;
        }

        //Swapping for a discrete set of functions
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(char Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(short Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(int Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(long Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(long long Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(float Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(double Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(long double Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator-(bool Other, SimpleMatrix<TemplateType> SMClass){return -(SMClass - Other);}

    ///Times
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator*(const SimpleMatrix<OtherType>& Other)
        {
            StopIfDimensionsIncompatible(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]*Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator*(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]*Other;
            return ResultSM;
        }



        //Swapping for a discrete set of functions
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(char Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(short Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(int Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(long Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(long long Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(float Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(double Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(long double Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator*(bool Other, SimpleMatrix<TemplateType> SMClass){return (SMClass * Other);}

    ///Divide
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator/(const SimpleMatrix<OtherType>& Other)
        {
            StopIfDimensionsIncompatible(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]/Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator/(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]/Other;
            return ResultSM;
        }

        //Swapping for a discrete set of functions
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::DivideByMatrix(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=Other/values[i][j];
            return ResultSM;
        }
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(char Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(short Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(int Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(long Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(long long Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(float Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(double Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(long double Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator/(bool Other, SimpleMatrix<TemplateType> SMClass){return SMClass.DivideByMatrix(Other);}

    ///Modulus
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator%(const SimpleMatrix<OtherType>& Other)
        {
            StopIfDimensionsIncompatible(Other);
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]%Other.values[i][j];
            return ResultSM;
        }

        //For other types
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::operator%(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=values[i][j]%Other;
            return ResultSM;
        }

        //Swapping for a discrete set of functions
        template <typename TemplateType> template <typename OtherType>
        SimpleMatrix<TemplateType> SimpleMatrix<TemplateType>::ModulusByMatrix(const OtherType& Other)
        {
            SimpleMatrix<TemplateType> ResultSM(xdimsize, ydimsize);
            for (int i=0; i<xdimsize; i++)
                for (int j=0; j<ydimsize; j++)
                    ResultSM.values[i][j]=Other%values[i][j];
            return ResultSM;
        }


        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(char Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(short Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(int Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(long Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(long long Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(float Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(double Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(long double Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}
        template <typename TemplateType> SimpleMatrix<TemplateType> operator%(bool Other, SimpleMatrix<TemplateType> SMClass){return SMClass.ModulusByMatrix(Other);}



//Apply a function to the matrix
template <typename TemplateType>
void SimpleMatrix<TemplateType>::Apply(TemplateType (*FunctionPointer)(TemplateType))
{
    for (int i=0; i<xdimsize; i++)
        for (int j=0; j<ydimsize; j++)
            values[i][j]=FunctionPointer(values[i][j]);
}

//This section works
//template <typename InputTemplateType>
//SimpleMatrix<InputTemplateType> Apply(InputTemplateType (*FunctionPointer)(InputTemplateType), SimpleMatrix<InputTemplateType> A)
//This section used to work, now broken
template <typename ReturnTemplateType, typename InputTemplateType>
SimpleMatrix<ReturnTemplateType> Apply(ReturnTemplateType (*FunctionPointer)(InputTemplateType), SimpleMatrix<InputTemplateType> A)
{
    ReturnTemplateType TempResultStore;
    //Determine size of input vector
    SimpleMatrix<ReturnTemplateType> ResultSM(A.xdimsize, A.ydimsize);

    //for all the elements of A
    for (int i=0; i<A.xdimsize; i++)
    {
        for (int j=0; j<A.ydimsize; j++)
        {
            TempResultStore=FunctionPointer(A.values[i][j]);
            ResultSM.values[i][j]=TempResultStore;
        }
    }
    return ResultSM;
}

//Applying a function to 2 multidimensional matrices
template <typename ReturnTemplateType, typename InputTemplateType>
SimpleMatrix<ReturnTemplateType> Apply(ReturnTemplateType (*FunctionPointer)(InputTemplateType, InputTemplateType), SimpleMatrix<InputTemplateType> A, SimpleMatrix<InputTemplateType> B)
{
    A.StopIfDimensionsIncompatible(B);
    ReturnTemplateType TempResultStore;
    SimpleMatrix<ReturnTemplateType> ResultSM(A.xdimsize, A.ydimsize);

    //for all the elements of A
    for (int i=0; i<A.xdimsize; i++)
    {
        for (int j=0; j<A.ydimsize; j++)
        {
            TempResultStore=FunctionPointer(A.values[i][j],  A.values[i][j]);
            ResultSM.values[i][j]=TempResultStore;
        }
    }
    return ResultSM;
}



//Display functions
template <typename TemplateType>
void SimpleMatrix<TemplateType>::Display(void)
{
    cout<<"Contents: "<<endl;
    for (int j=0; j<ydimsize; j++)
    {
        for (int i=0; i<xdimsize; i++)
            cout<<values[i][j]<<", ";
        cout<<endl;
    }

}

template <typename TemplateType>
void SimpleMatrix<TemplateType>::DisplayInfo(void)
{
    cout<<"Dimensions: ( "<< xdimsize << ", " << ydimsize <<")"<<endl;

    cout<<"Contents summary: ";
    for (int j=0; j<ydimsize && j<5 ; j++)//limit to a 5 by 5 display of content
    {
        for (int i=0; i<xdimsize && i<5; i++)
            cout<<values[i][j]<<", ";
        cout<<endl;
    }
    cout<<"..."<<endl;
    cout<<"To see full contents use Display()"<<endl<<endl;
}














template <typename TemplateType>
SimpleMatrix<TemplateType> Join(SimpleMatrix<TemplateType> A, SimpleMatrix<TemplateType> B, int Dimension)
{
    SimpleMatrix<TemplateType> ReturnMatrix;
    //check that  other dimension is equal
    return ReturnMatrix;
}


    //Use this in in CountConstructorArgs to only run if ints
    //http://www.cplusplus.com/reference/type_traits/enable_if/
