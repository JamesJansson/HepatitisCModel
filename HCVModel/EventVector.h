#include <vector>
using namespace std;
//vector<int> v;         // no need to prepend std:: any more
//myvector.resize(5); change the vector size to 5
//myvector.resize(8,100); change the vecotr size to 8, fill new spots with 100s
class EventVector {

	int LastSlot;
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
	int VectorPosition (float);
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
	LastSlot=-1;
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

	LastSlot=-1;
	VectorSize=0;

}





int EventVector::Set(float Time, int EventValue)
{
    //is the last Time after the Time attempting to be set? This is an error, return -1
	if (LastSlot>=0)
    {
        if (EventTimeVector[LastSlot]>Time)
        {
            return -1;
        }
    }
	LastSlot++;
	VectorSize++;
    EventValueVector.push_back( EventValue);
    EventTimeVector.push_back( Time);
    return 0;
}

int EventVector::Set(float Time, int EventValue, bool EraseFutureEvents)// used to remove future events if, for example, the expected time of death is set but medication is given that changes the death Time
{
    if (EraseFutureEvents==true)
    {
        //Determine if there are future events
        if (LastSlot>=0)
        {
            //Find future events
            int LastPostitionLTTime=VectorPosition(Time);
            if (EventTimeVector[LastPostitionLTTime]==Time)
            {
                LastPostitionLTTime=LastPostitionLTTime-1;
            }
            if (LastPostitionLTTime<LastSlot)
            {
                //Delete events
                VectorSize=LastPostitionLTTime+1;
                EventValueVector.resize(VectorSize);
                EventTimeVector.resize(VectorSize);
                LastSlot=LastPostitionLTTime;

            }
            //else no need to delete future events
        }
    }
    return Set(Time, EventValue);//set the current event
}


int EventVector::Add(float Years, int EventValue)
{
    if (LastSlot==-1)
		return -1;//error, no value to add on to

	LastSlot++;
	VectorSize++;
    EventValueVector.push_back( EventValue);
    EventTimeVector.push_back( EventTimeVector[LastSlot-1]+Years);

	return 0;
}




float EventVector::LastTimeEntry (void)
{
    if (LastSlot>=0)
    {
        return EventTimeVector[LastSlot];
    }
    return -1;// this may become a problem if the time goes into negative time.
}

int EventVector::LastValueEntry (void)
{
    if (LastSlot>=0)
    {
        return EventValueVector[LastSlot];
    }
    return -1;// this may become a problem if the time goes into negative time.
}

int EventVector::VectorPosition (float Time)
{
    if (LastSlot==-1)
    {
        return -1;//error, nothing set as yet
    }

    //if the time is prior to the first set time
	if (Time<EventTimeVector[0])
    {
        return -1;//error, as time is prior to first step
    }

    int Slot=0;
    while (Slot<LastSlot)
    {
        //std::cout<<"While loop"<<Slot<<" "<<EventTimeVector[Slot]<<" "<<Time<<endl;
        if (EventTimeVector[Slot]<=Time && Time<EventTimeVector[Slot+1])
        {
            return Slot;
        }
        Slot++;
    }

    return LastSlot;// if it isn't any of the slots < LastSlot, it should be the LastSlot
}

int EventVector::Value (float Time)
{
    //this class is used to determine the value at the spcified time
    return EventTimeVector[VectorPosition(Time)];
}

float EventVector::Find (int ValueToFind)
{
    std::cout<<"This function is not quite complete.";
    vector<float> StartTimes;
    vector<float> EndTimes;
	int Slot=0;
	while (Slot<=LastSlot)
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
	while (Slot<=LastSlot)
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
    std::cout<<"Vector size:"<<VectorSize<<" last vector position: "<<LastSlot<<endl;
    int Slot=0;
	while (Slot<=LastSlot)
	{
		std::cout<<EventValueVector[Slot]<<' '<<EventTimeVector[Slot]<<endl;
		Slot++;
	}
	char buffer;
	std::cout << "\nEnter any character to continue";
	std::cin >> buffer;
}

