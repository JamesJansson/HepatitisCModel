function X=DistributionOfIDU(NumberToAdd)
MeanAgeAtFirstIDUUse=20;
VarianceOfAgeAtFirstIDUUse=10;

m = MeanAgeAtFirstIDUUse;
v = VarianceOfAgeAtFirstIDUUse;
mu = log((m^2)/sqrt(v+m^2));
sigma = sqrt(log(v/(m^2)+1));

X = lognrnd(mu,sigma,1,NumberToAdd);

% hist(X, 0:100)
% xlim([10 35]);
% xlabel('Age at first injection');
% ylabel('Number added');

