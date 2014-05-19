%function LoadAndCleanMigrationData

File1996='ABS Data/1996 34120do006_201112_201213.xls';
File2001='ABS Data/2001 34120do007_201112_201213.xls';
File2006='ABS Data/2006 34120do008_201112_201213.xls';
File2011='ABS Data/2011 attualiz.xls';



StateNum=1;
%Load NSW data
%1996
YearIndex=1;
[State(StateNum, YearIndex).Data, State(StateNum, YearIndex).SACCCode State(StateNum, YearIndex).CountryName]=OpenSheetData(File1996, 'Table_6.2', [9 59]);
%2001 ;
YearIndex=2;

%2006
YearIndex=3;

%2011
YearIndex=4;


%Load NSW data
%1996

%2001

%2006

%2011