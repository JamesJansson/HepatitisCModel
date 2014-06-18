function [Age, AgeValues]=SmoothCurve(Ranges, values)
% Written by James Jansson, as part of a PhD program


%create a vector that indiates the ranges
Age=(min(Ranges( :, 1))):(max(Ranges(:, 2)));
j=0;
[RangesLength,~]=size(Ranges);
RangesVector=1:RangesLength;
for CurrentAge=Age
    j=j+1;
    RangesRef=CurrentAge>=Ranges(:, 1)&CurrentAge<=Ranges(:, 2);
    AgeValues(j)=values(RangesRef)/(Ranges(RangesRef, 2)-Ranges(RangesRef, 1)+1);
    AgeRangeNumber(j)=RangesVector(RangesRef);
end

%Start plot
h4=plot(Age, AgeValues);
%axis([0 70 0 0.06])%axis([xmin xmax ymin ymax]);

% axis([0 70 0 7])


[~, VectorLength]=size(Age);
NumbersVector=1:VectorLength;
pause(0.5);
for i=1:200
    pause(0.01);

    %Smooth all adjacent points
    
    for j=1:VectorLength
        if j==1
            %AgeValues(1)=mean([AgeValues(1) AgeValues(2)]);
            %Temp(1)=mean([AgeValues(1) AgeValues(2)]);
            %Temp(1)=AgeValues(2);
            Temp(1)=AgeValues(1);
            
        elseif j==VectorLength
            %AgeValues(VectorLength)=mean([AgeValues(VectorLength-1) AgeValues(VectorLength)]);
            %Temp(VectorLength)=mean([AgeValues(VectorLength-1) AgeValues(VectorLength)]);
            %Temp(VectorLength)=AgeValues(VectorLength-1);
            Temp(VectorLength)=AgeValues(VectorLength);
        else
            %AgeValues(j)=mean([AgeValues(j-1) AgeValues(j) AgeValues(j+1)]);
            Temp(j)=mean([AgeValues(j-1) AgeValues(j) AgeValues(j+1)]);
            %Temp(j)=mean([AgeValues(j-1) AgeValues(j+1)]);
            
              
            
        end
    end
    AgeValues=Temp;
    %Normalise blocks that have become the wrong height
    for BlockNumber=1:RangesLength
        %Factor=sum of the real block/sum of the simulated block
        NormalisingFactor=values(BlockNumber)/sum(AgeValues(BlockNumber==AgeRangeNumber));
        AgeValues(BlockNumber==AgeRangeNumber)=AgeValues(BlockNumber==AgeRangeNumber)*NormalisingFactor;
    end

    set(h4,'xdata',Age,'ydata',AgeValues);
    drawnow;

end