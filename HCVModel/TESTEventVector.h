
void EVSetSomeEvents(void)
{

//    vector<int> veccy;
//    veccy.push_back( 1);
//    veccy.push_back( 2);
//    cout<<veccy[0]<<" "<<veccy[1]<<endl;
//    veccy.resize(1);
//    cout<<veccy.size()<<endl;
//
//    cout<<veccy[0]<<" "<<veccy[1]<<endl;
//    veccy.resize(2, 3);
//    cout<<veccy[0]<<" "<<veccy[1]<<" "<<veccy[2]<<endl;

    EventVector Test;
//    std::cout<<Test.Set(2012.1, 2)<<endl;
//    Test.Display();
//    std::cout<<Test.Set(2012.5, 3)<<endl;
//    Test.Display();
//    std::cout<<Test.Set(2012.3, 1)<<endl;
//    Test.Display();

    Test.Set(2012.1, 2);
    Test.Set(2012.5, 3);
    Test.Set(2012.7, 3);
    Test.Display();


    std::cout<<"Deleting future"<<endl;
    std::cout<<Test.Set(2012.9, 1, true)<<endl;
    Test.Display();






}

void EVSpeedTest(void)
{

    EventVector Test;
    std::cout<<"Starting speed test (1 million adds)"<<endl;
    //Get current time
    std::clock_t start;
    double duration;
    start = std::clock();
    for (int i=1; i<100000000; i++)
    {
        Test.Set(2012.5+i, 3+i);
    }
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Time in seconds: "<< duration <<'\n';
    std::cout<<Test.Size()<<endl;

}



void EVRangeTest(float StartTime, float EndTime)
{
    EventVector Test;
    EventData Output;
    Test.Set(2010.1, 55);
    Test.Set(2010.2, 56);
    Test.Set(2010.3, 57);
    Test.Set(2010.4, 58);
    Test.Set(2010.5, 59);



    Output=Test.Range(StartTime, EndTime);
    Output.Times;
    for (int c=0; c<Output.NoEvents; c++)
    {
        std::cout<< Output.Times[c] << " " << Output.Values[c] <<endl;
    }
}

void EVRangeTestMultiple(void)
{
    float StartTime, EndTime;
    StartTime=2009.2;
    EndTime=2009.3;
    std::cout<<"Testing values " << StartTime << " " <<EndTime<<endl;
    EVRangeTest(StartTime, EndTime);

    StartTime=2009.2;
    EndTime=2010.25;
    std::cout<<"Testing values " << StartTime << " " <<EndTime<<endl;
    EVRangeTest(StartTime, EndTime);

    StartTime=2009.2;
    EndTime=2010.8;
    std::cout<<"Testing values " << StartTime << " " <<EndTime<<endl;
    EVRangeTest(StartTime, EndTime);

    StartTime=2010.25;
    EndTime=2010.8;
    std::cout<<"Testing values " << StartTime << " " <<EndTime<<endl;
    EVRangeTest(StartTime, EndTime);

    StartTime=2010.2;
    EndTime=2010.8;
    std::cout<<"Testing values " << StartTime << " " <<EndTime<<endl;
    EVRangeTest(StartTime, EndTime);

    StartTime=2010.0;
    EndTime=2010.4;
    std::cout<<"Testing values " << StartTime << " " <<EndTime<<endl;
    EVRangeTest(StartTime, EndTime);
}
