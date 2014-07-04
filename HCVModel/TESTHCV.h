
void TESTHCV(void)
{

    // Start by creating a simulation class
    Simulation HCVSimulation, HCVSimulationIntervention;

    //Set up parameterisations
    // Send in the per yera probability of moving stages

    // Set the population (in this case a homogenous group of people infected with HCV)

    // Run the simulation that determines the transition of HCV
    HCVSimulation.Run(YearStart, YearEnd);

    //Get aggregate statistics
    HCVSimulation.CreateAggregateStatistics();

    HCVSimulation.SaveAggregateStatistics();
    //Maybe
    AggregateStats=HCVSimulation.AggregateStatistics();

    HCVSimulation.GetResults(ResultsType, Year, HCVInfection, HIVInfection, Sex, Age, Location, Treatment);//All inputs are vectors, to allow multiple selections

    ResultsType= infections, diagnoses, treatments, hospital utilisations, disease stage

    // request example: "I'd like to know the total number of female injecting drug users and sex workers by year who have an HCV diagnosis between 2003 and 2013

}


