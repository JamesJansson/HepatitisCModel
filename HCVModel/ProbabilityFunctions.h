#include <math.h>
#include <stdlib.h>
float rand01(void)
{
	return ((float)rand()/(float)RAND_MAX);
}
float randrange(float Range1,float Range2)
{
	return Range1 + ((float)rand()/(float)RAND_MAX)*(Range2-Range1);
}

int randrange(int Range1,int Range2)//note at the moment it can only randomly choose between a maximum of 32000 (RAND_MAX) values
{
	return Range1 + ((float)rand()/(float)RAND_MAX)*(Range2-Range1);
}

float randnormal(float Mean,float SD)
{
	float Rand1=0, Rand2=0;

	while (Rand1==0)//to avoid log(0) errors
		Rand1=rand01();
	Rand2=rand01();
	//Use the Box-Muller tranformation
	return (pow((-2*log(Rand1)), (float) 0.5))*cos(2*3.14159*Rand2)*SD+Mean;
}

float YearsUntilEvent (float ProbabilityOfEvent) {
	//determines time in years until an event occurring based on a yearly probability of the event occuring
	float Years, RandomValue;
	RandomValue=(float)rand()/(float)RAND_MAX;
	//we will need to ensure that a value of 1 doesn't kill the logarithm function and cause an error
	if (RandomValue==1)
		return 1000000;
	Years=log(1-RandomValue)/log(1-ProbabilityOfEvent);
	return Years;
}


float RaceEvents (float ProbabilityOfEvent1, float ProbabilityOfEvent2, int &Winner) {
	//RaceEvents: given 2 event probabilities, determines when each is likely to happen, and chooses the one that occurs first.
	char buffer;
	std::cout << "\nFunction RaceEvents was used when you thought it was no longer used";
	std::cin >> buffer;

	float Event1Time, Event2Time;
	Event1Time=YearsUntilEvent (ProbabilityOfEvent1);
	Event2Time=YearsUntilEvent (ProbabilityOfEvent2);
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
