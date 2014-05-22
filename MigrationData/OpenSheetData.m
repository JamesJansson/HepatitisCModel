function [Data, SACCCode, CountryName]=OpenSheetData(File, Sheet, Range)

%Load the whole range
NumericalData=xlsread(File, Sheet, ['C' num2str(Range(1)) ':AX' num2str(Range(2)) ]);

%Load the headers
[~, ~, SACCCodeTemp]=xlsread(File, Sheet, ['A' num2str(Range(1)) ':A' num2str(Range(2)) ]);

%clean SACC code (make all strings)
SACCCode=cell(size(SACCCodeTemp));
CountryCount=1;
for entry=SACCCodeTemp'
    if isnumeric(entry{:})==true
        %Convert from num to str
        entry=num2str(entry{:});
    else
        %Break it out of cell into array
        entry=entry{:};
    end
    SACCCode{CountryCount}=entry;
    CountryCount=CountryCount+1;
end


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
[SACCCode SACCIndex]=sort(SACCCode);
Data=Data(SACCIndex, :, :);