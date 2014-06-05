#include <iostream>
#include <ctime>

#include "EventVector.h"
#include "SimulationClass.h"
#include "csvread.h"
//#include <thread.h>

#include "TEST.h"
#define TESTOn 1

using namespace std;

int main()
{
    cout << "argv and argc will determine what the program is to do (optimise, sim, load previous sim etc)" << endl;
    if (TESTOn)
    {
        cout << "Starting  testing" << endl;
        TESTFunctions();
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

    //Save optimised simulation
        // use current time as part of the filename

    //Run baseline
    Simulation BaselineSim=Sim;
    //Save baseline simulation

    //Create an intervention simulation
    Simulation InterventionSim=Sim;

    // Create disired output summary statistics

    // Perform sensitivity analyses

    // Save output of these simulations



    return 0;
}


