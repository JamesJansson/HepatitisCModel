% The purpose of this script is to show the deficiencies of advancing
% people probabilistically across age groups. 


clear 
clc

%Age Ranges
Ranges=[0 4;
    5 14;
    15 19;
    20 29;
    30 39;
    40 49;
    50 59;
    60 99];

%2000-2009 notifications
Incidence=...
    [1 2 4 2 4 3 6 3 1 6;
    3 2 1 1 1 2 1 2 0 2;
    73 90 60 62 43 52 48 48 41 30;
    275 359 221 235 166 182 203 174 184 207;
    122 168 107 107 102 100 126 107 93 111;
    52 47 44 46 35 35 46 39 32 34 ;
    8 9 10 10 9 5 6 7 6 10;
    4 6 1 3 1 0 6 4 5 1];%Note the 0.0001 on either side is usd to set the edge points. If you are certain incidence is 0 at birth, set the incidence in the age range 0-1 as zero.


% [AgeVector ReportedIDUSmoothed]=SmoothCurve(Ranges, ReportedIDU);


% for all the years
for Year=1:10
    [AgeVector, Incidence1Year(:, Year)]=SmoothCurve(Ranges, Incidence(:, Year));
    hold on;
end

for Year=11:20
    Incidence1Year(:, Year)=Incidence1Year(:, 10);
end



%Create 5 year bins
for Year=1:20
    for i=0:19
        Incidence5Year(i+1, Year)=Incidence1Year(5*i+1, Year)+Incidence1Year(5*i+2, Year)+Incidence1Year(5*i+3, Year)+Incidence1Year(5*i+4, Year)+Incidence1Year(5*i+5, Year);
    end
end




%Simulate aging in the range based estimates
Prevalence5Year=zeros(20, 20);
for Year=1:20
    Prevalence5Year(:, Year)=Incidence5Year(:, Year);%set prevalence to incidence
    if Year>1
        Prevalence5Year(1:19, Year)=Prevalence5Year(1:19, Year)+0.8*Prevalence5Year(1:19, Year-1);%Add people in the same band
        Prevalence5Year(2:20, Year)=Prevalence5Year(2:20, Year)+0.2*Prevalence5Year(1:19, Year-1);%Add people who move into next age band
        Prevalence5Year(20, Year)=Prevalence5Year(20, Year)+Prevalence5Year(20, Year-1);%Add people who woudl fall off the end
    end
    
end
    
%Simulate aging in the range based estimates
Prevalence1Year=zeros(100, 20);
for Year=1:20
    Prevalence1Year(:, Year)=Incidence1Year(:, Year);%set prevalence to incidence
    if Year>1
        Prevalence1Year(2:100, Year)=Prevalence1Year(2:100, Year)+Prevalence1Year(1:99, Year-1);%Add people from the previous year
        Prevalence1Year(100, Year)=Prevalence1Year(100, Year)+Prevalence1Year(100, Year-1);%Add people who woudl fall off the end
    end
    
end
    
%Create 5 year bins
for Year=1:20
    for i=0:19
        Prevalence1YearInBins(i+1, Year)=Prevalence1Year(5*i+1, Year)+Prevalence1Year(5*i+2, Year)+Prevalence1Year(5*i+3, Year)+Prevalence1Year(5*i+4, Year)+Prevalence1Year(5*i+5, Year);
    end
end



clf
plot(0:5:95, Prevalence5Year(:, 10), 'r--');
hold on;
plot(0:5:95, Prevalence5Year(:, 20), 'r-');
plot(0:5:95, Prevalence1YearInBins(:, 10), 'b--');
plot(0:5:95, Prevalence1YearInBins(:, 20), 'b-');
hold off;
xlabel('Age Band');
ylabel('Number in band');


disp(['Checksum (total) 2009; 5 year: ' num2str(sum(Prevalence5Year(:, 10))) ', 1 year: ' num2str(sum(Prevalence1Year(:, 10))) ])
disp(['Checksum (total) 2019; 5 year: ' num2str(sum(Prevalence5Year(:, 20))) ', 1 year: ' num2str(sum(Prevalence1Year(:, 20))) ])

Comparison=[ Prevalence1YearInBins(:, 10) Prevalence5Year(:, 10) Prevalence1YearInBins(:, 20) Prevalence5Year(:, 20)];


