// Developed by James Jansson
#include <fstream>
#include <sstream>// may not be necesary in final build
//using namespace std;

class csvfile {

    vector<string> FileLines;
    vector <vector <string>> StringMatrix;
    // int array to store the converted strings
    // float array to store the converted strings

public:
    vector<string> SplitLine(const std::string&  LineString);//note that this should eventually not be public (following testing)



    int Open(string FileName);//loads file and data
    int GetInt(int x, int y);
    int GetInt(int xStart, int xEnd, int yStart, int yEnd);
    int ConvertToInt(void);
    int ConvertToFloat(void);
    int ReadInt(string FileName, int ReadDimensionXStart, int ReadDimensionXEnd, int ReadDimensionYStart, int ReadDimensionYEnd);
    float ReadFloat(string FileName, int ReadDimensionXStart, int ReadDimensionXEnd, int ReadDimensionYStart, int ReadDimensionYEnd);
    string ReadString(string FileName, int ReadDimensionXStart, int ReadDimensionXEnd, int ReadDimensionYStart, int ReadDimensionYEnd);

    void DisplayFile(void);

    // Writing functions
    int Add(int ArrayOf, int xpos, int ypos);//


    // SaveFile
    // is the string contains a " or a , then the string has to be put in quotes ("_") and all quotes in the original string have to be turned into double quote marks


};


int csvfile::Open(string FileName)
{
    std::ifstream infile;
    string CurrentLine;
    infile.open (FileName, std::ifstream::in);
	std::string LineString;
    if (infile.is_open()==false)
    {
        std::cout << "\nError opening file";
        return -1;
    }
    // Read in the files
    while (infile.good())
    {
        getline(infile, CurrentLine, '\n');
        FileLines.push_back(CurrentLine);
    }
    infile.close();

    //Convert the file lines to individual strings
    for(string CurrentString : FileLines)
    {
        StringMatrix.push_back(SplitLine(CurrentString));//Split lines returns a vector of strings
    }
    return 0;
}


vector<string> csvfile::SplitLine(const std::string&  LineString)
{
    bool EntryEndReached;
    bool QuoteOpen;

    string CurrentString;
    vector<string> StringPart;
    //Determine the length of the string
    int StringLength=LineString.length();
    int charpos=0;

    //for each of the entries
    int EntryCount=0;
    while (charpos<StringLength)
    {
        EntryCount++;
        CurrentString.clear();

        EntryEndReached=false;
        if (LineString[charpos]=='"')//is a quotemark
        {
            QuoteOpen=true;
            charpos++;
        }
        else
        {
            QuoteOpen=false;
        }

        //keep going while not the last element of the line
        while (EntryEndReached==false && charpos<StringLength)
        {
            if (QuoteOpen==false && LineString[charpos]==',')//if a character is found and is not being protect by quotes being open
            {
                EntryEndReached=true;
                charpos++;
            }
            else if (QuoteOpen==true && LineString[charpos]=='"')//is a quotemark
            {
                if (charpos+1==StringLength) //it is the last element of the string (to avoid accessing memory illegally)
                {
                    QuoteOpen=false; //it must be a quote close mark
                    charpos++;
                }
                else if (LineString[charpos+1]=='"')//the next character is also a quote mark
                {
                    // the quote is still open
                    // add a quote mark to the string
                    CurrentString.push_back('"');
                    charpos++;//jump twice because of the escape character
                    charpos++;//jump twice because of the escape character
                }
                else
                {
                    QuoteOpen=false; //it must be a quote close mark
                    charpos++;
                }
            }
            else
            {
                CurrentString.push_back(LineString[charpos]);
                charpos++;
            }
        }

        //note that an empty string should be counted as an entry, even if it is at the end of a line
        //Add a new entry
        StringPart.push_back(CurrentString);
    }
    //return a vector of strings, to be converted later
    return StringPart;
}

void csvfile::DisplayFile(void)
{
    for(string CurrentString : FileLines)
        cout << "  " << CurrentString << endl;
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


