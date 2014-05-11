//use this space to declare global variables
int TotalNumberOfIDU, NumberOfMaleRegularIDUs ;
//float HCVDiagnoses,

class MortalityClass {

	public:
	static const int NumberOfAgeGroups=25;
	float InterventionYearStart, InterventionYearStop;

	float AcuteInfectionDuration;
	float F0toF1[3], F1toF2[3], F2toF3[3], F3toF4[3], F4toHCC, F4toLiverFailure, LiverFailureToHCC;//movement through fibrosis levels
	//F0toF1[0] is IDU, F0toF1[1] is non-IDU
	//The risk of developing cirrhosis ranges from 5% to 25% over periods of 25 to 30 years.87,88 http://www.ashm.org.au/images/hcv/diagnosis_of_hep_c_update%20aug%20_09pdfaasld.pdf


	float TranslplantForHCC, TranslplantForLiverFailure;//rate of transplant
	//Rates of mortality
	float GeneralPopulationMortalityRate[2][NumberOfAgeGroups];//Mortality rates by age band to 120, 5 year age bands, and gender
	float GeneralPopulationMortalityRateBand[2][NumberOfAgeGroups];//Mortality rates by age band to 120, 5 year age bands, and start age stop age
	float LiverFailureRelatedMortality, HCCRelatedMortality;
	float FirstYearTransplantMortality, SubsequentYearTransplantMortality;
	float IDUDrugUseMortality;


	//Probability of diagnosis
	float AcuteDiagnosisProbability[2];//AcuteDiagnosisProbability[X]
	//X: intervention rate (0= current testing rate, 1=intervention testing rate)
	//float AcuteDiagnosisProbability(float Year);
	//Per-year probability of diagnosis
	float FibrosisDiagnosisProbabilityF[5][2];//FibrosisDiagnosisProbabilityF[X][Y]
	//X: 0-4 indicates fibrosis stages F0-F4
	//Y: intervention rate (0= current testing rate, 1=intervention testing rate)
	// NOTE: FibrosisDiagnosisProbabilityF[4][*] needs to be higher thant FibrosisDiagnosisProbabilityF[0][*] as the probability of noticing such symptoms


	//float FibrosisDiagnosisProbabilityF(float Year);


	//Probability of treatment
	float TreatmentRateAcute[2];//TreatmentRateAcute[X]
	//X: intervention rate (0= current treatment rate, 1=intervention treatment rate)
	//float TreatmentRateAcute(float Year);

	//Yearly probability of treatment
	float TreatmentRateF[5][2][2];//TreatmentRateF[X][Y][Z]
	//X: 0-4 indicates fibrosis stages F0-F4
	//Y: indicates HCV genotype (type1=1, non type 1=0)
	//Z: intervention rate (0= current treatment rate, 1=intervention treatment rate)
	//float TreatmentRateF(int FibrosisLevel, float Year);

	float TreatmentDurationAcute, TreatmentDurationFibrosis;
	float SpontaneousClearanceAcute;// Propobability that spontaneous clearance occurs during acute phase
	float TreatmentClearanceAcute[2];// Propobability that spontaneous clearance occurs due to treatment during acute phase
	float TreatmentClearanceF[5][2][2];// Propobability that spontaneous clearance occurs due to treatment
	// [X][Y][Z]
	//X: 0-4 indicates fibrosis stages F0-F4
	//Y: indicates HCV genotype (type1=1, non type 1=0)
	//Z: modern treatment (0= current treatment, 1=new treatment)

	float RecentDiagnosisDist[100][2];//Early diagnosis age distribution, used for optimisation
	float TotalDiagnosisDist[100][2];//Total diagnosis age distribution, used for optimisation
	float TotalInDistribution[2];//Total number in the TotalDiagnosisDist, by gender
	float OptimisedDiagnosisRate;//yearly probability of diagnosis
	float DiagnosisRateBySex[2];//yearly probability of diagnosis, kept but not used in calculations

	float OptimisedDiagnosisProportion;//the proportion of individuals infected who are diagnosed before self clearing
	float DiagnosisProportionBySex[2];//the proportion of individuals infected who are diagnosed before self clearing, kept but not used in calculations



	//Rates of taking up and stopping injecting drug use (IDU)
	//float MeanTimeOnIDU;
	//float TimeOnIDUPlusMinus;//give the interquartile range of time individual

	//Population statistics
	int NumberOfIDUs;
	int NumberOfNewInfectionsPerYear;//different
	float IDUExitRate;
	float TotalNewIDUsPerYear[2];//Male and female rates of new IDUs per year
	float IDUStartingDist[100];//an age based distribution
	float IDUTotalDist[100];//an age based distribution
	float AgeOfNewIDU[10000];//a stored vector to randomly select from when trying to add a new individual to the IDU population


	//Functions
	float YearsUntilEvent (float ProbabilityOfEvent);
	float YearOfTreatment (int FibrosisLevel, float CurrentYear, int HCVGenotype);
	float DetermineAgeAtDeathGeneral(int SexValue, float StartAge);
	int CurrentlyIntervention(float Year);
	//int SetTestingProbability(float AcuteRate[2], float FibrosisRate[5][2]);
	int SetTestingProbability(float YearlyProbabilityOfTest);
	void LoadDiagnosisDistributions(void);
	void LoadIDUDistributions(float IDUPopulationSize);
	void CreateStartHCVAgeVector(float* InfectionAgeVector, int N, int Sex);
	//void LoadIDUStartDistributions(void);
	float ChooseNewIDUAge(void);
	float DurationOfIDU(void);
	float TimeUntilIDUMortality(void);
	float DetermineYearOfDiagnosis(float CurrentYear, int FibrosisLevel);
	float DetermineTreatmentDuration(int HCVStage);



	//void LoadGeneralPopulationMortality(void);
};

float ParameterClass::YearsUntilEvent (float ProbabilityOfEvent) {
	//determines time in years until an event occurring based on a yearly probability of the event occuring
	float Years, RandomValue;
	RandomValue=(float)rand()/(float)RAND_MAX;
	//we will need to ensure that a value of 1 doesn't kill the logarithm function and cause an error
	if (RandomValue==1)
		return 1000000;
	Years=log(1-RandomValue)/log(1-ProbabilityOfEvent);
	return Years;
}

float ParameterClass::YearOfTreatment (int FibrosisLevel, float CurrentYear, int HCVGenotype)
{
	float YearOfTreatmentStart;
	if (CurrentYear<InterventionYearStart)// || CurrentYear>InterventionYearStop)
	{
		if (rand01()<TreatmentRateF[FibrosisLevel][HCVGenotype][0])
		{
			return CurrentYear;
		}
		else //try again in intervention year
		{
			if (rand01()<TreatmentRateF[FibrosisLevel][HCVGenotype][1])
			{
				return InterventionYearStart;
			}
		}

	}
	else if (CurrentYear<InterventionYearStop)
	{
		if (rand01()<TreatmentRateF[FibrosisLevel][HCVGenotype][1])
		{
			return CurrentYear;
		}
	}
	else //(CurrentYear>InterventionYearStop)
	{
		if (rand01()<TreatmentRateF[FibrosisLevel][HCVGenotype][0])
		{
		return CurrentYear;
		}
	}


	return -1;//no treatment occurred

	// Note the function below is currently unused as we are using probability-of-starting-treatment-when-changing-fibrosis-level-model
	//float YearOfTreatmentStart;
	//if (CurrentYear<InterventionYearStart)
	//{
	//	YearOfTreatmentStart=YearsUntilEvent (TreatmentRateF[FibrosisLevel][HCVGenotype][0])+CurrentYear;
	//	if (YearOfTreatmentStart<InterventionYearStart)
	//	{
	//		return YearOfTreatmentStart;
	//	}
	//	else
	//	{
	//		//In the next step we'll try from the intervention start year
	//		CurrentYear=InterventionYearStart;
	//	}
	//}

	//if (CurrentYear<InterventionYearStop)
	//{
	//	YearOfTreatmentStart=YearsUntilEvent (TreatmentRateF[FibrosisLevel][HCVGenotype][1])+CurrentYear;
	//	if (YearOfTreatmentStart<InterventionYearStop)
	//	{
	//		return YearOfTreatmentStart;
	//	}
	//	else
	//	{
	//		//In the next step we'll try from the intervention start year
	//		CurrentYear=InterventionYearStop;
	//	}
	//}

	//YearOfTreatmentStart=YearsUntilEvent (TreatmentRateF[FibrosisLevel][HCVGenotype][0])+CurrentYear;
	//return YearOfTreatmentStart;
}

float ParameterClass::DetermineAgeAtDeathGeneral(int SexValue, float StartAge)//sex male=0, female=1
{
	//Tested, works well.
	float PredictedAgeAtDeath;
	int i=0;
	int AgeBandChosen=NumberOfAgeGroups-1;
	bool DeathOccurred=0;
	while (i<NumberOfAgeGroups-1)
	{
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

int ParameterClass::CurrentlyIntervention(float Year)
{
	if (Year>=InterventionYearStart && Year<InterventionYearStop)
		return 1;
	else
		return 0;
}

int ParameterClass::SetTestingProbability(float YearlyProbabilityOfTest)//mainly used for testing,
{
	//is an example of what an optimisation technique would look like
	//Inputs necessary include (FibrosisDiagnosisProbabilityF[0][0], TestingMultiplier[1:4], InterventionRateIncrease

	//AcuteDiagnosisProbability[0]=0.15*0.3;//Symptomatic virus in 10-15% of HCV infections source: Acute hepatitis C; Anurag Maheshwari, Stuart Ray, Paul J Thuluvath
	AcuteDiagnosisProbability[0]=0.000000000000001;//As the probability of testing during the acute stage is extremely low with a flat yearly probability of testing, set to zero
	AcuteDiagnosisProbability[1]=0.000000000000001;//As the probability of testing during the acute stage is extremely low with a flat yearly probability of testing, set to zero

	//assume 30% of symptomatic cases are diagnosed
	//AcuteDiagnosisProbability[1]=AcuteDiagnosisProbability[0];//assume intervention has little impact on acute diagnosis (my strong belief), may change in future
	//float TestingMultiplier[4] = { 1.1, 1.1, 1.1, 1.1}; //TestingMultiplier is some value >1 which indicates the difference in probability between detection at the last fibrosis stage and the current one
	//FibrosisDiagnosisProbabilityF[0][0]=0.1;
	//FibrosisDiagnosisProbabilityF[1][0]=TestingMultiplier[0]*FibrosisDiagnosisProbabilityF[0][0];
	//FibrosisDiagnosisProbabilityF[2][0]=TestingMultiplier[1]*FibrosisDiagnosisProbabilityF[1][0];
	//FibrosisDiagnosisProbabilityF[3][0]=TestingMultiplier[2]*FibrosisDiagnosisProbabilityF[2][0];
	//FibrosisDiagnosisProbabilityF[4][0]=TestingMultiplier[3]*FibrosisDiagnosisProbabilityF[3][0];

	FibrosisDiagnosisProbabilityF[0][0]=YearlyProbabilityOfTest;
	FibrosisDiagnosisProbabilityF[1][0]=YearlyProbabilityOfTest;
	FibrosisDiagnosisProbabilityF[2][0]=YearlyProbabilityOfTest;
	FibrosisDiagnosisProbabilityF[3][0]=YearlyProbabilityOfTest;
	FibrosisDiagnosisProbabilityF[4][0]=YearlyProbabilityOfTest;




	float InterventionRateIncrease=2.0;

	for (int i=0; i<5; i++)
	{
		FibrosisDiagnosisProbabilityF[i][1]=1-(1-FibrosisDiagnosisProbabilityF[i][0])*exp(InterventionRateIncrease);
		//The justification for the above equation can be found in the document "Determining probabilty and rate change formula"
	}
	return 0;
}



//float ParameterClass::AcuteDiagnosisProbability(float Year)
//{
//	if (Year>InterventionYearStart && Year<InterventionYearStop)
//		return AcuteDiagnosisProbabilityValue[1];
//	else
//		return AcuteDiagnosisProbabilityValue[0];
//}
//
//float ParameterClass::TreatmentRateAcute(float Year)
//{
//	if (Year>InterventionYearStart && Year<InterventionYearStop)
//		return TreatmentRateValueAcute[1];
//	else
//		return TreatmentRateValueAcute[0];
//}
//
//float ParameterClass::FibrosisDiagnosisProbabilityF(float Year)
//{
//	if (Year>InterventionYearStart && Year<InterventionYearStop)
//		return FibrosisDiagnosisProbabilityValueF[FibrosisLevel][1];
//	else
//		return FibrosisDiagnosisProbabilityValueF[FibrosisLevel][0];
//}
//
//float ParameterClass::TreatmentRateF(int FibrosisLevel, float Year)
//{
//	if (Year>InterventionYearStart && Year<InterventionYearStop)
//		return TreatmentRateValueF[FibrosisLevel][1];
//	else
//		return TreatmentRateValueF[FibrosisLevel][0];
//}



//-----------------------------------------------------------------------


int ParameterSetup(ParameterClass& p)
{
	p.LoadDiagnosisDistributions();

	p.InterventionYearStart=3000;//begins 2012
	p.InterventionYearStop=4000;//ends beginning 2020

	p.AcuteInfectionDuration=7.5/52;//approximately 7.5 weeks (range 2-26) source: Hepatitis C: the clinical spectrum of the disease Patrick Marcellin

	//Yearly probability of progression
	//Varies by IDU status where
	//0 : not IDU
	//1 : occasional IDU
	//2 : regular IDU
	p.F0toF1[0]=0.106;
	p.F1toF2[0]=0.074;
	p.F2toF3[0]=0.106;
	p.F3toF4[0]=0.105;

	p.F0toF1[1]=0.116;
	p.F1toF2[1]=0.085;
	p.F2toF3[1]=0.085;
	p.F3toF4[1]=0.130;
	//regular IDUs have the same progression rate as occasional IDU
	p.F0toF1[2]=0.116;
	p.F1toF2[2]=0.085;
	p.F2toF3[2]=0.085;
	p.F3toF4[2]=0.130;

	p.F4toLiverFailure=0.055;//0.037 in the report referes to a 'calibrated value' used in the report. 0.055 is the proper calibrated value
	p.F4toHCC=0.031;//0.010 in the report referes to a 'calibrated value' used in the report. 0.031 is the proper calibrated value
	p.LiverFailureToHCC=0.068;

	p.TranslplantForLiverFailure=0.033;//rate of transplant
	p.TranslplantForHCC=0.1;

	//Rates of mortality
	//Read from file
	std::string FileName;
	FileName = "AverageAustralianMortality.csv";

	int a;
	int MaxArraySizeX=2;
	int MaxArraySizeY=p.NumberOfAgeGroups;
	float** Output = new float*[MaxArraySizeX];
	for(int i = 0; i < MaxArraySizeX; i++)
		Output[i] = new float[MaxArraySizeY];
	//Read the age bands
		a=csvread(FileName, Output, 0, 1, 2, p.NumberOfAgeGroups+1);
		for (int i=0; i<MaxArraySizeY; i++)
		{
			for (int j=0; j<MaxArraySizeX; j++)
			{
				p.GeneralPopulationMortalityRateBand[j][i]=Output[j][i];
			}
		}

	// Read the age band rates
		a=csvread(FileName, Output, 2, 3, 2, p.NumberOfAgeGroups+1);
		for (int i=0; i<MaxArraySizeY; i++)
		{
			for (int j=0; j<MaxArraySizeX; j++)
			{
				p.GeneralPopulationMortalityRate[j][i]=Output[j][i]/1000;
			}
		}
		delete Output;

	p.LiverFailureRelatedMortality=0.138;
	p.HCCRelatedMortality=0.605;

	p.FirstYearTransplantMortality=0.169;
	p.SubsequentYearTransplantMortality=0.034;
	p.IDUDrugUseMortality=0.0083;// from HCV report


	//Probability of being diagnosed
	std::cout<<"\nThe following line should be deleted and eventually set in the SetTestingProbability function";
	p.AcuteDiagnosisProbability[0]=0;//As the probability of testing during the acute stage is extremely low with a flat yerly probability of testing, set to zero
	p.AcuteDiagnosisProbability[1]=0;//As the probability of testing during the acute stage is extremely low with a flat yerly probability of testing, set to zero
	//float FibrosisDiagnosisProbability[5];

	//Treatment rates
	//p.TreatmentRateValueAcute[2];//TreatmentRateAcute[X]
	p.TreatmentRateAcute[1]=0.7;//pre-intervention, genotype 1
	std::cout<<"\nDon't know treatment rate for genotype non-1 in acute phase. Set at at least f0 levels of efficacy";
	p.TreatmentRateAcute[0]=0.84;//pre-intervention, genotype non-1
	std::cout<<"\nChoose an intervention treatment rate greater than currently occurs";
	p.TreatmentRateAcute[1]=0.7+0.2;//post intervention
	//X: intervention rate (0= current treatment rate, 1=intervention treatment rate)

	//Pre-intervention rates
	//genotype non-1
	p.TreatmentRateF[0][0][0]=0.02;
	p.TreatmentRateF[1][0][0]=0.02;
	p.TreatmentRateF[2][0][0]=0.02;
	p.TreatmentRateF[3][0][0]=0.02;//these rates should be appreciably higher
	p.TreatmentRateF[4][0][0]=0.02;
	//genotype 1
	p.TreatmentRateF[0][0][1]=0.02;
	p.TreatmentRateF[1][0][1]=0.02;
	p.TreatmentRateF[2][0][1]=0.02;
	p.TreatmentRateF[3][0][1]=0.02;
	p.TreatmentRateF[4][0][1]=0.02;

	//Intervention rates
	//genotype non-1
	p.TreatmentRateF[0][0][0]=0.02*2;
	p.TreatmentRateF[1][0][0]=0.02*2;
	p.TreatmentRateF[2][0][0]=0.02*2;
	p.TreatmentRateF[3][0][0]=0.02*2;
	p.TreatmentRateF[4][0][0]=0.02*2;
	//genotype 1
	p.TreatmentRateF[0][0][1]=0.02*4;
	p.TreatmentRateF[1][0][1]=0.02*4;
	p.TreatmentRateF[2][0][1]=0.02*4;
	p.TreatmentRateF[3][0][1]=0.02*4;
	p.TreatmentRateF[4][0][1]=0.02*4;


	//p.TreatmentRateValueF[5][2];//TreatmentRateF[X][Y]
	//X: 0-4 indicates fibrosis stages F0-F4
	//Y: intervention rate (0= current treatment rate, 1=intervention treatment rate)


	p.TreatmentDurationAcute=0.46;//Years
	p.TreatmentDurationFibrosis=0.69;//years
	p.SpontaneousClearanceAcute=0.25;// Propobability that spontaneous clearance occurs during acute phase
	p.TreatmentClearanceAcute[0]=0.70;// Propobability that clearance occurs due to treatment during acute phase
	std::cout<<"\nWe don't know this value, but we assume >0.84 effective";
	//p.TreatmentClearanceAcute[1]=0.90;//don't know this value, but we assume >0.84 effective

	p.TreatmentClearanceF[0][0][0]=0.84;//F0, genotype non-1, old treatment
	p.TreatmentClearanceF[1][0][0]=0.84;//F1, genotype non-1, old treatment
	p.TreatmentClearanceF[2][0][0]=0.84;//F2, genotype non-1, old treatment
	p.TreatmentClearanceF[3][0][0]=0.74;//F3, genotype non-1, old treatment
	p.TreatmentClearanceF[4][0][0]=0.74;//F4, genotype non-1, old treatment

	p.TreatmentClearanceF[0][1][0]=0.57;//F0, genotype 1, old treatment
	p.TreatmentClearanceF[1][1][0]=0.57;//F1, genotype 1, old treatment
	p.TreatmentClearanceF[2][1][0]=0.57;//F2, genotype 1, old treatment
	p.TreatmentClearanceF[3][1][0]=0.41;//F3, genotype 1, old treatment
	p.TreatmentClearanceF[4][1][0]=0.41;//F4, genotype 1, old treatment

	//all p.TreatmentClearanceF[*][*][1] treatment levels are going to be in some way related to p.TreatmentClearanceF[*][*][0] levels


	//IDU population parameters
	p.IDUExitRate=0.1729;//Rate is established in 'Calculating an entry rate into the IDU population.xlsx'  based on smothed population data based on the ANSPS report.
	//float TotalNewIDUsPerYear[2];//Male and female rates of new IDUs per year
	//float NewIDUDistribution[100];//an age based random distribution

	return 0;
}


void ParameterClass::LoadDiagnosisDistributions(void)
{
	//Loads the diagnosis distributions that are used in the optimisation of the rate of diagnosis
	int MaxArraySizeX=2;
	int MaxArraySizeY=100;
	float** Output = new float*[MaxArraySizeX];
	for(int i = 0; i < MaxArraySizeX; i++)
		Output[i] = new float[MaxArraySizeY];
	//Read the file
	csvread("DiagnosisDistributions.csv", Output, 3, 4, 2, 101);
	for (int i=0; i<MaxArraySizeY; i++)
	{
		std::cout<<"\n"<<i<<':';
		for (int j=0; j<MaxArraySizeX; j++)
		{
			RecentDiagnosisDist[i][j]=Output[j][i];
			std::cout<<" "<<RecentDiagnosisDist[i][j];
		}
	}
	char buffer;
	std::cin>>buffer;
	csvread("DiagnosisDistributions.csv", Output, 1, 2, 2, 101);
	for (int i=0; i<MaxArraySizeY; i++)
	{
		std::cout<<"\n"<<i<<':';
		for (int j=0; j<MaxArraySizeX; j++)
		{
			TotalDiagnosisDist[i][j]=Output[j][i];
			std::cout<<" "<<TotalDiagnosisDist[i][j];
		}
	}
	std::cin>>buffer;
	//Find the total number in the distribution of all diagnosed
	for (int SexValue=0; SexValue<2; SexValue++)
	{
		TotalInDistribution[SexValue]=0;
		for (int i=0; i<100; i++)
		{
			TotalInDistribution[SexValue]=TotalInDistribution[SexValue]+TotalDiagnosisDist[i][SexValue];
		}
	}
	//csvread("DiagnosisDistributions.csv", **RecentDiagnosisDist, 3, 4, 2, 101);
	//csvread("DiagnosisDistributions.csv", **TotalDiagnosisDist, 1, 2, 2, 101);
}

void ParameterClass::LoadIDUDistributions(float IDUPopulationSize)
{
	//Loads the diagnosis distributions that are used in the optimisation of the rate of diagnosis
	int MaxArraySizeX=1;
	int MaxArraySizeY=100;
	float** Output = new float*[MaxArraySizeX];
	for(int i = 0; i < MaxArraySizeX; i++)
		Output[i] = new float[MaxArraySizeY];
	//Read the file
	csvread("IDUDistributions.csv", Output, 1, 1, 2, 101);
	for (int i=0; i<MaxArraySizeY; i++)
	{
		std::cout<<"\n"<<i<<':';
		for (int j=0; j<MaxArraySizeX; j++)
		{
			IDUStartingDist[i]=Output[j][i]*IDUPopulationSize;
			std::cout<<" "<<IDUStartingDist[i];
		}
	}
	char buffer;
	std::cin>>buffer;

	csvread("IDUDistributions.csv", Output, 2, 2, 2, 101);
	for (int i=0; i<MaxArraySizeY; i++)
	{
		std::cout<<"\n"<<i<<':';
		for (int j=0; j<MaxArraySizeX; j++)
		{
			IDUTotalDist[i]=Output[j][i]*IDUPopulationSize;
			std::cout<<" "<<IDUTotalDist[i];
		}
	}

	std::cin>>buffer;



}



void ParameterClass::CreateStartHCVAgeVector(float* InfectionAgeVector, int N, int Sex)
{
	//Tested, works excellently

	//Create a cumulative distribution vector
	float CD[100];
	//RecentDiagnosisDist[CurrentAge][Sex];
	CD[0]=RecentDiagnosisDist[0][Sex];
	for (int i=1; i<100; i++)
	{
		CD[i]=CD[i-1]+RecentDiagnosisDist[i][Sex];
		//std::cout<<"\n CreateStartHCVAgeVector; "<<CD[i];
	}
	//char buffer;
	//std::cin>>buffer;

	float RandomValue;
	int i;
	bool Found;
	for (int j=0; j<N; j++)
	{
		RandomValue=rand01();
		i=-1;
		Found=false;
		while (i<99 && Found==false)
		{
			i++;
			if (i==0 && RandomValue<CD[0])
			{
				//std::cout<<"\n CreateStartHCVAgeVector; "<<i;
				Found=true;
			}
			else
			{
				if (RandomValue>=CD[i-1] && RandomValue<=CD[i])
				{
					//std::cout<<"\n CreateStartHCVAgeVector; "<<i;
					Found=true;
				}
			}
		}
		if (Found==false)//if it got to the last slot without finding the point at which it can be inserted
			i=99;
		InfectionAgeVector[j]=(float)i+rand01();


	}

}


//void ParameterClass::LoadIDUStartDistributions(void)
//{
//	IDUExitRate=0.172983987;//This value was calculated in a spreadsheet called "Calculating an entry rate into the IDU population"
//
//	int MaxArraySizeX=1;
//	int MaxArraySizeY=100;
//	//float* Output = new float[MaxArraySizeY];
//	float** Output = new float*[MaxArraySizeY];
//	for(int i = 0; i < MaxArraySizeX; i++)
//		Output[i] = new float[MaxArraySizeY];
//	//Read the file
//	csvread("EstimatedIDUStartNumbers.csv", Output, 1, 1, 2, 101);
//	for (int i=0; i<MaxArraySizeY; i++)
//	{
//		//std::cout<<"\n"<<i<<':';
//		for (int j=0; j<MaxArraySizeX; j++)
//		{
//			NewIDUDistribution[i]=Output[j][i];
//		}
//	}
//
//	//Create a stored vector that call be called upon to create new individuals when requested of various ages
//
//	float NewIDUDistribution[100];
//	float AgeOfNewIDU[10000];//a stored vector to randomly select from when trying to add a new individual to the IDU population
//}

float ParameterClass::ChooseNewIDUAge(void)
{
	char buffer;
	std::cout << "\nThe function ChooseNewIDUAge is currently incomplete";
	std::cin >> buffer;
	float Age=1;


	//Choose at random from a predefined list of ages at entering IDU population




	return Age;
}


//float ParameterClass::ChooseNewTimeAsIDU(void)
//{
//	fix
//	float TimeUntilLeavingIDU=1;
//	return TimeUntilLeavingIDU;
//}


float ParameterClass::DurationOfIDU(void)
{
	return YearsUntilEvent (IDUExitRate);
}

float ParameterClass::TimeUntilIDUMortality(void)
{
	return YearsUntilEvent (IDUDrugUseMortality);
}

float ParameterClass::DetermineYearOfDiagnosis(float CurrentYear, int FibrosisLevel)//note fibrosis level is unused at this stage
{
	//DiagnosisRate[2];
	//FibrosisDiagnosisProbabilityF[FibrosisLevel][0];
	float CalculatedYearOfDiagnosis;
	if (CurrentYear<InterventionYearStart)
	{
		//std::cout<<"\n HCVClass "<<FibrosisDiagnosisProbabilityF[FibrosisLevel][0];
		CalculatedYearOfDiagnosis=YearsUntilEvent (FibrosisDiagnosisProbabilityF[FibrosisLevel][0])+CurrentYear;
		//std::cout<<"\n HCVClass "<<CalculatedYearOfDiagnosis;
		if (CalculatedYearOfDiagnosis<InterventionYearStart)
		{
			return CalculatedYearOfDiagnosis;
		}
		else
		{
			//In the next step we'll try from the intervention start year
			CurrentYear=InterventionYearStart;
		}
	}

	if (CurrentYear<InterventionYearStop)
	{
		CalculatedYearOfDiagnosis=YearsUntilEvent (FibrosisDiagnosisProbabilityF[FibrosisLevel][1])+CurrentYear;
		if (CalculatedYearOfDiagnosis<InterventionYearStop)
		{
			return CalculatedYearOfDiagnosis;
		}
		else
		{
			//In the next step we'll try from the intervention stop year
			CurrentYear=InterventionYearStop;
		}
	}

	CalculatedYearOfDiagnosis=YearsUntilEvent (FibrosisDiagnosisProbabilityF[FibrosisLevel][0])+CurrentYear;
	return CalculatedYearOfDiagnosis;

}


float ParameterClass::DetermineTreatmentDuration(int HCVStage)
{
	return TreatmentDurationFibrosis;//Note this function will become more useful in the future, giving a range of
}




//-----------------------------------------------------------------------

class PopulationDataClass {
	public:
	//static const int NoYearsOfData=14;
	static const int NumberOfAgeGroups=25;
	float ProportionGenotype1;


	float ProportionEverUse[NumberOfAgeGroups][2], ProportionRecentUse[NumberOfAgeGroups][2];

	//Initial conditions
	int NumberOfIDUs;
	int NumberOfHCV;
	int NumberOfDiagnosed;
	int NumberDiagnosedPerYear;
	int NumberTreatedPerYear;
	float DistributionOfRecentDiagnoses[100][2];
	float DistributionOfNewInfections[100][2];//The distribution of new IDUs correlates with the number of recent diagnoses of HCV







	PopulationDataClass(void);
	void ChooseNew(int SexValue);
};


PopulationDataClass::PopulationDataClass(void)
{
	ProportionGenotype1=0.55;
	NumberOfIDUs=170000;
	NumberOfHCV=102000;//60% of 170000
	NumberOfDiagnosed=71400;//70% of 102000
	NumberDiagnosedPerYear=12000;//Surveillance report
	NumberTreatedPerYear=3969;//from the surveillance report


}
