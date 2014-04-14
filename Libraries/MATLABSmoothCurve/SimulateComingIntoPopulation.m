% 
NumberToAdd=13500;
ProbabiltyLeaving=0.15;

X=DistributionOfIDU(NumberToAdd);
hist(X, 0:100)
xlim([10 35]);
set(gca, 'fontsize', 22)
set(gca,'Color',[1.0 1.0 1.0]);
set(gcf,'Color',[1.0 1.0 1.0]);%makes the grey border white
xlabel('Age at first injection');
ylabel('N');
box off;


PopAge=[];
PopRecent=[];
Total=0;

for Year=1:30
    
    %Age all existing people by 1 year
    PopAge=PopAge+1;
    
    %Simulate leaving
    PopRecent(logical(PopRecent))=rand(1, sum(PopRecent))<(1-ProbabiltyLeaving);
    
    %Add 12 year olds
    PopAge=[PopAge DistributionOfIDU(NumberToAdd)];
    PopRecent=[PopRecent true(1, NumberToAdd)];
    Total=Total+NumberToAdd;
    
    DistEver=hist(PopAge, 0:100);
    DistRecent=hist(PopAge(logical(PopRecent)), 0:100);
    
    
    
    plot(0:100, [DistEver; DistRecent])
    xlim([15 50]);
    drawnow;
    pause(0.1);
end

