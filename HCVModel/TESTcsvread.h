
void TESTCSVGetInt(void)
{
    csvfile a;
    a.Open("test.csv");
    a.DisplayFile();

    int x, y;
    x=2;
    y=3;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=3;
    y=2;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=10;
    y=2;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=0;
    y=9;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=1;
    y=9;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=2;
    y=9;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=3;
    y=9;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=4;
    y=9;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=5;
    y=9;
    cout<<x<<" "<<y<<": "<<a.GetInt(x, y)<<endl;

    x=4;
    y=9;
    cout<<x<<" "<<y<<": "<<a.GetFloat(x, y)<<endl;

    x=1;
    y=3;
    cout<<x<<" "<<y<<": "<<a.GetFloat(x, y)<<endl;


    cout<<"X size: "<<a.xSize()<<endl;
    cout<<"Y size: "<<a.ySize()<<endl;

}







void TESTcsvreadstring(void)
{
    csvfile a;
    a.Open("test.csv");


    a.DisplayFile();

    vector<string> output;
    string stringtoclean="Hello,nice,\"abc,\"";
    output=a.SplitLine(stringtoclean);

    stringtoclean="\"Hello,\"nice,\"abc,\"";
    output=a.SplitLine(stringtoclean);
}

/*void TESTsimplecsvread(void)
{
    // this won't work because it is using the old CSV read library

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


}*/


