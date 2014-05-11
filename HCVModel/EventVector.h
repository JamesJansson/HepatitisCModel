#include <vector>
using namespace std;
//vector<int> v;         // no need to prepend std:: any more
//myvector.resize(5); change the vector size to 5
//myvector.resize(8,100); change the vecotr size to 8, fill new spots with 100s
class EventVector {

	int MostRecentSlot;
	int VectorSize;

    vector<int> EventValueVector;
    vector<float> EventTimeVector;
	//int EventValueVector[EventVectorMaxSize];//
	//float EventTimeVector[EventVectorMaxSize];//a vector that indicates the time that the current DiseaseValue occurred at.

public:
	EventVector(void);//Constructor class
	void Reset(void);
	int Set(float Time, int EventValue);
	int Set(float Time, int EventValue, bool EraseFutureEvents);// used to remove future events if, for example, the expected time of death is set but medication is given that changes the death Time
	int Add(float Years, int EventValue);
	float LastTimeEntry (void);
	int LastValueEntry (void);
	int Value (float Time);
	float Find (int ValueToFind);
	float FindNext (int ValueToFind, float Time);
	void Display (void);
};


EventVector::EventVector(void)//Constructor class
{
    //use std::vector <int>
    //int *p;
    //p = new int[5];
    //for(int i=0;i<5;i++)
    //    *(p+i)=i;

    // realloc
    //int* temp = new int[6];
    //std::copy(p, p + 5, temp); // Suggested by comments from Nick and Bojan
    //delete [] p;
    //p = temp;
	MostRecentSlot=-1;
	VectorSize=0;
	//for (int i=0; i<EventVectorMaxSize; i++)
	//{
	//	EventValueVector[i]=-1;
	//	EventTimeVector[i]=-1;
	//}

}


void EventVector::Reset(void)//Constructor class
{
    EventValueVector.resize(0);
    EventTimeVector.resize(0);

	MostRecentSlot=-1;
	VectorSize=0;

}





int EventVector::Set(float Time, int EventValue)//Time can either be the current year for AddOrSet=s, or the number of years since the last Value with AddOrSet=a
{
	//is the last Time after the Time attempting to be set? This is an error, return -1
	if (EventTimeVector[MostRecentSlot]>Time)
    {
        return -1;
    }


	MostRecentSlot++;
	VectorSize++;
    EventValueVector.resize(VectorSize, EventValue);
    EventTimeVector.resize(VectorSize, EventValue);
    float MostRecentTime (void);
	float MostRecentValue (void);

}

int EventVector::Set(float Time, int EventValue, bool EraseFutureEvents)// used to remove future events if, for example, the expected time of death is set but medication is given that changes the death Time
{
    if (EraseFutureEvents==true)
    {
        //Determine if there are future events

        //Determine where future events start
        std::cout << "\nDelete all future events";
            std::cout << "\nFind future events";
            std::cout << "\nDelete events";
    }
    return Set(Time, EventValue);
}


int EventVector::Add(float Years, int EventValue)//Time can either be the current year for AddOrSet=s, or the number of years since the last Value with AddOrSet=a
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




float EventVector::LastTimeEntry (void)
{
    if (MostRecentSlot>=0)
    {
        return EventTimeVector[MostRecentSlot];
    }
    return -1;// this may become a problem if the time goes into negative time.
}

int EventVector::LastValueEntry (void)
{
    if (MostRecentSlot>=0)
    {
        return EventValueVector[MostRecentSlot];
    }
    return -1;// this may become a problem if the time goes into negative time.
}



int EventVector::Value (float Time)
{
	//this class is used to determine the value at the current time
	if (MostRecentSlot==-1)
	{
		return -1;//error, nothing set as yet
	}

	//if the time is prior to the first set time
	if (Time<EventTimeVector[0])
    {
        return -1;
    }

    if (MostRecentSlot==0)
    {
        if (Time>=EventTimeVector[0])
        {
            return EventTimeVector[0];
        }
    }

    //find when the next event will happen
    int Slot=0;
	while (Slot<MostRecentSlot)
	{
        if (Time>= EventTimeVector[Slot] && Time<EventTimeVector[Slot+1])
        {
            return EventValueVector[Slot];//take the left hand value
        }

        Slot++;
	}

    return EventTimeVector[MostRecentSlot];//if the time is after the most recent slot time, use that
}

float EventVector::Find (int ValueToFind)
{
    std::cout<<"This function is not quite complete.";
    vector<float> StartTimes;
    vector<float> EndTimes;
	int Slot=0;
	while (Slot<=MostRecentSlot)
	{
		if (EventValueVector[Slot]==ValueToFind)
		{
			return EventTimeVector[Slot];
		}
		Slot++;
	}
	return -1;//value not found
}

float EventVector::FindNext (int ValueToFind, float Time)
{
	//Find the next occurence of the Value ValueToFind after the Time given
	int Slot=0;
	while (Slot<=MostRecentSlot)
	{
		if (EventValueVector[Slot]==ValueToFind && EventTimeVector[Slot]>=Time)
		{
			return EventTimeVector[Slot];
		}
		Slot++;
	}
	return -1;//value not found
}






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

