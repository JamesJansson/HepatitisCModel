function [SACCCode, SACCIndex]=LoadSACCCodeAndOrdering(File, Sheet, Range)
%return the SACCCodes from the file and the order which they appear in the file


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
[SACCCode, SACCIndex]=sort(SACCCode);

end