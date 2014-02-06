// cstdlib is included for rand() functionality
#include  <cstdlib>
// time.h is included for rand() functionality
#include <time.h>
#include <tgmath.h>

float rand01(void)
{
	return ((float)rand()/(float)RAND_MAX);
}

bool eventp(float p)//returns true if an even with probability p occurs
{
	if (((float)rand()/(float)RAND_MAX)<p)
    {
        return true;
    }
    return false;
}

float randrange(float Range1,float Range2)
{
	return Range1 + ((float)rand()/(float)RAND_MAX)*(Range2-Range1);
}

//int randrange(int Range1,int Range2)//note at the moment it can only randomly choose between a maximum of 32000 (RAND_MAX) values
//{
//	return Range1 + ((float)rand()/(float)RAND_MAX)*(Range2-Range1);
//}

int randrange(int Range1,int Range2)//note at the moment it can only randomly choose between a maximum of 32000 (RAND_MAX) values
{
	return Range1 + ((rand()*RAND_MAX+rand())%(Range2-Range1+1));
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
