function [DistributionByYear]=GenerateMigrationDistribution(StartDistribution, EndDistribution, MortalityBandRate)
%Assumptions about input
% StartDistribution, EndDistributioni s in 5 year increments between 0 and 75
% MortalityBandRate is in 5 year increments between 0 and 100
%Spacing between the starting and ending distribution is 5 years
% DistributionByYear is a 5 by 100 array
% Use the first column as the population rate prior to the data available

SurvivalBandRate=1-MortalityBandRate;

Increase=EndDistribution-SurvivalBandRate*StartDistribution;

%Remove negatives from increase

Increase(Increase<0)=0;

% all people between 0 and 5 years in the end distribution 


%


% if zero people in 70-75 and > 0 in 75+, all people are in 75 to 80,
% otherwise evenly spaced according to 70-75





end

