
void EVSetSomeEvents(void)
{

    vector<int> veccy;
    veccy.push_back( 1);
    veccy.push_back( 2);
    cout<<veccy[0]<<" "<<veccy[1]<<endl;
    veccy.resize(1);
    cout<<veccy.size()<<endl;

    cout<<veccy[0]<<" "<<veccy[1]<<endl;
    veccy.resize(2, 3);
    cout<<veccy[0]<<" "<<veccy[1]<<" "<<veccy[2]<<endl;

    EventVector Test;
//    std::cout<<Test.Set(2012.1, 2)<<endl;
//    Test.Display();
//    std::cout<<Test.Set(2012.5, 3)<<endl;
//    Test.Display();
//    std::cout<<Test.Set(2012.3, 1)<<endl;
//    Test.Display();

    Test.Set(2012.1, 2);
    Test.Set(2012.5, 3);
    Test.Display();
    std::cout<<"Deleting future"<<endl;
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
    for (int i=1; i<10000; i++)
    {
        Test.Set(2012.5+i, 3+1);
    }
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Time in seconds: "<< duration <<'\n';




}
