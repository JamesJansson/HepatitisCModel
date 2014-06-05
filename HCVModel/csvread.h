#include <fstream>
#include <sstream>// may not be necesary in final build
//using namespace std;

class csvfile {

    vector<string> FileLines;
    // vector of vector of strings
    // int array to store the converted strings
    // float array to store the converted strings


    vector<string> SplitLine(string LineString);


public:
    int Open(string FileName);//loads file an data
    int ConvertToInt(void);
    int ConvertToFloat(void);
    int ReadInt(string FileName, int ReadDimensionXStart, int ReadDimensionXEnd, int ReadDimensionYStart, int ReadDimensionYEnd);
    float ReadFloat(string FileName, int ReadDimensionXStart, int ReadDimensionXEnd, int ReadDimensionYStart, int ReadDimensionYEnd);
    string ReadString(string FileName, int ReadDimensionXStart, int ReadDimensionXEnd, int ReadDimensionYStart, int ReadDimensionYEnd);

    //
    int Add(int ArrayOf, int xpos, int ypos);//


    // SaveFile
    // is the string contains a " or a , then the string has to be put in quotes ("_") and all quotes in the original string have to be turned into double quote marks


};


int csvfile::SplitLine(string LineString)
{
    bool CommaOpen=1;
    bool EntryStarted=;
    bool QuoteOpen=0;
    string CurrentString;
    //Determine the length of the string

    int charcount=0;

    //any time you look at the next character, check that the current

    //return a vector of strings, to be converted later?
    return 0;
}





























#define csvreadmaxrows 30000
#define csvreadmaxcolumns 300

//int version
int csvread(std::string FileName, int** FileData, const int ReadDimensionXStart, const int ReadDimensionXEnd, const int ReadDimensionYStart, const int ReadDimensionYEnd)
{
	std::ifstream infile;
	std::istringstream FileLineStream;
	//Set maximum size of array
	int MaxArraySizeX=ReadDimensionXEnd-ReadDimensionXStart+1;
	int MaxArraySizeY=ReadDimensionYEnd-ReadDimensionYStart+1;
	//int *FileData=new int [MaxArraySizeX * MaxArraySizeY];//Note that this is a 1 dimensional declaration for a 2D array used as a hack to overcome memory issues in dynamic allocation
	//int** ary = new int*[sizeX];
	//	for(int i = 0; i < sizeX; ++i)
	//	ary[i] = new int[sizeY];

	int LineCount, CommaCount;
	int ColumnCount, RowCount;
	char Line[csvreadmaxrows] ;
	char CharNumber[csvreadmaxcolumns];

	std::cout<<"Insert into here a try catch exception to handle a lack of the appropriate file. "<<endl;
	std::cout<<"Also try to handle exceptions to the file dimension size maximum. "<<endl;

    infile.open (FileName, std::ifstream::in);
	std::string LineString;
    if (infile.is_open())
    {
		RowCount=0;
		LineCount=0;
        while (infile.good())
        {
			FileLineStream.clear();
			infile.getline(Line, csvreadmaxrows, '\n');
			if (LineCount>=ReadDimensionYStart && LineCount<=ReadDimensionYEnd)
			{
				LineString=Line;
				FileLineStream.str(LineString);
				ColumnCount=0;
				CommaCount=0;
				while (FileLineStream.good() && ColumnCount<=(ReadDimensionXEnd-ReadDimensionXStart))
				{
					FileLineStream.getline(CharNumber, csvreadmaxcolumns, ',');

					if (CommaCount>=ReadDimensionXStart && CommaCount<=ReadDimensionXEnd)
					{
						FileData[ColumnCount][RowCount]= atoi(CharNumber) ;
						ColumnCount++;
					}
					CommaCount++;
				}
				RowCount++;
			}
			LineCount++ ;

        }
		//Testing: testing to see that the data is being read in properly
		bool TestingOn=false;
		if (TestingOn)
		{
			for (int i=0; i<MaxArraySizeY; i++)
			{
				std::cout<<"\n"<<i<<':';
				for (int j=0; j<MaxArraySizeX; j++)
				{
					std::cout<<FileData[j][i]<<' ';
				}
			}
		}
        infile.close();
    }
    else
    {
        std::cout << "\nError opening file";
    }
	//std::cout << "\nWe may need to eliminate the delete line if the values need to be transfered back through the pointer";
	//delete[] FileData;
	return 0;
}

//float version
int csvread(std::string FileName, float** FileData, const int ReadDimensionXStart, const int ReadDimensionXEnd, const int ReadDimensionYStart, const int ReadDimensionYEnd)
{
	std::ifstream infile;
	std::istringstream FileLineStream;
	//Set maximum size of array
	int MaxArraySizeX=ReadDimensionXEnd-ReadDimensionXStart+1;
	int MaxArraySizeY=ReadDimensionYEnd-ReadDimensionYStart+1;

	int LineCount, CommaCount;
	int ColumnCount, RowCount;
	char Line[csvreadmaxrows] ;
	char CharNumber[csvreadmaxcolumns];
    infile.open (FileName, std::ifstream::in);
	std::string LineString;
    if (infile.is_open())
    {
		RowCount=0;
		LineCount=0;
        while (infile.good())
        {
			FileLineStream.clear();
			infile.getline(Line, csvreadmaxrows, '\n');
			if (LineCount>=ReadDimensionYStart && LineCount<=ReadDimensionYEnd)
			{
				LineString=Line;
				FileLineStream.str(LineString);
				ColumnCount=0;
				CommaCount=0;
				while (FileLineStream.good() && ColumnCount<=(ReadDimensionXEnd-ReadDimensionXStart))
				{
					FileLineStream.getline(CharNumber, csvreadmaxcolumns, ',');

					if (CommaCount>=ReadDimensionXStart && CommaCount<=ReadDimensionXEnd)
					{
						FileData[ColumnCount][RowCount]= atof(CharNumber) ;
						ColumnCount++;
					}
					CommaCount++;
				}
				RowCount++;
			}
			LineCount++ ;

        }
		//Testing: testing to see that the data is being read in properly
		bool TestingOn=false;
		if (TestingOn)
		{
			for (int i=0; i<MaxArraySizeY; i++)
			{
				std::cout<<"\n"<<i<<':';
				for (int j=0; j<MaxArraySizeX; j++)
				{
					std::cout<<FileData[j][i]<<' ';
				}
			}
		}
        infile.close();
    }
    else
    {
        std::cout << "\nError opening file";
    }
	return 0;
}

int csvwrite(std::string FileName, float** FileData, int DimensionX, int DimensionY)
{
	std::ofstream Output;
	Output.open (FileName);

	for (int i=0; i<DimensionY; i++)
	{
		for (int j=0; j<DimensionX; j++)
		{
			Output << FileData[j][i]<<",";
		}
		Output << "\n";
	}
	Output.close();
	return 0;
}


