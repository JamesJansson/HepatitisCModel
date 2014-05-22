%function AnalyseMigration
%AusData(Year, Country, Sex, Age)

%Determine highest impact countries by sorting by total population size
[CountrySize, CountrySizeIndexArray]=sort(TotalFromEachCountry, 'descend');
    CountryIndex=CountrySizeIndexArray(2);
    disp(CountryNames(CountryIndex))

% % % % % % % % % % %chooose a country, sex
% % % % % % % % % % FirstYear=1;
% % % % % % % % % % SecondYear=2;
% % % % % % % % % % for CountryCount=2:max(size(ContrySizeIndexArray))
% % % % % % % % % %     CountryIndex=CountrySizeIndexArray(2);
% % % % % % % % % %     disp(CountryNames(CountryIndex))
% % % % % % % % % %     for Sex=1:3
% % % % % % % % % %         FirstYearData=AusData(FirstYear, CountryIndex, Sex, :);
% % % % % % % % % %     end
% % % % % % % % % % end
% % % % % % % % % % % AusData(1)

%2001+migration
FirstYear=1;
SecondYear=2;
FirstYearData=squeeze(AusData(FirstYear, :, :, :));
SecondYearData=squeeze(AusData(SecondYear, :, :, :));
%(Country, Sex, Age)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%This is a bad algorithm: it breaks, causing negatives
%All the people in 0-5 in 2006 represent half the migration between
%2001-2006. The other half end up in the second age group
EstimatedMigrants(:, :, 1)=2*SecondYearData(:, :, 1);

for AgeGroup=2:max(size(AusData, 4))-1
    EstimatedMigrants(:, :, AgeGroup)=2*(SecondYearData(:, :, AgeGroup)-EstimatedMigrants(:, :, AgeGroup-1)/2-FirstYearData(:, :, AgeGroup-1));
end

% for the end group, 
AgeGroup=max(size(AusData, 4));
EstimatedMigrants(:, :, AgeGroup)=SecondYearData(:, :, AgeGroup)-EstimatedMigrants(:, :, AgeGroup-1)/2-FirstYearData(:, :, AgeGroup-1)-FirstYearData(:, :, AgeGroup);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


CountryIndex=CountrySizeIndexArray(4);
Sex=3;
disp(squeeze(squeeze(EstimatedMigrants(CountryIndex, Sex, :))))

a=[squeeze(squeeze(FirstYearData(CountryIndex, Sex, :))) squeeze(squeeze(SecondYearData(CountryIndex, Sex, :)))]; 

GenerateMigrationDistribution


%2006+migration