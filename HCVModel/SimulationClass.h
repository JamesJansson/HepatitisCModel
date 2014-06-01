#include "EventVector.h"
using namespace std;

class Simulation {
    int Optimised;

    // Define the parameterisation for this simulation

    // Define the population
    // Define the network that the population follows
    //

    EventVector NewInjectors;
    //Break down by state (and year in the event vector)





public:
    Simulation(void);//Constructor class
    int Reset(void);
    int SetParameters(int A);

    int LoadData(void);

    int RunOptimisation(void);

    int RunBaseline(void);
    int RunIntervention(void);

    int DetermineSummaryStatistics(void);




	void Display (void);
};


Simulation::Simulation(void)//Constructor class
{

	Optimised=0;
	//Load parameters

}


int Simulation::Reset(void)
{

    return 0;

}




