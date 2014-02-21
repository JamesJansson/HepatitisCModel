% Sparse networks grouping
% This function demonstrates moving between groups. Each person has an
% annual probability of of leaving their current group and joining another.
clear
NoPeople=1000;
AveragePeoplePerGroup=5.5;
NoGroups=round(NoPeople/AveragePeoplePerGroup);

PersonID=1:NoPeople;
ProbabilityOfMoving=0.01;



% Randomly assign the individuals
AssignVec=randsample(NoGroups, NoPeople, true);

%Count numbers in each group
for g=1:NoGroups
    NumberInGroup(g)=sum(AssignVec==g);
end
% Figure 1: Number of people in each group
subplot(4, 2, 1);
bar(1:NoGroups, NumberInGroup);
xlim([0 NoGroups])
xlabel('Group ID');
ylabel('Number of people in group');

% Figure 2: Distribution of people in each group
subplot(4, 2, 3);
hist(NumberInGroup, 0:30)
xlim([-1 15])
xlabel('Number of people per group');
ylabel('Number of groups');

% Figure 3: Count contacts per person
for i=1:NoPeople
    Contacts(i)=NumberInGroup(AssignVec(i))-1;
end
subplot(4, 2, 5);
hist(Contacts, 0:30)
xlim([-1 15])
xlabel('Number of contacts per person');
ylabel('Number of people');

%Contacts per person over time
MeanContacts=mean(Contacts);
MedianContacts=median(Contacts);
UQRContacts=prctile(Contacts, 75);
LQRContacts=prctile(Contacts, 25);

subplot(4, 1, 4);
plot(MeanContacts);
xlabel('Step');
ylabel('Mean number of contacts per person');

drawnow();


for Sim=1:10000
    
    %Decide if the person is going to move
    Movers=rand(1, NoPeople)<ProbabilityOfMoving;
    NoMovers=sum(Movers);
    
    % Randomly assign the individuals
    AssignVec(Movers)=randsample(NoGroups, NoMovers, true);

    disp(NoMovers)
    
    %Count numbers in each group
    for g=1:NoGroups
        NumberInGroup(g)=sum(AssignVec==g);
    end
    % Figure 1: Number of people in each group
    subplot(4, 2, 2);
    bar(1:NoGroups, NumberInGroup);
    xlim([0 NoGroups]);
    xlabel('Group ID');
    ylabel('Number of people in group');

    % Figure 2: Distribution of people in each group
    subplot(4, 2, 4);
    hist(NumberInGroup, 0:30)
    xlim([-1 15])
    xlabel('Number of people per group');
    ylabel('Number of groups');

    % Figure 3: Count contacts per person
    for i=1:NoPeople
        Contacts(i)=NumberInGroup(AssignVec(i))-1;
    end
    subplot(4, 2, 6);
    hist(Contacts, 0:30)
    xlim([-1 15])
    xlabel('Number of contacts per person');
    ylabel('Number of people');
    
    %Contacts per person over time
    MeanContacts(Sim+1)=mean(Contacts);
    MedianContacts(Sim+1)=median(Contacts);
    UQRContacts(Sim+1)=prctile(Contacts, 75);
    LQRContacts(Sim+1)=prctile(Contacts, 25);
    
    subplot(4, 1, 4);
    %plot([MeanContacts; MedianContacts; UQRContacts; LQRContacts]);
    plot(MeanContacts);
    xlabel('Step');
    ylabel('Mean number of contacts per person');

    drawnow();

end
