%function AnalyseMigration
%AusData(Year, Country, Sex, Age)

%% Generate migration distribution
%Note that these mortality rates represent the expected AVERAGE probability
%of mortality occuring in a 5 year period moving on to the next age band. 


MaleMortalityBands=[0.003170074
0.000522614
0.001521396
0.003132185
0.004016083
0.004650213
0.005532987
0.007115477
0.010048755
0.01470482
0.022155291
0.034815236
0.056170269
0.091866948
0.153279057
0.254362478
0.444732149
0.573071932
0.573071932
0.573071932];

FemaleMortalityBands=[0.002625521
0.0004999
0.000863273
0.001362873
0.001567187
0.001884896
0.002633465
0.003902724
0.005962279
0.009011412
0.01349145
0.021059357
0.033381221
0.05486433
0.094749857
0.170859989
0.363610297
0.506126996
0.506126996
0.506126996];


%% Determine highest impact countries by sorting by total population size
[CountrySize, CountrySizeIndexArray]=sort(TotalFromEachCountry, 'descend');



% 2001+migration
FirstYear=1;
SecondYear=2;
FirstYearData=squeeze(AusData(FirstYear, :, :, :));
SecondYearData=squeeze(AusData(SecondYear, :, :, :));
%(Country, Sex, Age)




CountryIndex=CountrySizeIndexArray(4);
Sex=1;





ThisFirstYearData=squeeze(squeeze(FirstYearData(CountryIndex, Sex, :)));
ThisSecondYearData=squeeze(squeeze(SecondYearData(CountryIndex, Sex, :)));

    
[DistributionByYear, NegativeBands]=GenerateMigrationDistribution(ThisFirstYearData, ThisSecondYearData, MaleMortalityBands);


% 2006+migration