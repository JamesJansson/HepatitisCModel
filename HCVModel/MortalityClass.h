#define NumberOfAgeGroups 24
class MortalityClass {

	public:
    float DetermineAgeAtDeathGeneral(int SexValue, float StartAge);//look up 'oldcode parameter setup to find more to do with mortality


//----------------------------------------------------------------------------------------


	//Rates of mortality
	float GeneralPopulationMortalityRate[2][NumberOfAgeGroups];//Mortality rates by age band to 120, 5 year age bands, and gender
	float GeneralPopulationMortalityRateBand[2][NumberOfAgeGroups];//Mortality rates by age band to 120, 5 year age bands, and start age stop age
	float LiverFailureRelatedMortality, HCCRelatedMortality;
	float FirstYearTransplantMortality, SubsequentYearTransplantMortality;
	float IDUDrugUseMortality;



};


float MortalityClass::DetermineAgeAtDeathGeneral(int SexValue, float StartAge)//sex male=0, female=1
{
	//Tested, works well.
	float PredictedAgeAtDeath;
	int i=0;
	int AgeBandChosen=NumberOfAgeGroups-1;
	bool DeathOccurred=0;
	while (i<NumberOfAgeGroups-1)
	{
	    cout<<"What is happening below with the [0] and the [1]";
		if (StartAge>=GeneralPopulationMortalityRateBand[0][i] && StartAge<GeneralPopulationMortalityRateBand[1][i])
		{
			AgeBandChosen=i;
		}
		i++;
	}

	float CurrentAge=StartAge;

	while (AgeBandChosen<NumberOfAgeGroups)
	{
		PredictedAgeAtDeath=YearsUntilEvent (GeneralPopulationMortalityRate[SexValue][AgeBandChosen]) +CurrentAge;
		if (PredictedAgeAtDeath<GeneralPopulationMortalityRateBand[1][AgeBandChosen])
		{
			return PredictedAgeAtDeath;
		}
		else
		{
			AgeBandChosen++;
			CurrentAge=GeneralPopulationMortalityRateBand[0][AgeBandChosen];
		}
	}

	return -1;//a negative age indicates that a person exceeds the age of 10000
}



