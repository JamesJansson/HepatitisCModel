function [NonSurvivalProbability TimeBounds]=SmoothedKPAlternative (SurvivalTimeData, Censored)
%note time bounds start with 0 and end wtih -1 (to indicate infinity)

% Order the data
[SurvivalTimeData, I]=sort(SurvivalTimeData);
Censored=Censored(I);
NotCensored=not(Censored);

% Determine the population time between surival points
Pos=0;
for i=NotCensored
    Pos=Pos+1;
    if i==1
        % Determine the probabilty of death per 
        
    end
end

