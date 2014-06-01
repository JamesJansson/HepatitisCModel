#include "EventVector.h"
#include "PersonClass.h"
using namespace std;

class Simulation {
    int Optimised;

    // Define the parameterisation for this simulation

    // Define the population
    // Define the network that the population follows
    //

    EventVector NewInjectors;
    //Break down by state (and year in the event vector)

    vector<Person> P;





public:
    Simulation(void);//Constructor class
    Simulation(int, int);// overloaded constructor class to allow early stage testing
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

Simulation::Simulation(int IDUPopSize, int HCVInfectedSize )//Constructor class
{
    Person PUninfected;
    PUninfected.DiseaseStage
    // Create a population
    //P.resize(PUninfected, IDUPopSize); // How to add a specific type of person to the group

    // Give a random time of birth
    float DateStartIDU;
    float InputBirthDate;
    int Sex;
    for (int i=0; i<IDUPopSize; i++)
    {



        StartIDU(float DateStartIDU, float InputBirthDate, int InputSex,  ParameterClass* p)

        P.HCV.DiseaseStage
    }

    // Give some of the individuals an infection some time between


}



int Simulation::Reset(void)
{

    return 0;

}




