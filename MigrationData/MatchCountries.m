for each state
    % Determine the countries that make up the largest part of the
    % Australian population in 2011. 
    YearIndex=4;
    IndexCodes=State(StateNum, YearIndex).SACCCode;
    
    CompiledState(StateNum).IndexCodes=State(StateNum, YearIndex).SACCCode;
    
    
    %
    CompiledState(StateNum).Country(CountryCount).Data(SexCount, AgeCount, YearCount)=-1*ones(SexSize,AgeSize, YearSize);
    % go through each year and extract the relevant information
    CompiledState(StateNum).Country(CountryCount).Data(SexCount, AgeCount, YearCount)=
    
    
    
    State(StateNum, YearIndex).Data
    
    find countries that match