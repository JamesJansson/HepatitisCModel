#include <iostream>
#include <ctime>

#include "EventVector.h"
#include "SimulationClass.h"


#include "TestingEventVector.h"
//#include "thread.h"
//#include "PersonClass.h"

#define TestingEventVector 1

using namespace std;

int main()
{


    if (TestingEventVector==1)
    {
        cout << "Starting  testing" << endl;
        EVRangeTestMultiple();
        //EVSetSomeEvents();
        //EVSpeedTest();
    }


    cout << "Starting model" << endl;

    // Load parameters and data

    // Create initial seed

    // Save seed

    // Set up multithreading
    // Create seeds for threads

    //Create simulation
    Simulation Sim(1000, 10);// add a seed element

    //Optimise simulation

    //Run baseline
    Simulation BaselineSim=Sim;

    //Create an intervention simulation
    Simulation InterventionSim=Sim;

    // Create disired output summary statistics

    // Perform sensitivity analyses

    // Save output of these simulations



    return 0;
}


