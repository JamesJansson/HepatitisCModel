%function AnalyseMigration
%AusData(Year, Country, Sex, Age)

%% Generate migration distribution
%Note that these mortality rates represent the expected AVERAGE probability
%of mortality occuring in a 5 year period moving on to the next age band. 


Male5YearMortalityBands=[0.003170074
0.000522614
0.001521396
0.003132185
0.004016083
0.004650213
0.005532987
0.007115477
0.010048755
0.01470482
0.022155291
0.034815236
0.056170269
0.091866948
0.153279057
0.254362478
0.444732149
0.573071932
0.573071932
0.573071932];

Female5YearMortalityBands=[0.002625521
0.0004999
0.000863273
0.001362873
0.001567187
0.001884896
0.002633465
0.003902724
0.005962279
0.009011412
0.01349145
0.021059357
0.033381221
0.05486433
0.094749857
0.170859989
0.363610297
0.506126996
0.506126996
0.506126996];

Mortality=[Male5YearMortalityBands Female5YearMortalityBands];




%% Go through each country, then each sex, then the two ranges of years
[~, NumCountries]=size(CountrySizeIndexArray);
YearlyCellMatrix={};
MeanCellMatrix={};
for CountryCount=1:NumCountries
    CountryIndex=CountrySizeIndexArray(CountryCount);% run each country by its size
    ThisCountryName=CountryNames{CountryIndex};
    ThisCountryName(ThisCountryName=='/')=[];%remove characters we don't like
    for Sex=1:2
        % 2001+migration
        FirstYear=1;
        SecondYear=2;
        
        FirstYearData=squeeze(AusData(FirstYear, CountryIndex, Sex, :));
        SecondYearData=squeeze(AusData(SecondYear, CountryIndex, Sex, :));
        
        [DistributionByYear1, NegativeBands]=GenerateMigrationDistribution(FirstYearData, SecondYearData, Mortality(:, Sex));

        % 2006+migration
        FirstYear=2;
        SecondYear=3;
        
        FirstYearData=squeeze(squeeze(squeeze(AusData(FirstYear, CountryIndex, Sex, :))));
        SecondYearData=squeeze(squeeze(squeeze(AusData(SecondYear, CountryIndex, Sex, :))));
        
        [DistributionByYear2, NegativeBands]=GenerateMigrationDistribution(FirstYearData, SecondYearData, Mortality(:, Sex));
        
        DistributionByYear=[DistributionByYear1; DistributionByYear2];
        
        % Output a graph of the results
        clf;
        MeanDistributionByYear=mean(DistributionByYear, 1);
        plot(0:99, MeanDistributionByYear, 'k', 'LineWidth',2);
        hold on;
        plot(0:99, DistributionByYear);
        hold off;
        xlabel('Age','fontsize', 22);
        ylabel('Number of immigrants per year','fontsize', 22);
        set(gca,'Color',[1.0 1.0 1.0]);
        set(gcf,'Color',[1.0 1.0 1.0]);%makes the grey border white
        set(gca, 'fontsize', 18)
        box off;
        %Save the plot
        FileName=['savedata/migrants-' num2str(CountryCount) '-' ThisCountryName '-' num2str(Sex) '.png'];
        disp(FileName)
        print('-dpng ','-r300',FileName);

        % Add to the Matrix for saving
        % SACCCode 
        CountryCodeOutput=(repmat({SACCCodes(CountryCount)},10,1));
        % Country name
        CountryNameOutput=(repmat({ThisCountryName},10,1));
        % Sex
        SexOutput=(repmat({num2str(Sex)},10,1));
        % Year
        YearOutput=num2str((2001:2010)');
        YearOutput=cellstr(YearOutput);
        % Data
        DataOutput=num2cell(DistributionByYear);
        
        ToAppend=[CountryNameOutput SexOutput YearOutput DataOutput];
        YearlyCellMatrix=[YearlyCellMatrix; ToAppend];
        
        % SACCCode 
        CountryCodeOutput={SACCCodes(CountryCount)};
        % Country name
        CountryNameOutput={ThisCountryName};        
        % Sex
        SexOutput={num2str(Sex)};
        %Year
        YearOutput=cellstr('Mean');
        % Data
        DataOutput=num2cell(MeanDistributionByYear);
        ToAppend=[CountryNameOutput SexOutput YearOutput DataOutput];
        MeanCellMatrix=[MeanCellMatrix; ToAppend];
    end
end

%Join the data into a massive cell

% Save the data to a csv/xls

xlswrite('savedata/EstimatedYearlyMigration.xls', YearlyCellMatrix); 
xlswrite('savedata/EstimatedMeanMigration.xls', MeanCellMatrix); 