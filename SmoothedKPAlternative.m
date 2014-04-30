function [NonSurvivalProbability TimeBounds]=SmoothedKPAlternative (SurvivalTimeData, Censored)
%note time bounds start with 0 and end wtih -1 (to indicate infinity)

%Determine the time between surival points
[SurvivalTimeData, I]=sort(SurvivalTimeData);
Censored=Censored(I);
