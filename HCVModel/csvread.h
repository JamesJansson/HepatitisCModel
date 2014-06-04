#include <fstream>
#include <sstream>
//using namespace std;

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
	char Line[30000] ;
	char CharNumber[300];
    infile.open (FileName, std::ifstream::in);
	std::string LineString;
    if (infile.is_open())
    {
		RowCount=0;
		LineCount=0;
        while (infile.good())
        {
			FileLineStream.clear();
			infile.getline(Line, 30000, '\n');
			if (LineCount>=ReadDimensionYStart && LineCount<=ReadDimensionYEnd)
			{
				LineString=Line;
				FileLineStream.str(LineString);
				ColumnCount=0;
				CommaCount=0;
				while (FileLineStream.good() && ColumnCount<=(ReadDimensionXEnd-ReadDimensionXStart))
				{
					FileLineStream.getline(CharNumber, 300, ',');

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
	char Line[30000] ;
	char CharNumber[300];
    infile.open (FileName, std::ifstream::in);
	std::string LineString;
    if (infile.is_open())
    {
		RowCount=0;
		LineCount=0;
        while (infile.good())
        {
			FileLineStream.clear();
			infile.getline(Line, 30000, '\n');
			if (LineCount>=ReadDimensionYStart && LineCount<=ReadDimensionYEnd)
			{
				LineString=Line;
				FileLineStream.str(LineString);
				ColumnCount=0;
				CommaCount=0;
				while (FileLineStream.good() && ColumnCount<=(ReadDimensionXEnd-ReadDimensionXStart))
				{
					FileLineStream.getline(CharNumber, 300, ',');

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


