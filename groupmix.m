% Sparse networks grouping
% This function demonstrates moving between groups. Each person has an
% annual probability of of leaving their current group and joining another.
clear
NoPeople=1000;
AveragePeoplePerGroup=2.5; 
% avearge people per group is 2.5: however the number of people per group 
% with people in it is less than 400, on average. Many of them have no
% people. 
% In addition to this, a group of 4 people have 4 people with 3 contacts.
% Two groups with two people have 4 people with 1 contact. The accumulation
% of people in the bigger groups results in many more contacts than would
% be expected otherwise.
NoGroups=round(NoPeople/AveragePeoplePerGroup);

PersonID=1:NoPeople;
ProbabilityOfMoving=0.01;



% Randomly assign the individuals
AssignVec=randsample(NoGroups, NoPeople, true);
AssignVec=AssignVec';

%Count numbers in each group
NumberInGroup(1:NoGroups)=0;
for GroupNumber=AssignVec
    NumberInGroup(GroupNumber)=NumberInGroup(GroupNumber)+1;
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

%Figure 4: Contacts per person over time
MeanContacts(1)=mean(Contacts);
subplot(4, 2, 7);
plot(MeanContacts);
xlabel('Step');
ylabel('Mean number of contacts per person');

%Figure 5: Mean people in groups with people in them
GroupsWithPeopleInThem=NumberInGroup(NumberInGroup>0);
MeanPeoplePerGroupWithPeople(1)=mean(GroupsWithPeopleInThem);
subplot(4, 2, 8);
plot(MeanPeoplePerGroupWithPeople);
xlabel('Step');
ylabel('Mean people per group with people');
    
drawnow();


for Sim=1:10000
    
    %Decide if the person is going to move
    Movers=rand(1, NoPeople)<ProbabilityOfMoving;
    NoMovers=sum(Movers);
    
    % Randomly assign the individuals
    AssignVec(Movers)=randsample(NoGroups, NoMovers, true);

    disp(NoMovers)
    
    %Count numbers in each group
    NumberInGroup(1:NoGroups)=0;
    for GroupNumber=AssignVec
        NumberInGroup(GroupNumber)=NumberInGroup(GroupNumber)+1;
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
    
    %Figure 4: Contacts per person over time
    MeanContacts(Sim+1)=mean(Contacts);
    subplot(4, 2, 7);
    plot(MeanContacts);
    xlabel('Step');
    ylabel('Mean number of contacts per person');

    %Figure 5: Mean people in groups with people in them
    GroupsWithPeopleInThem=NumberInGroup(NumberInGroup>0);
    MeanPeoplePerGroupWithPeople(Sim+1)=mean(GroupsWithPeopleInThem);
    subplot(4, 2, 8);
    plot(MeanPeoplePerGroupWithPeople);
    xlabel('Step');
    ylabel('Mean people per group with people');
    
    drawnow();

end
disp('Mean contacts per person')
mean(MeanContacts)
