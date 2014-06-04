/*
This file describes the assumptions of a population of people who inject drugs (IDU).

The purpose is to get a rough estimate of when people first started injecting drugs, and how long they have been injecting drugs.

Firstly, national estimates of drug use provide information about the age rate of recent and lifetime drug use.

Almost all estimates put male use at double that of female rate, implying that males make up 66.6% of users.
This is fairly consistent across years and sub categories of IDU.

The primary variable that changes the outcome of the rates in this model is that changes in use associated with drug prices increases from 1999 onwards.


*/



int CreatePopulation
{
    //Load data files
    float MaleProp=0.666;
    float SexVariability=0.05;//Plus or minus 5% of the above

    float FinalYearOfData=2010;

    float AgeBand[]= {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
    float LifetimeUseRate[]= {0, 0, 0.001, 0.004, 0.008, 0.033, 0.042, 0.036, 0.022, 0.03, 0.017, 0.011, 0.001, 0.002, 0.002, 0.001, 0.001, 0.001, 0, 0, 0};
    float RecentUseRate[]= {0, 0, 0.001, 0.003, 0.006, 0.012, 0.011, 0.007, 0.004, 0.003, 0.002, 0.001, 0.001, 0.001, 0.001, 0, 0, 0, 0, 0, 0};
    int ABSPopulation[]= {1426921, 1376097, 1391020, 1450165, 1582281, 1604743, 1519174, 1571677, 1570445, 1536852, 1467337, 1319264, 1185593, 917596, 707328, 556809, 558341, 444032, 0, 0, 0};

    float PerAgeBandVariability=0.25;
    float TotalVariability=0.25;

    float AgeFirstIDUMean=20.1;
    float AgeFirstIDULogNormSTD=3.16;

    //total people in the recent and lifetime user bands smoothed

    return 0;
}


//int BandSmother
