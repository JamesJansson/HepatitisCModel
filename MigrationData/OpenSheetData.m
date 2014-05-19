function [Data, SACCCode, CountryName]=OpenSheetData(File, Sheet, Range)

%Load the whole range
NumericalData=xlsread(File, Sheet, ['C' num2str(Range(1)) ':AX' num2str(Range(2)) ]);
%Strip and save the headers
[~, SACCCode, ~]=xlsread(File, Sheet, ['A' num2str(Range(1)) ':A' num2str(Range(2)) ]);
[~, CountryName, ~]=xlsread(File, Sheet, ['B' num2str(Range(1)) ':B' num2str(Range(2)) ]);




size(NumericalData)

TotalRows=Range(2)-Range(1)+1;
for CountryCount=1:TotalRows
    ColumnCount=1;
    AgeCount=1;
    while ColumnCount<=48
        for SexCount=1:3
            Data(CountryCount, SexCount, AgeCount).value=NumericalData(CountryCount, ColumnCount);
            ColumnCount=ColumnCount+1;
        end
        AgeCount=AgeCount+1;
    end
end
    
    
