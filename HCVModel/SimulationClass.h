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

Simulation::Simulation(int IDUPopSize, int HCVInfectedSize )//Constructor class overloaded for testing purposes
{
    //Person PUninfected;
    //PUninfected.DiseaseStage
    // Create a population
    //P.resize(PUninfected, IDUPopSize); // How to add a specific type of person to the group

    // Give a random time of birth
    float DateStartIDU;
    float AgeStartIDU;
    float InputBirthDate;
    int Sex;
    for (int i=0; i<IDUPopSize; i++)
    {
        Person TempP;
        P.push_back (TempP);
        if (i<HCVInfectedSize)
        {
            AgeStartIDU=randnormal(20.1, 5);
            InputBirthDate=randrange((float) 1960, (float) 1980);
            Sex=0;

            DateStartIDU=InputBirthDate+AgeStartIDU;

            P[i].StartIDU(DateStartIDU, InputBirthDate, Sex);
            //P(i).StartIDU
        }

    }

    // Give some of the individuals an infection some time between


}



int Simulation::Reset(void)
{

    return 0;

}





int PerformSensitivityAnalysis(void)
{
    //The point of this function is to take in a vector of simualtions (as defined above) and look at the parameters that change between the simulations
    //The function performs a GLM over the varying parameters in the simulation for the outcomes specificed in the input of this function

    // Importantly, the sensistivity analyses should not only look at absolute increase and decreases, but also proportional changes
    // for example the starting population is very likely to affect the outcome of a simulation
    // however, which parameter causes the greatest increase in infections?
    return 0;
}





