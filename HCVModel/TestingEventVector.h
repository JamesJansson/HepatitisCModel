
void EVSetSomeEvents(void)
{

    EventVector Test;
    std::cout<<Test.Set(2012.1, 2)<<endl;
    Test.Display();
    std::cout<<Test.Set(2012.5, 3)<<endl;
    Test.Display();
    std::cout<<Test.Set(2012.3, 1)<<endl;
    Test.Display();
    std::cout<<Test.Set(2012.3, 1, true)<<endl;
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
    for (i=1; i<10000; i++)
    {
        Test.Set(2012.5+i, 3+1);
    }
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Time in seconds: "<< duration <<'\n';




}
