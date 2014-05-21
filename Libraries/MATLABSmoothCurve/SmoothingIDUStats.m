% Written by James Jansson, for the Kirby Institute Hepatitis C Project

clear 
clc

%Age Ranges
Ranges=[0 13;
    14 19;
    20 29;
    30 39;
    40 69;
    70 100];

%2001
ReportedIDU=[0.00001
    22200
    123900
    84200
    64200
    0.00001];


[AgeVector ReportedIDUSmoothed]=SmoothCurve(Ranges, ReportedIDU);

hold on;

%2004
ReportedIDU=[0.00001
    16400
    101100
    107300
    88500
    0.00001];


[AgeVector ReportedIDUSmoothed(2, :)]=SmoothCurve(Ranges, ReportedIDU);

hold on;

%2007
ReportedIDU=[0.00001
    12400
    77200
    121300
    118500
    0.00001];


[AgeVector ReportedIDUSmoothed(3, :)]=SmoothCurve(Ranges, ReportedIDU);