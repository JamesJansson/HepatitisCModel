#include "stdafx.h"
#include "ProbabilityFunctions.h"
#include "EventVector.h"




class HCVClass {

    float YearOfBirth; //used in determining age based probability of death, fibrosis development

	int Sex;//male 0, female, 1



public:
	EventVector DiseaseStage;
	//-1 : empty
	//0 : not infected
	//1 : accute infection
	//2  : fibrosis level f0
	//3  : fibrosis level f1
	//4  : fibrosis level f2
	//5  : fibrosis level f3
	//6  : fibrosis level f4
	//7  : liver failure
	//8  : HCC
	//9  : liver transplant
	//10  : death

	EventVector Genotype[7];//zero is unused, 1-6 indicates genotype 1-6 infected
	//0: not infected
	//1: infecected at that point

	EventVector Diagnosed;
	//0: not diagnosed
	//1: diagnosed

	EventVector Treatment;
	//0 : not on treatment
	//1 : on treatment

	EventClass AlcoholUse;

	HCVProbabilityClass *Prob;//Some sort of pointer to a class of probabilities. This can be live updated to represent changes in the probabilities

	HCVClass(void);//Constructor class
	void Reset(void);





//------------------------------------------------------------------------------------------------------


	int StartIDU(float DateStartIDU, float InputBirthDate, int InputSex,  ParameterClass* p);
	int CleanUpMortality(void);
	bool SusceptibleIDU(float Year);
	void SetSex(int SexValue);
	void SetYearOfBirth(float YearOfBirthValue);

	float CurrentAge (float CurrentYear);
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

HCVClass::HCVClass(void)//Constructor class
{
	StepSize=0.1;
	cout<<"Warning, hard value set here"<<endl;
	Active=0;
	NextSusceptible=0;

}

void HCVClass::Reset(void)//Constructor class
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

int HCVClass::StartIDU(float DateStartIDU, float InputBirthDate, int InputSex,  ParameterClass* p)
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

int HCVClass::CleanUpMortality(void)
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

bool HCVClass::SusceptibleIDU(float Year)
{
	if (Year>NextSusceptible && Year<YearOfDeath)
	{
		return 1;
	}
	return 0;
}

float HCVClass::CurrentAge (float CurrentYear) {
	return CurrentYear-YearOfBirth;
}

float HCVClass::DetermineCurrentIDUStatus (float CurrentYear) {
	if (CurrentYear>IDUStart && CurrentYear<IDUStop)
		return 1;
	else
		return 0;
}

float HCVClass::YearsUntilEvent (float ProbabilityOfEvent) {
	//determines time in years until an event occurring based on a yearly probability of the event occuring
	float Years, RandomValue;
	RandomValue=(float)rand()/(float)RAND_MAX;
	//we will need to ensure that a value of 1 doesn't kill the logarithm function and cause an error
	if (RandomValue==1)
		return 1000000;
	Years=log(1-RandomValue)/log(1-ProbabilityOfEvent);
	return Years;
}

float HCVClass::RaceEvents (float ProbabilityOfEvent1, float ProbabilityOfEvent2, int &Winner) {
	//RaceEvents: given 2 event probabilities, determines when each is likely to happen, and chooses the one that occurs first.
	char buffer;
	std::cout << "\nFunction RaceEvents was used when you thought it was no longer used";
	std::cin >> buffer;

	float Event1Time, Event2Time;
	Event1Time=HCVClass::YearsUntilEvent (ProbabilityOfEvent1);
	Event2Time=HCVClass::YearsUntilEvent (ProbabilityOfEvent2);
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

//int HCVClass::SetNextDiseaseStage (float Date, int DiseaseCode, char AddOrSet)//Date can either be the current year for AddOrSet=s, or the number of years since the last stage with AddOrSet=a
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

//float HCVClass::MostRecentDiseaseStageDate (void)
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

//int HCVClass::CurrentDiseaseStage (float Date)
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

//int HCVClass::CurrentIDUState (float Date)
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



float HCVClass::ReturnYearOfGeneralDeath (void)
{
	return GeneralMortalityDate;
}

//int HCVClass::DeterminePatientHistory (float InfectionDate, int HCVStrain, ParameterClass* p)
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

int HCVClass::NewHCVInfection (float YearOfInfection,  int HCVGenotypeGiven, ParameterClass* p)
{
	if (HCV.Stage (YearOfInfection)>0)//if HCV.Stage returns 0, not infected in that year. If it return -1, no infections recorded
	{
		return -1;//error: infection already exists for this date
	}


	int NextDiseaseStage;
	float CurrentDiseaseStageDuration;
	float CurrentStageStart;
	float TestTimeUntilDiagnosed;
	float TestTimeUntilTreatment;
	float YearOfTreatment;
	int Intervention;
	//int TreatmentAttempted=0;
	int TreatmentSuccessful=-1;//-1 means unknown, 0 means no, 1 means yes
	int CurrentlyDiagnosed=0;//0 for undiagnosed for this infection round
	int CurrentIDUStatus;
	float DiagnosedThisStep;//indicates if the individual was diagnosed during the current disease stage
	float YearOfDiagnosis;
	float TreatmentDuration;



//Acute-----------------------------------------------------------------------------------------------------------
	HCV.Set(YearOfInfection, AcuteInfection);
	HCVGenotype.Set(YearOfInfection, HCVGenotypeGiven);

	NextDiseaseStage=FibrosisLevelF0;

	Intervention=p->CurrentlyIntervention(CurrentStageStart);
	//Determining if diagnosed in acute stage
	if (rand01()<p->AcuteDiagnosisProbability[Intervention])//Determine if diagnosis occurs during acute stage
	{
		//std::cout<<"\n Diagnosed in acute stage!";
		CurrentlyDiagnosed=1;
		if (rand01()<p->TreatmentRateAcute[Intervention])//Determine if treatment occurs
		{
			//TreatmentAttempted=1;
			if (rand01()<p->TreatmentClearanceAcute[Intervention])//Determine if treatment successful
			{
				NextDiseaseStage=NotInfected;
				TreatmentSuccessful=1;//treatment was a success in this individual
			}
			else
			{
				TreatmentSuccessful=0;//treatment was a failure in this individual
			}
		}
	}
	else // undiagnosed scenario
	{
		//std::cout<<"\n Not diagnosed in acute stage!";
		//Determine if spontaneous clearance during acute phase occurs
		if (rand01()<p->SpontaneousClearanceAcute)
		{
			NextDiseaseStage=NotInfected;
			HCV.Add(p->AcuteInfectionDuration, NextDiseaseStage);
			return 0;
		}
		else
		{
			NextDiseaseStage=FibrosisLevelF0;
			HCV.Add(p->AcuteInfectionDuration, NextDiseaseStage);
		}
	}
	//Determine duration of acute infection
	//
	//if (NextDiseaseStage==NotInfected)//escape function if clearance occurs
	//{
	//	SetNextDiseaseStage (10000, NotInfected, 'a');//set a really big number for not being infected
	//	return 0;
	//}


//Check each of the fibrosis stages------------------------------------------------------------------------------
	for (int f=0; f<5; f++)
	{
		DiagnosedThisStep=0;
		CurrentStageStart=HCV.MostRecentDate();      //    DiseaseStageTime[MostRecentSlot];
		CurrentIDUStatus=DetermineCurrentIDUStatus(CurrentStageStart);

		if (f==0)
		{
		    //Years Until event have been moved to the probabilityfunctions header
			CurrentDiseaseStageDuration=YearsUntilEvent (p->F0toF1[CurrentIDUStatus]);
			NextDiseaseStage=FibrosisLevelF1;
		}
		if (f==1)
		{
			CurrentDiseaseStageDuration=YearsUntilEvent (p->F1toF2[CurrentIDUStatus]);
			NextDiseaseStage=FibrosisLevelF2;
		}
		if (f==2)
		{
			CurrentDiseaseStageDuration=YearsUntilEvent (p->F2toF3[CurrentIDUStatus]);
			NextDiseaseStage=FibrosisLevelF3;
		}
		if (f==3)
		{
			CurrentDiseaseStageDuration=YearsUntilEvent (p->F3toF4[CurrentIDUStatus]);
			NextDiseaseStage=FibrosisLevelF4;
		}
		if (f==4)
		{
			//race between HCC and liver failure
			float TimeUntilHCC=YearsUntilEvent (p->F4toHCC);
			float TimeUntilLiverFailure=YearsUntilEvent (p->F4toLiverFailure);
			if (TimeUntilLiverFailure<TimeUntilHCC)
			{
				CurrentDiseaseStageDuration=TimeUntilLiverFailure;
				NextDiseaseStage=LiverFailure;
			}
			else
			{
				CurrentDiseaseStageDuration=TimeUntilHCC;
				NextDiseaseStage=HCC;
			}

		}


		float CurrentDiseaseStageStartYear=HCV.MostRecentDate();
		float TreatmentPossibleFromYear=CurrentDiseaseStageStartYear;//Note this date is increased if the person becomes diagnosed in the next step
		if (CurrentlyDiagnosed==0)
		{
			//Determine what happens first, diagnosis or disease advancement//race events
			YearOfDiagnosis=p->DetermineYearOfDiagnosis(CurrentDiseaseStageStartYear, f);
			TestTimeUntilDiagnosed=YearOfDiagnosis-CurrentDiseaseStageStartYear;

			//std::cout<<"\n HCVClass "<<YearOfDiagnosis<<" "<<TestTimeUntilDiagnosed<<" "<<CurrentDiseaseStageDuration;
			//if disease advancement occurs fist, move to next stage of fibrosis
			if (CurrentDiseaseStageDuration<TestTimeUntilDiagnosed)
			{
				//Advance to the next disease stage without diagnosis
				HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
				//Currently diagnosed remains =0
			}
			else//if diagnosis occurs first,
			{
				CurrentlyDiagnosed=1;
				//Set the diagnosis year
				HCVDiagnosis.Set(YearOfDiagnosis, 1);
				DiagnosedThisStep=1;
				//TreatmentPossibleFromYear=YearOfDiagnosis;
				//TreatmentSuccessful=-1;
			}
		}
		//For individuals currently diagnosed but not on treatment
		if (CurrentlyDiagnosed==1)//note TreatmentSuccessful==-1 was removed because we want people to have the chance fo
		{
			//Determine if diagnosed in this stage or in a previous one
			if (DiagnosedThisStep==1)
			{
				TreatmentPossibleFromYear=YearOfDiagnosis;
			}
			else
			{
				TreatmentPossibleFromYear=CurrentDiseaseStageStartYear;
			}

			//determine if treatment occurs before movement on to next stage or not during this stage
			YearOfTreatment=p->YearOfTreatment (f, TreatmentPossibleFromYear, HCVGenotypeGiven);//(int FibrosisLevel, float CurrentYear, int HCVGenotype);
			if (YearOfTreatment>=0)//YearOfTreatment will be -1 if no treatment occurs
			{
				if (YearOfTreatment<CurrentDiseaseStageStartYear+CurrentDiseaseStageDuration)//if treatment occurs before the next diagnosis
				{
					//Create treatment record and determine treatment duration
					Treatment.Set(YearOfTreatment, 1);//Indicate treatment started
					TreatmentDuration=p->DetermineTreatmentDuration(f);
					Treatment.Set(YearOfTreatment+TreatmentDuration, 0);//Indicate treatment stopped

					//Determine if treatment successful
					Intervention=p->CurrentlyIntervention(YearOfTreatment);
					if (rand01()<p->TreatmentClearanceF[f][HCVGenotypeGiven][Intervention])//treatment successful
					{
						NextDiseaseStage=NotInfected;
						HCV.Set(YearOfTreatment+TreatmentDuration, NotInfected);
						HCVDiagnosis.Set(YearOfTreatment+TreatmentDuration, 0);
						TreatmentSuccessful=1;//treatment was a success in this individual
						return 0;
					}
					else
					{
						//TreatmentSuccessful=0;//treatment was a failure in this individual treatment success is not considered in this model
						HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
					}
				}
				else //if treatment occurs after the next stage, simply push on to the next stage
				{
					HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
				}
			}
			else//if no treatment occurs, simply push on to the next stage
			{
				HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
			}

		}



		////if not currently diagnosed
		//if (CurrentlyDiagnosed==0)
		//{
		//	//Determine what happens first, diagnosis or disease advancement//race events
		//	//Intervention=p->CurrentlyIntervention(CurrentStageStart);
		//	float CurrentDiseaseStageStartYear=HCV.MostRecentDate();
		//	YearOfDiagnosis=p->YearOfDiagnosis(CurrentDiseaseStartYear, f);
		//	TestTimeUntilDiagnosed=YearOfDiagnosis-CurrentDiseaseStageStartYear;
		//	//if disease advancement occurs fist, move to next stage of fibrosis
		//	if (CurrentDiseaseStageDuration<TestTimeUntilDiagnosed)
		//	{
		//		//Advance to the next disease stage without diagnosis
		//		HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
		//	}
		//	else//if diagnosis occurs first,
		//	{
		//		//Set the diagnosis year
		//		Diagnosis.Set(YearOfDiagnosis, 1);
		//
		//		//determine if treatment occurs before movement on to next stage or not during this stage
		//		YearOfTreatment=p->YearOfTreatment (f, YearOfDiagnosis, HCVGenotypeGiven);//(int FibrosisLevel, float CurrentYear, int HCVGenotype);
		//		if (YearOfTreatment>=0)//YearOfTreatment will be -1 if no treatment occurs
		//		{
		//			if (YearOfTreatment<CurrentDiseaseStageStartYear+CurrentDiseaseStageDuration)//if treatment occurs before the next diagnosis
		//			{
		//				//Create treatment record and determine treatment duration
		//				Treatment.Set(YearOfTreatment, 1);//Indicate treatment started
		//				TreatmentDuration=p->DetermineTreatmentDuration(void);
		//				Treatment.Set(YearOfTreatment+TreatmentDuration, 0);//Indicate treatment stopped
		//
		//				//Determine if treatment successful
		//				Intervention=p->CurrentlyIntervention(YearOfTreatment);
		//				if (rand01()<p->TreatmentClearanceF[f][HCVStrain][Intervention])//treatment successful
		//				{
		//					NextDiseaseStage=NotInfected;
		//					HCV.Set(YearOfTreatment+TreatmentDuration, NotInfected);
		//					Diagnosis.Set(YearOfTreatment+TreatmentDuration, 0);
		//					TreatmentSuccessful=1;//treatment was a success in this individual
		//					return 0;
		//				}
		//				else
		//				{
		//					TreatmentSuccessful=0;//treatment was a failure in this individual
		//					HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
		//				}
		//			}
		//		}
		//	}
		//}
		//else if (CurrentlyDiagnosed==1 && TreatmentSuccessful==-1)//if currently diagnosed && if (TreatmentSuccessful==-1); only try treatment if treatment success is unknown
		//{
		//	float CurrentDiseaseStageStartYear=HCV.MostRecentDate();
		//	YearOfTreatment=p->YearOfTreatment (f, CurrentDiseaseStageStartYear, HCVGenotypeGiven);//(int FibrosisLevel, float CurrentYear, int HCVGenotype);
		//	if (YearOfTreatment>=0)//YearOfTreatment will be -1 if no treatment occurs
		//	{
		//		if (YearOfTreatment<CurrentDiseaseStageStartYear+CurrentDiseaseStageDuration)//if treatment occurs before the next diagnosis
		//		{
		//			//Create treatment record and determine treatment duration
		//			Treatment.Set(YearOfTreatment, 1);//Indicate treatment started
		//			TreatmentDuration=p->DetermineTreatmentDuration(void);
		//			Treatment.Set(YearOfTreatment+TreatmentDuration, 0);//Indicate treatment stopped
		//
		//			//Determine if treatment successful
		//			Intervention=p->CurrentlyIntervention(YearOfTreatment);
		//			if (rand01()<p->TreatmentClearanceF[f][HCVStrain][Intervention])//treatment successful
		//			{
		//				NextDiseaseStage=NotInfected;
		//				HCV.Set(YearOfTreatment+TreatmentDuration, NotInfected);
		//				Diagnosis.Set(YearOfTreatment+TreatmentDuration, 0);
		//				TreatmentSuccessful=1;//treatment was a success in this individual
		//				return 0;
		//			}
		//			else
		//			{
		//				TreatmentSuccessful=0;//treatment was a failure in this individual
		//				HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
		//			}
		//		}
		//	}






			//float CurrentDiseaseYear=HCV.MostRecentDate();
			////determine if treatment occurs before movement on to next stage or not during this stage
			//YearOfTreatment=p->YearOfTreatment (f, CurrentDiseaseYear, HCVGenotypeGiven);//(int FibrosisLevel, float CurrentYear, int HCVGenotype);
			//if (YearOfTreatment>=0 && TestTimeUntilTreatment<CurrentDiseaseStageDuration )//YearOfTreatment will be -1 if no treatment occurs//if treatment occurs before the next diagnosis
			//{
			//	//Create treatment record and determine treatment duration
			//	Treatment.Set(YearOfTreatment, 1);//Indicate treatment started
			//	TreatmentDuration=p->DetermineTreatmentDuration(void);
			//	Treatment.Set(YearOfTreatment+TreatmentDuration, 0);//Indicate treatment stopped
			//
			//	//Determine if treatment successful
			//	Intervention=p->CurrentlyIntervention(YearOfTreatment);
			//	if (rand01()<p->TreatmentClearanceF[f][HCVStrain][Intervention])//treatment successful
			//	{
			//		NextDiseaseStage=NotInfected;
			//		SetNextDiseaseStage (TestTimeUntilTreatment, NextDiseaseStage, 'a');
			//		HCV.Set(YearOfTreatment+TreatmentDuration, NotInfected);
			//		Diagnosis.Set(YearOfTreatment+TreatmentDuration, 0);
			//		TreatmentSuccessful=1;//treatment was a success in this individual
			//		return 0;
			//	}
			//	else
			//	{
			//		TreatmentSuccessful=0;//treatment was a failure in this individual
			//		HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
			//	}
			//}






			////determine if treatment occurs in this stage

			//Intervention=p->CurrentlyIntervention(CurrentStageStart);
			//TestTimeUntilTreatment=YearsUntilEvent (p->TreatmentRateF[f][Intervention]);
			//if (rand01()<p->TreatmentRateF[f][Intervention])//Determine if treatment occurs
			//{
			//	//TreatmentAttempted=1;
			//	if (rand01()<p->TreatmentClearanceF[f][HCVStrain][Intervention])//Determine if treatment successful
			//	{
			//		SetNextDiseaseStage (TestTimeUntilTreatment, NextDiseaseStage, 'a');
			//		NextDiseaseStage=NotInfected;
			//		TreatmentSuccessful=1;//treatment was a success in this individual
			//	}
			//	else
			//	{
			//		TreatmentSuccessful=0;//treatment was a failure in this individual
			//		SetNextDiseaseStage (CurrentDiseaseStageDuration, NextDiseaseStage, 'a');
			//	}
			//}


		//}

	}

	//the patient could get through all 5 stages of fibrosis without diagnosis, but after that they must become diagnosed
	if (CurrentlyDiagnosed==0)
	{
		float CurrentDiseaseStageStartYear=HCV.MostRecentDate();
		CurrentlyDiagnosed=1;
		//Set the diagnosis year
		HCVDiagnosis.Set(CurrentDiseaseStageStartYear, 1);
	}



	float TimeUntilHCC;
	float TimeUntilTransplant;
	float TimeUntilLiverMortality;
	if (NextDiseaseStage==LiverFailure)
	{
		//Determine time until HCC
		TimeUntilHCC=YearsUntilEvent (p->LiverFailureToHCC);
		//Determine time until transplant
		TimeUntilTransplant=YearsUntilEvent (p->TranslplantForLiverFailure);
		//Determine time until related mortality.
		TimeUntilLiverMortality=YearsUntilEvent (p->LiverFailureRelatedMortality);
		//Choose the earliest of the 3
		if (TimeUntilHCC<TimeUntilTransplant)
		{
			CurrentDiseaseStageDuration=TimeUntilHCC;//these are temporarily set
			NextDiseaseStage=HCC;
		}
		else
		{
			CurrentDiseaseStageDuration=TimeUntilTransplant;//these are temporarily set
			NextDiseaseStage=LiverTransplant;
		}

		if (TimeUntilLiverMortality<CurrentDiseaseStageDuration)
		{
			CurrentDiseaseStageDuration=TimeUntilLiverMortality;
			NextDiseaseStage=Death;
			HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
			return 0;
		}

		HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
	}

	//Determine outcome of HCC
	if (NextDiseaseStage==HCC)
	{
		//Determine time until transplant
		TimeUntilTransplant=YearsUntilEvent (p->TranslplantForHCC);
		//Determine time until related mortality.
		TimeUntilLiverMortality=YearsUntilEvent (p->HCCRelatedMortality);
		//Choose the earliest of the 3
		if (TimeUntilLiverMortality<TimeUntilTransplant)
		{
			CurrentDiseaseStageDuration=TimeUntilLiverMortality;//these are temporarily set
			NextDiseaseStage=Death;
			HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
			return 0;// no more simulation can occur, so return 0
		}
		else
		{
			CurrentDiseaseStageDuration=TimeUntilTransplant;//these are temporarily set
			NextDiseaseStage=LiverTransplant;
			HCV.Add(CurrentDiseaseStageDuration, NextDiseaseStage);
		}

	}

	//liver transplant
	//determine what happens first year mortality
	float TimeTransplantMortality;
	TimeTransplantMortality=YearsUntilEvent (p->FirstYearTransplantMortality);
	if (TimeTransplantMortality<1)//if mortality happens within the year
	{
		NextDiseaseStage=Death;
		HCV.Add(TimeTransplantMortality, NextDiseaseStage);
		return 0;
	}
	//determine mortality beyond first year
	TimeTransplantMortality=1+YearsUntilEvent (p->SubsequentYearTransplantMortality);
	NextDiseaseStage=Death;
	HCV.Add(TimeTransplantMortality, NextDiseaseStage);
	return 0;

}


void HCVClass::SetNextSusceptible (float Year)
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


void HCVClass::Display (void)
{

	char buffer;
	std::cout << "\nEnter any character to continue";
	std::cin >> buffer;
}
