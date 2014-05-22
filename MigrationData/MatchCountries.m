for StateNum=1
    % Determine the countries that make up the largest part of the
    % Australian population in 2011. 
    YearIndex=4;
    IndexCodes=State(StateNum, YearIndex).SACCCode;
    
    CompiledState(StateNum).IndexCodes=sort(State(StateNum, YearIndex).SACCCode);
    
    state, country, sex, age, year, 
    8, 285, 3, 16, 4
    
    
    AgeSize=16;
    SexSize=3;
    YearSize=4;
    for SexNum=1:SexSize
        %create the empty matrix
        DataOutput=-1*ones(AgeSize, YearSize);

        for YearIndex=1:4
            for CountryCount=State(StateNum, YearIndex).SACCCode


            



            CompiledState(StateNum).Country(CountryCount).Data(SexCount, AgeCount, YearCount)=-1*ones(SexSize,AgeSize, YearSize);
            % go through each year and extract the relevant information
            CompiledState(StateNum).Country(CountryCount).Data(SexCount, AgeCount, YearCount)=

        end
    end
    
    
    State(StateNum, YearIndex).Data
    
    find countries that match
    
end