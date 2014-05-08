#define EventVectorMaxSize 50

class EventVector {

	int MostRecentSlot;

	int EventValueVector[EventVectorMaxSize];//
	float EventTimeVector[EventVectorMaxSize];//a vector that indicates the time that the current DiseaseStage occurred at.

public:
	EventVector(void);//Constructor class
	void Reset(void);
	int Set(float Date, int EventValue);
	int Add(float Years, int EventValue);
	float MostRecentDate (void);
	float MostRecentStage (void);
	int Stage (float Date);
	float Find (int ValueToFind);
	float FindNext (int ValueToFind, float Date);
	void Display (void);
};


EventVector::EventVector(void)//Constructor class
{
	MostRecentSlot=-1;
	for (int i=0; i<EventVectorMaxSize; i++)
	{
		EventValueVector[i]=-1;
		EventTimeVector[i]=-1;
	}

}


void EventVector::Reset(void)//Constructor class
{
	MostRecentSlot=-1;
	for (int i=0; i<EventVectorMaxSize; i++)
	{
		EventValueVector[i]=-1;
		EventTimeVector[i]=-1;
	}

}





int EventVector::Set(float Date, int EventValue)//Date can either be the current year for AddOrSet=s, or the number of years since the last stage with AddOrSet=a
{
	int Slot=0;
	while (Slot<EventVectorMaxSize)
	{
		if (EventValueVector[Slot]==-1)
		{
			if (Slot>0)
			{
				if (EventTimeVector[Slot-1]>=Date)//error check (don't allow later disease states to overlap previous ones)
					return -2;//error has occurred
			}
			EventValueVector[Slot]=EventValue;
			EventTimeVector[Slot]=Date;
			MostRecentSlot=Slot;
			return 0;
		}
		Slot++;
	}
	return -1;//error, run out of space to store disease progression
}


int EventVector::Add(float Years, int EventValue)//Date can either be the current year for AddOrSet=s, or the number of years since the last stage with AddOrSet=a
{
	if (EventValueVector[0]==-1)
		return -1;//error, no value to add on to
	int Slot=1;
	while (Slot<EventVectorMaxSize)
	{
		if (EventValueVector[Slot]==-1)
		{
			EventValueVector[Slot]=EventValue;
			EventTimeVector[Slot]=EventTimeVector[Slot-1]+Years;
			MostRecentSlot=Slot;
			return 0;
		}
		Slot++;
	}
	return -1;//error, run out of space to store disease progression
}




float EventVector::MostRecentDate (void)
{
	int Slot=0;
	while (Slot<StandardVectorSize-1)
	{
		if (EventValueVector[Slot+1]==-1)
		{

			return EventTimeVector[Slot];
		}
		Slot++;
	}
	return -1;//error, run out of space to store disease progression
}

int EventVector::Stage (float Date)
{
	//this class is used to determine the disease stage at the current time

	if (EventValueVector[0]==-1)
	{
		return -1;//error, nothing set as yet
	}

	int Slot=0;
	while (Slot<StandardVectorSize-1)
	{
		if (Date>= EventTimeVector[Slot] && (Date<EventTimeVector[Slot+1]  || EventValueVector[Slot+1]==-1))
		{
			return EventValueVector[Slot];
		}
		Slot++;
	}
	return -1;//error, run out of space to store disease progression
}

float EventVector::Find (int ValueToFind)
{
	int Slot=0;
	while (Slot<StandardVectorSize-1 && EventValueVector[Slot]!=-1)
	{
		if (EventValueVector[Slot]==ValueToFind)
		{
			return EventTimeVector[Slot];
		}
		Slot++;
	}
	return -1;//value not found
}

float EventVector::FindNext (int ValueToFind, float Date)
{
	//Find the next occurence of the stage ValueToFind after the date given
	int Slot=0;
	while (Slot<StandardVectorSize-1 && EventValueVector[Slot]!=-1)
	{
		if (EventValueVector[Slot]==ValueToFind && EventTimeVector[Slot]>=Date)
		{
			return EventTimeVector[Slot];
		}
		Slot++;
	}
	return -1;//value not found
}


//float EventVector::Clean (int ValueToSet, float CutOffTime)
//{
//	int Slot=0;
//	while (Slot<StandardVectorSize-1 && EventValueVector[Slot]!=-1)
//	{
//		if
//		if (EventValueVector[Slot]==ValueToFind))
//		{
//			return EventTimeVector[Slot];
//		}
//		Slot++;
//	}
//	return -1;//value not found
//}




void EventVector::Display (void)
{
	//Displays the current disease progression of the individual
	int i=0;
	while (EventValueVector[i]!=-1)//for (int i=0; i<10; i++)
	{
		std::cout<<"\n"<<EventValueVector[i]<<' '<<EventTimeVector[i];
		i++;
	}
	char buffer;
	std::cout << "\nEnter any character to continue";
	std::cin >> buffer;
}

