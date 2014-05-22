%function LoadAndCleanMigrationData
clear
File1996='ABS Data/1996 34120do006_201112_201213.xls';
File2001='ABS Data/2001 34120do007_201112_201213.xls';
File2006='ABS Data/2006 34120do008_201112_201213.xls';
File2011='ABS Data/2011 attualiz.xls';

disp('Load Australia data')
%Load Australian data 2001 - 2006 - 2011
%AusData(Year, Country, Sex, Age)
[AusData(1, :, :, :), SACCCodes, CountryNames]=OpenSheetData(File2001, 'Table_7.1', [9 294]);
[AusData(2, :, :, :), SACCCodes, CountryNames]=OpenSheetData(File2006, 'Table_8.1', [9 294]);
[AusData(3, :, :, :), SACCCodes, CountryNames]=OpenSheetData(File2011, 'Table_9.1', [9 294]);

%Load state data 2011
disp('Load state data')
for StateCount=1:8
    temp=xlsread(File2011, ['Table_9.' num2str(StateCount+1)], 'BA9:BA294');
    [SACCCode, SACCIndex]=LoadSACCCodeAndOrdering(File2011, ['Table_9.' num2str(StateCount+1)], [9 294]);
    %out put the data by SACC code
    CountryStateNumber(StateCount, :)=temp(SACCIndex);
end

disp('Calc state proportions')
TotalFromEachCountry=sum(CountryStateNumber, 1);
size(TotalFromEachCountry)
Multiplier=ones(8, 1)*TotalFromEachCountry;
CountryProportion=CountryStateNumber./Multiplier;
CountryProportion(isnan(CountryProportion))=0;


AnalyseMigration


























% 
% 
% 
% %Estimate per year migration by age and country and sex
% %Find negatives, zero out?
% 
% 
% 
% 
% 
% %1996
% %YearIndex=1;
% %[State(StateNum, YearIndex).Data, State(StateNum, YearIndex).SACCCode, State(StateNum, YearIndex).CountryName]=OpenSheetData(File1996, 'Table_6.2', [9 59]);
% 
% %Load NSW data
% StateNum=1;
% %2001 ;
% YearIndex=1;
% [State(StateNum, YearIndex).Data, State(StateNum, YearIndex).SACCCode, State(StateNum, YearIndex).CountryName]=OpenSheetData(File2001, 'Table_7.2', [9 294]);
% %2006
% YearIndex=2;
% [State(StateNum, YearIndex).Data, State(StateNum, YearIndex).SACCCode, State(StateNum, YearIndex).CountryName]=OpenSheetData(File2006, 'Table_8.2', [9 294]);
% %2011
% YearIndex=3;
% [State(StateNum, YearIndex).Data, State(StateNum, YearIndex).SACCCode, State(StateNum, YearIndex).CountryName]=OpenSheetData(File2011, 'Table_9.2', [9 294]);
% 
% %Load Vic data
% StateNum=2;
% %2001 ;
% YearIndex=1;
% [State(StateNum, YearIndex).Data, State(StateNum, YearIndex).SACCCode, State(StateNum, YearIndex).CountryName]=OpenSheetData(File2001, 'Table_7.3', [9 294]);
% %2006
% YearIndex=2;
% [State(StateNum, YearIndex).Data, State(StateNum, YearIndex).SACCCode, State(StateNum, YearIndex).CountryName]=OpenSheetData(File2006, 'Table_8.3', [9 294]);
% %2011
% YearIndex=3;
% [State(StateNum, YearIndex).Data, State(StateNum, YearIndex).SACCCode, State(StateNum, YearIndex).CountryName]=OpenSheetData(File2011, 'Table_9.3', [9 294]);