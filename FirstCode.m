% Author: James Jansson, UNSW

% Regular network (attached to nearest neighbours on a ring)
% Small world network
% Sparse network with dense subgraph <- most realistic for cold, flu etc
% Sparse random network

%http://arxiv.org/ftp/arxiv/papers/1302/1302.4024.pdf

% Paper to investigate
% The Structure and Function of Complex Networks
% Read More: http://epubs.siam.org/doi/abs/10.1137/S003614450342480?journalCode=siread&



ConnectionsPerNode=2*3*2;
TotalNodes=7*5*4*3*2 *119;%7*5*4*3*2=840, 119*840=99960~100000
NumSims=100;


% Groups to try

% Each person has 2 groups with 6 connections, leading to 7 people per group
confignum=1;
Groups(confignum)=2; Connections(confignum)=6; GroupSize(confignum)=7;
% Each person has 3 groups with 4 connections, leading to 5 people per group
confignum=2;
Groups(confignum)=3; Connections(confignum)=4; GroupSize(confignum)=5;
% Each person has 4 groups with 3 connections, leading to 4 people per group
confignum=3;
Groups(confignum)=4; Connections(confignum)=3; GroupSize(confignum)=4;
% Each person has 6 groups with 2 connections, leading to 3 people per group
confignum=4;
Groups(confignum)=6; Connections(confignum)=2; GroupSize(confignum)=3;
% Each person has 12 groups with 1 connection, leading to 2 people per group (Each person has 12 connections) 
confignum=5;
Groups(confignum)=12; Connections(confignum)=1; GroupSize(confignum)=2;

% at some later point, we'll analyse
% 30 people in work/school group, 5 in social group, 5 in family



% for each of the group configs
for confignum=1:5
    % for the number of simulations to repeat over
    for sim=1:NumSims
        % Create groups
            % Divide number of nodes by number in group = number of groups
            % for the number of groups per person
                % group assignment = [1 1 1 1 1 2 2 2 2 2 ....]
                % randperm
        % Create a connection matrix
            % for the number of groups per person
                % look up the groups the individual belongs to
                % add all the individuals in the group to a lookup matrix which is sparse
            Store(confignum).Connection(sim, ID, ConnectionIDIndex);
    end
end

            
DepthCheckMax=100;%number of steps that are checked before stopping
% for each of the group configs
for confignum=1:5
    % for the number of simulations to repeat over
    
    Results(confignum).DepthMatrix=zeros(NumSims, TotalNodes, TotalNodes);
    for sim=1:NumSims
        ConnectionMatrix=Store(confignum).Connection(sim, :, :);
        for Ind=1:TotalNodes
            DepthArray=-1*ones(1, TotalNodes);%an array that records if the individual has been checked or not
            DepthArray(Ind)=0;
            CheckThisStep=Ind;%an array to store the next set of people to check

            Depth=0;
            KeepChecking=true;
            while Depth<DepthCheckMax && KeepChecking
                Depth=Depth+1;
                %Look up individuals in those that are being check this step
                CheckNext=ConnectionMatrix(CheckThisStep, :);
                % Reshape
                CheckNext=reshape(CheckNext, 1, []);
                % Remove duplicates
                CheckNext=unique(CheckNext);
                % Look up checked array
                CheckNext=find(DepthArray(CheckNext)<0.5);
                
                [~, NumToCheck]=size(CheckNext);
                if NumToCheck<1 %if there are no new people to check
                    KeepChecking=false;
                else
                    CheckThisStep=CheckNext;
                    DepthArray(CheckNext)=Depth;
                end
            end
            Results(confignum).DepthMatrix(Sim, Ind, :)=DepthArray;
            %note values that could not be reached are represented as -1
        end
    end
    
    %Determine the total number 
    Results(confignum).DistancePropExplored=
    AllDistances=Results(confignum).DepthMatrix;
    AllDistances=reshape(AllDistances, 1, []);
    AllDistances(AllDistances==0)=[];
    Results(confignum).DistanceHistogram=AllDistances;
    
end


% Determine the speed of connections (% of population reached on average
% after 1 step, 2 steps, 3 steps etc)

% Determine probability of interacting with a person who is infected?


% then do sexual connections- individual must choose only a set number of sexual parteners in the groups they are in
% Or even allow 'friends of friends'
% Repeat measurements of speed etc




% A larger distance between points implies that for an an epidemic which
% reaches 10% of the population in 5 interactions has a much higher
% probability of transmission in a system with 