function [DistributionByYear, NegativeBands]=GenerateMigrationDistribution(StartDistribution, EndDistribution, MortalityBandRate)
%Assumptions about input
% StartDistribution, EndDistributioni s in 5 year increments between 0 and 75
% MortalityBandRate is in 5 year increments between 0 and 100
%Spacing between the starting and ending distribution is 5 years
% DistributionByYear is a 5 by 100 array
% Use the 5 year average as the population rate prior to the data available

SurvivalBandRate=1-MortalityBandRate;

% Weight people in the older bands according to their survival probability
AgedWeighting=[1 SurvivalBandRate(16)*[1 SurvivalBandRate(17)*[1 SurvivalBandRate(18)*[1 SurvivalBandRate(19)]]]];
%Normalise
AgedWeighting=AgedWeighting/sum(AgedWeighting);
%Space out 75 year olds
StartDistribution(16:20)=StartDistribution(16).*AgedWeighting;
EndDistribution(16:20)=EndDistribution(16).*AgedWeighting;

%Determine the increase in the age group accounting for mortality
Increase(1)=EndDistribution(1);
Increase(2:20)=EndDistribution(2:20)-SurvivalBandRate(1:19).*StartDistribution(1:19);
Increase(20)=Increase(20)-SurvivalBandRate(1:20).*StartDistribution(1:20);

%Remove negatives from increase
NegativeBands=Increase<0;% feedback negatives, incase there is something interesting 
Increase(NegativeBands)=0;

% all people between 0 and 5 years in the end distribution should be
% younger than 5 in the 5th year
% Mean per year=Increase(0)/(25);

BandCount=0;
for BandStart=0:5:95
    for Y=1:6
        for AgeIndex=(0:4)
            if (Y=1 || Y=6) %on the diagonals, apply a half rate
                DistributionByYear(Y, AgeIndex)


                disp(DistributionByYear);
                pause(0.5);
            end
        end
    end
    BandCount=BandCount+1;
end





DistributionByYear=[]
NegativeBands=[]



end

