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
Increase(20)=Increase(20)-SurvivalBandRate(20).*StartDistribution(20);

%Remove negatives from increase
NegativeBands=Increase<0;% feedback negatives, incase there is something interesting 
Increase(NegativeBands)=0;

% all people between 0 and 5 years in the end distribution should be
% younger than 5 in the 5th year
% Mean per year=Increase(0)/(25);
% disp([Increase' StartDistribution EndDistribution])
disp([EndDistribution(2:20) StartDistribution(1:19)])
pause(10);
DistributionByYear=zeros(5, 100);

BandCount=1;
for BandStart=-4:5:95
    if (BandCount==1 )
        % Apply double rate
        IncreasePerBox=Increase(BandCount)/12.5;
    else
        IncreasePerBox=Increase(BandCount)/25;
    end
    disp(IncreasePerBox)
    for Y=1:5
        for AgeAdd=(0:5)
            Ageindex=BandStart+AgeAdd+(Y-1);
            if (Ageindex>0)
                if (AgeAdd==0 || AgeAdd==5) %on the diagonals, apply a half rate
                    DistributionByYear(Y, Ageindex)=DistributionByYear(Y, Ageindex)+IncreasePerBox/2;
                else %apply at the normal rate
                    DistributionByYear(Y, Ageindex)=DistributionByYear(Y, Ageindex)+IncreasePerBox;
                end
            end
        end
        disp(DistributionByYear(:, 1:100));
        pause(0.1);
    end
    BandCount=BandCount+1;
end



end

