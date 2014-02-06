#include <iostream>
#include <thread>//allows multithreading http://stackoverflow.com/questions/266168/simple-example-of-threading-in-c
#include "ProbabilityFunctions.h"



using namespace std;

#define NumberOfIndividuals 2300000
#define TransProb 0.1

class PersonC
{
    protected:
        int ID;
        int InfectionStage;
        float TimeInfected;
        int ConnectedTo[10];
    public:
        PersonC();
        void SetID(int Number);
        int ExposedToHCV();
        int GetInfectionStage();
        void ConnectRandomly(int MaxIDs);
        int ChooseSharer();
        void Infect();
};

PersonC::PersonC(){//constructor class
    InfectionStage=0;
};

void PersonC::SetID(int Number){//constructor class
    ID=Number;
};

int PersonC::ExposedToHCV()
{
    if (InfectionStage==0)
    {
        if (eventp(TransProb))
        {
            Infect();
            return 1;
        }
        return 0;
    }
    return 2;
};

void PersonC::Infect()
{
    InfectionStage=1;
};

void PersonC::ConnectRandomly(int MaxIDs)
{
    for (int i=0; i<10; i++)
    {
        ConnectedTo[i]=randrange(0,NumberOfIndividuals);
    }
};

int PersonC::ChooseSharer()
{
    return ConnectedTo[randrange(0,10)];
};

int PersonC::GetInfectionStage()
{
    return InfectionStage;
};


//The function we want to make the thread run.
void task1(string msg, int numtodisp)//can be int, etc if desired
{
    cout << "task1 says: " << msg << numtodisp;

};







PersonC P[NumberOfIndividuals];

int main()
{

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

    thread t1(task1, "Hello", 999999);//threaded task, can pass an int if it likes
    t1.join();//must do this to exit the program cleanly



    //#include  <random>
    //const int min = 100000;//To get this to work, this needs to be included in the project .pro file: CONFIG += c++11
    //const int max = 1000000;
    //std::default_random_engine generator;
    //std::uniform_int_distribution<int> distribution(min,max);
    //int random_int = distribution(generator);  // generate random int flat in [min, max]

    srand ( time(NULL) );
    rand();
    cout << "Hello world!" << rand()*RAND_MAX+rand() << endl;

    //Set up clases and pointers
    for (int i=0; i<NumberOfIndividuals; i++)
    {
        P[i].SetID(i);//so we can later create a pointer
    }


    //Set up network
    for (int i=0; i<NumberOfIndividuals; i++)
    {
        P[i].ConnectRandomly(NumberOfIndividuals-1);
        if (i%100000==0)
        {
            cout <<i << endl;
            //cout <<  P[i].ChooseSharer() << endl;
        }

    }
    // infect first person
    P[0].Infect();



    int Receiver;
    int Outcome;
    int IndivInfectionStage;
    int TotalInfected;
    int InfectedThisStep=0;
    // For an amount of time decide if the
    int TenPercent=NumberOfIndividuals/10;
    for (int t=0; t<100; t++)
    {
        InfectedThisStep=0;
        for (int i=0; i<NumberOfIndividuals; i++)
        {
            //Maybe here select the person at random

            Receiver=P[i].ChooseSharer();
            Outcome=P[Receiver].ExposedToHCV();

            if (Outcome==1)
            {
                InfectedThisStep++;
            }
            if ((i+1)%TenPercent==0)
            {
                cout <<"." ;
                //cout <<  P[i].ChooseSharer() << endl;
            }
        }

        TotalInfected=0;
        for (int i=0; i<NumberOfIndividuals; i++)
        {
            IndivInfectionStage=P[i].GetInfectionStage();
            if (IndivInfectionStage==1)
            {
                TotalInfected++;
            }
        }
        cout <<"Total infected: "<<TotalInfected<<", This step:"<< InfectedThisStep << endl;
    }


    return 0;
}
