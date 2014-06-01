#include "EventVector.h"
using namespace std;

class Parameter {

    int Value;

    vector<EventVector> ParamValue;//allows a parameter value to be specified over time (that is, it changes with time)

    // Dependent on
    // Age
    // Sex
    // Alcohol status
    // IDU
    // HIV status
    // HCV status


    int Optimised;


public:
    Parameter(void);//Constructor class
    int Reset(void);
    int SetParameters(int A);


	void Display (void);
};


Parameter::Parameter(void)//Constructor class
{

	Optimised=0;
	//Load parameters

}


int Parameter::Reset(void)
{

    return 0;

}




