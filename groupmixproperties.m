% Sparse networks grouping
% This function demonstrates moving between groups. Each person has an
% annual probability of of leaving their current group and joining another.
clear
NoPeople=10000000;
AveragePeoplePerGroup=3.1419; 
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

NumberInGroup(1:NoGroups)=0;
for GroupNumber=AssignVec
    NumberInGroup(GroupNumber)=NumberInGroup(GroupNumber)+1;
end


% Figure 2: Distribution of people in each group
subplot(1, 2, 1);
hist(NumberInGroup, 0:30)
xlim([-1 15])
xlabel('Number of people per group');
ylabel('Number of groups');

% Figure 3: Count contacts per person
for i=1:NoPeople
    Contacts(i)=NumberInGroup(AssignVec(i))-1;
end
subplot(1, 2, 2);
hist(Contacts, 0:30)
xlim([-1 15])
xlabel('Number of contacts per person');
ylabel('Number of people');

%Figure 4: Contacts per person over time
MeanContacts(1)=mean(Contacts);
disp('Mean number of contacts per person');
disp(MeanContacts);


%Figure 5: Mean people in groups with people in them
GroupsWithPeopleInThem=NumberInGroup(NumberInGroup>0);
MeanPeoplePerGroupWithPeople(1)=mean(GroupsWithPeopleInThem);
disp('Mean people per group with people');
disp(MeanPeoplePerGroupWithPeople);
