function [Data, SACCCode, CountryName]=OpenSheetData(File, Sheet, Range)

%Load the whole range
NumericalData=xlsread(File, Sheet, ['C' num2str(Range(1)) ':AX' num2str(Range(2)) ]);

%Load the headers
[SACCCode, SACCIndex]=LoadSACCCodeAndOrdering(File, Sheet, Range);

% Break out age and sex into separate matrix dimensions
[~, ~, CountryName]=xlsread(File, Sheet, ['B' num2str(Range(1)) ':B' num2str(Range(2)) ]);

TotalRows=Range(2)-Range(1)+1;
for CountryCount=1:TotalRows
    ColumnCount=1;
    AgeCount=1;
    while ColumnCount<=48
        for SexCount=1:3
            Data(CountryCount, SexCount, AgeCount)=NumericalData(CountryCount, ColumnCount);
            ColumnCount=ColumnCount+1;
        end
        AgeCount=AgeCount+1;
    end
end

%Order data according to SACCCode
CountryName=CountryName(SACCIndex);
Data=Data(SACCIndex, :, :);