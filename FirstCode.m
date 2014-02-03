% Author: James Jansson, UNSW

% Regular network (attached to nearest neighbours on a ring)
% Small world network
% Sparse network with dense subgraph <- most realistic for cold, flu etc
% Sparse random network

%http://arxiv.org/ftp/arxiv/papers/1302/1302.4024.pdf


ConnectionsPerNode=2*3*2;
TotalNodes=7*5*4*3*2 *119;%7*5*4*3*2=840, 119*840=99960~100000
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


% for each of the group configs
for confignum=1:5
    % for the number of simulations to repeat over
    for sim=1:100
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

            

% for each of the group configs
for confignum=1:5
    % for the number of simulations to repeat over
    for sim=1:100
        DepthCheckMax=100;%number of steps that are checked before stopping
        CheckedArray=rand(1, TotalNodes);%an array that records if the individual has been checked or not
        CheckThisStep=[];%an array to store the next set of people to check

        ConnectionMatrix=Store(confignum).Connection(sim, :, :);
        
        for Ind=1:TotalNodes
            CheckThisStep=Ind;
            Depth=0;
            while Depth<DepthCheckMax
                Depth=Depth+1;

            end


        end
    end
end


% Determine the speed of connections (% of population reached on average
% after 1 step, 2 steps, 3 steps etc)

% Determine probability of interacting with a person who is infected?


% then do sexual connections- individual must choose only a set number of sexual parteners in the groups they are in
% Or even allow 'friends of friends'
% Repeat measurements of speed etc