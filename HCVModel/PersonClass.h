#include "EventVector.h"
//#include "transmission.h"
//#include "HCVClass.h"
//#include "mortality.h"

class PersonClass {
	bool Active;//A variable used to indicate if the slot has been used for an individual yet (true) or not (false).
    float YearOfBirth;

	//, YearOfInfection, YearOfGeneralDeath, YearOfDrugDeath, YearOfHCVDeath, YearOfTransplantDeath;
	int Sex;//male 0, female, 1
	EventVector Location;//numerical location

    MortalityClass *Mortalilty;//a pointer to a general mortality probability

	HCVClass HCV;
	HIVClass HIV;
	IDUClass IDU; //contains IDU status, network record of IDU
	//TransmissionClass SexualNetwork
	//TransmissionClass HIVInjectingNetwork
    //TransmissionClass HCVSexualNetwork



	float GeneralMortalityDate, IDUMortalityDate, HCVMortalityDate, TransplantMortalityDate, HIVMortalityDate;
	float DateOfDeath;//DateOfDeath is earliest of all the above death dates
	float NextSusceptible;//When the individual can possibly be infected next. Set to NextSusceptibleMAX if can never be infected again

public:

	PersonClass(void);//Constructor class
	void Reset(void);
	void SetSex(int SexValue);
	void SetYearOfBirth(float YearOfBirthValue);
	float CurrentAge (float CurrentYear);


//------------------------------------------------------------------------------------------------------





	int StartIDU(float DateStartIDU, float InputBirthDate, int InputSex,  ParameterClass* p);
	int CleanUpMortality(void);
	bool SusceptibleIDU(float Year);

	float DetermineCurrentIDUStatus (float CurrentYear);
	float YearsUntilEvent (float ProbabilityOfEvent);
	float RaceEvents (float ProbabilityOfEvent1, float ProbabilityOfEvent2, int &Winner);
	//int SetNextDiseaseStage (float Date, int DiseaseCode, char AddOrSet);
	float MostRecentDiseaseStageDate (void);
	int CurrentDiseaseStage (float Date);
	float ReturnYearOfGeneralDeath (void);
	int NewHCVInfection (float InfectionDate, int HCVStrain, ParameterClass* p);
	void SetNextSusceptible (float Year);
	void Display (void);

};

PersonClass::PersonClass(void)//Constructor class
{
	StepSize=0.1;
	Active=0;
	NextSusceptible=0;

}

void PersonClass::Reset(void)//Constructor class
{
	//Reset birthdate too!
	//std::cout<<"\nhey you need to reset general pop mortality too!";


	HCV.Reset();
	HCVGenotype.Reset();
	HCVDiagnosis.Reset();
	Treatment.Reset();
	Active=0;
	NextSusceptible=0;

}

int PersonClass::StartIDU(float DateStartIDU, float InputBirthDate, int InputSex,  ParameterClass* p)
{
	if (DateStartIDU<InputBirthDate)//check the date of starting use is after birth
	{
		return -1;
	}
	if (Active==1)
	{
		return -1;//can't restart a person on IDU if they are already listed as an IDU
	}

	Active=1;

	Sex=InputSex;
	YearOfBirth=InputBirthDate;
	IDUStart=DateStartIDU;
	IDUStop=DateStartIDU+p->DurationOfIDU();

	NextSusceptible=IDUStart;

	//Set the tracking variables
	HCV.Set(YearOfBirth, 0);
	HCVGenotype.Set(YearOfBirth, 0);
	HCVDiagnosis.Set(YearOfBirth, 0);
	Treatment.Set(YearOfBirth, 0);

	//Determine general population mortality
	float AgeAtGeneralMortality;
	AgeAtGeneralMortality = p->DetermineAgeAtDeathGeneral(InputSex, DateStartIDU-InputBirthDate);
	GeneralMortalityDate = InputBirthDate+AgeAtGeneralMortality;
	//Determine IDU mortality
	float TestYearOfIDUMortality;
	TestYearOfIDUMortality=DateStartIDU+p->TimeUntilIDUMortality();
	// Does IDU exit occur before mortality
	if (IDUStop<TestYearOfIDUMortality)//IDU mortality never occurs because user stops use before death
	{
		YearOfDeath=GeneralMortalityDate;
	}
	else
	{
		//Determine which occurs first, general mortality or IDU mortality
		if (GeneralMortalityDate<TestYearOfIDUMortality)//general mortality occurs first
		{
			YearOfDeath=GeneralMortalityDate;
		}
		else
		{
			YearOfDeath=TestYearOfIDUMortality;
		}
	}
	return 0;
}

int PersonClass::CleanUpMortality(void)
{

	//Determine HCV death date
	float CurrentHCVDeathDate;
	CurrentHCVDeathDate=HCV.Find(Death);
	if (CurrentHCVDeathDate>0)//catching cases where -1 indicates not found
	{
		if (CurrentHCVDeathDate<YearOfDeath)
		{
			YearOfDeath=CurrentHCVDeathDate;
		}
	}
	//HCV.Clean(Date, CodeToClearWith);
	//first one found out of line is given the code to clean with, subsequent slots are given -1 valuess

	//HCV.Clean(YearOfDeath, Death);
	//HCVGenotype.Clean(YearOfDeath, 0);//This value is problematic
	//HCVDiagnosis.Clean(YearOfDeath, 0);
	//Treatment.Clean(YearOfDeath, 0);
	return 0;
}

bool PersonClass::SusceptibleIDU(float Year)
{
	if (Year>NextSusceptible && Year<YearOfDeath)
	{
		return 1;
	}
	return 0;
}

float PersonClass::CurrentAge (float CurrentYear) {
	return CurrentYear-YearOfBirth;
}

float PersonClass::DetermineCurrentIDUStatus (float CurrentYear) {
	if (CurrentYear>IDUStart && CurrentYear<IDUStop)
		return 1;
	else
		return 0;
}

float PersonClass::YearsUntilEvent (float ProbabilityOfEvent) {
	//determines time in years until an event occurring based on a yearly probability of the event occuring
	float Years, RandomValue;
	RandomValue=(float)rand()/(float)RAND_MAX;
	//we will need to ensure that a value of 1 doesn't kill the logarithm function and cause an error
	if (RandomValue==1)
		return 1000000;
	Years=log(1-RandomValue)/log(1-ProbabilityOfEvent);
	return Years;
}

float PersonClass::RaceEvents (float ProbabilityOfEvent1, float ProbabilityOfEvent2, int &Winner) {
	//RaceEvents: given 2 event probabilities, determines when each is likely to happen, and chooses the one that occurs first.
	char buffer;
	std::cout << "\nFunction RaceEvents was used when you thought it was no longer used";
	std::cin >> buffer;

	float Event1Time, Event2Time;
	Event1Time=PersonClass::YearsUntilEvent (ProbabilityOfEvent1);
	Event2Time=PersonClass::YearsUntilEvent (ProbabilityOfEvent2);
	if (Event1Time<=Event2Time)
	{
		Winner=1;
		return Event1Time;
	}
	else
	{
		Winner=2;
		return Event2Time;
	}
}

//int PersonClass::SetNextDiseaseStage (float Date, int DiseaseCode, char AddOrSet)//Date can either be the current year for AddOrSet=s, or the number of years since the last stage with AddOrSet=a
//{
//	int Slot=0;
//	while (Slot<StandardVectorSize)
//	{
//		if (DiseaseStage[Slot]==-1)
//		{
//			if (AddOrSet=='s')//Determining if the user wants to add on to the previous entry or simply specify a date
//			{
//				if (Slot>0)
//				{
//					if (DiseaseStageTime[Slot-1]>=Date)//error check (don't allow later disease states to overlap previous ones)
//						return -2;//error has occurred
//				}
//				DiseaseStage[Slot]=DiseaseCode;
//				DiseaseStageTime[Slot]=Date;
//				MostRecentSlot=Slot;
//			}
//			else if (AddOrSet=='a' && Slot>0)//slot must be bigger than zero to ensure that there is actually something to add on to
//			{
//				DiseaseStage[Slot]=DiseaseCode;
//				DiseaseStageTime[Slot]=DiseaseStageTime[Slot-1]+Date;
//				MostRecentSlot=Slot;
//			}
//			else
//			{
//				return -2;//error, command not found or in valid range
//			}
//			return 0;
//		}
//		Slot++;
//	}
//	return -1;//error, run out of space to store disease progression
//}

//float PersonClass::MostRecentDiseaseStageDate (void)
//{
//	int Slot=0;
//	while (Slot<StandardVectorSize-1)
//	{
//		if (DiseaseStage[Slot+1]==-1)
//		{
//
//			return DiseaseStageTime[Slot];
//		}
//		Slot++;
//	}
//	return -1;//error, run out of space to store disease progression
//}

//int PersonClass::CurrentDiseaseStage (float Date)
//{
//	//this class is used to determine the disease stage at the current time
//
//	int Slot=0;
//	while (Slot<StandardVectorSize-1)
//	{
//		if (DiseaseStageTime[Slot]>= Date && (DiseaseStageTime[Slot+1]< Date || DiseaseStage[Slot+1]==-1))
//		{
//			return DiseaseStage[Slot];
//		}
//		Slot++;
//	}
//	return -1;//error, run out of space to store disease progression
//}

//int PersonClass::CurrentIDUState (float Date)
//{
//	//this class is used to determine the disease stage at the current time
//
//	int Slot=0;
//	while (Slot<StandardVectorSize-1)
//	{
//		if (IDUStatusTime[Slot]>= Date && (IDUStatusTime[Slot+1]< Date || IDUStatus[Slot+1]==-1))
//		{
//			return IDUStatus[Slot];
//		}
//		Slot++;
//	}
//	return -1;//error, run out of space to store disease progression
//}



float PersonClass::ReturnYearOfGeneralDeath (void)
{
	return GeneralMortalityDate;
}

//int PersonClass::DeterminePatientHistory (float InfectionDate, int HCVStrain, ParameterClass* p)
//{
//	YearOfBirth=1985.09;//Note that this year of birth may be set slightly differently: we may determine the age distribution of the current IDU population in an external function
//	Sex=0;
//					//std::cout<<"\nSet year of birth";
//	SetNextDiseaseStage (YearOfBirth, NotInfected, 's');//note this line may be removed in future incarnations, and placed outside this function
//					//std::cout<<"\n"<<DiseaseStage[0]<<' '<<DiseaseStage[1]<<' '<<DiseaseStage[2]<<' '<<DiseaseStage[3]<<' '<<DiseaseStage[4];
//					//std::cout<<"\n"<<DiseaseStageTime[0]<<' '<<DiseaseStageTime[1]<<' '<<DiseaseStageTime[2]<<' '<<DiseaseStageTime[3]<<' '<<DiseaseStageTime[4];
//					//std::cout<<"\nSet next disease stage birth";
//
//	//Determine movement between non-user, regular and occasional IDU states
//
//	//Determine when infected
//	//Set infection date
//	YearOfInfection=InfectionDate;
//
//
//						//std::cout<<"\nSet Acute infection";
//
//
//	//Determine natural mortality
//	if (InfectionDate>=YearOfBirth)
//		YearOfGeneralDeath=p->DetermineAgeAtDeathGeneral(Sex, InfectionDate-YearOfBirth);//determine natural mortality after infection occurs
//	else
//		return -1;//error has occurred, date of infection cannot be before date of birth
//
//
//
//
//	//Determine disease stages (including clearance)//Determine when diagnosed//Determine when treatment occurs//Determine if and when clearance occurs due to drugs
//	DetermineDiseaseProgression (HCVStrain, p);
//	//Determine IDU related mortality
//	//Liver related mortality
//	//Choose the earliest mortality out of all
//	//cut down the disease progression to the earliest death date
//
//
//	//Determine new cases created from current case
//
//
//
//
//
//	//Display();
//	return 0;
//}




void PersonClass::SetNextSusceptible (float Year)
{
	float YearOfFoundNextSusceptible;
	YearOfFoundNextSusceptible=HCV.FindNext(NotInfected, NextSusceptibleMAX);
	if (YearOfFoundNextSusceptible<0)
	{
		NextSusceptible= NextSusceptibleMAX;
	}
	else
	{
		NextSusceptible= YearOfFoundNextSusceptible;
	}
}


void PersonClass::Display (void)
{

	char buffer;
	std::cout << "\nEnter any character to continue";
	std::cin >> buffer;
}
