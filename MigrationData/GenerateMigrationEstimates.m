function GenerateMigrationEstimates

LoadAndCleanMigrationData

IndexCodes=sort(State(1, 4).SACCCode);


[CountryData]=MatchCountries

DetermineMigrationRate

SaveToCSV


for EachState
    MatchAge