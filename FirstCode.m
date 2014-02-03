% Regular network (attached to nearest neighbours on a ring
% Small world network
% Sparse network with dense subgraph <- most realistic for cold, flu etc
% Sparse random network

%http://arxiv.org/ftp/arxiv/papers/1302/1302.4024.pdf

TotalNodes=1000000;
ConnectionsPerNode=2*3*2;





% Groups to try

% Each person has 2 groups with 6 connections, leading to 7 people per group
% Each person has 3 groups with 4 connections, leading to 5 people per group
% Each person has 4 groups with 3 connections, leading to 4 people per group
% Each person has 6 groups with 2 connections, leading to 3 people per group
% Each person has 12 groups with 2 connections, leading to 2 people per group (Each person has 12 connections) 