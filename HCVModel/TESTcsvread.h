
void TESTcsvreadstring(void)
{
    csvfile a;

    a.Open("test.csv");
    a.DisplayFile();

    vector<string> output;
    string stringtoclean="Hello,nice,\"poo,\"";
    output=a.SplitLine(stringtoclean);

    stringtoclean="\"Hello,\"nice,\"poo,\"";
    output=a.SplitLine(stringtoclean);
}

void TESTsimplecsvread(void)
{
std::string FileName;
	FileName = "test.csv";
	std::cout << "\n" << FileName;
	int a;
	//float Output[9*8];
	//int Output[9][8];

	//testing csv read int function
	const int MaxArraySizeX=8-0+1;
	const int MaxArraySizeY=7-0+1;
	float** Output = new float*[MaxArraySizeX];
	for(int i = 0; i < MaxArraySizeX; i++)
    Output[i] = new float[MaxArraySizeY];
	a=csvread(FileName, Output, 0, 8, 0, 7);


	//testing
	for (int i=0; i<MaxArraySizeY; i++)
	{
		std::cout<<"\n"<<i<<':';
		for (int j=0; j<MaxArraySizeX; j++)
		{
			//std::cout<<Output[MaxArraySizeX*i + j]<<' ';
			std::cout<<Output[j][i]<<' ';
		}
	}


}


