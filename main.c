#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxLineLength 1000

void removeQuotation(char *str)
{

    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '"')
        {
            for (int j = i; j < len - 1; j++)
            {
                str[j] = str[j + 1];
            }
            str[len - 1] = '\0';
            len--;
            i--;
        }
    }
}

int main()
{

    FILE *statscan = fopen("statscan_diabetes.csv", "r");
    FILE *plot1 = fopen("plot1.data", "w");
    FILE *plot2 = fopen("plot2.data", "w");

    char line[MaxLineLength],
        refDate[MaxLineLength],
        geo[MaxLineLength],
        ageGroup[MaxLineLength],
        value[MaxLineLength],
        *ageGroupArray[3] = {"35 to 49 years", "50 to 64 years", "65 years and over"};
    ;

    double ontarioCount = 0, ontarioSum = 0,
           quebecCount = 0, quebecSum = 0,
           bcCount = 0, bcSum = 0,
           albertaCount = 0, albertaSum = 0,
           canadaCount = 0, canadaSum = 0,
           ontarioYearCount[7] = {0}, ontarioYearSum[7] = {0},
           quebecYearCount[7] = {0}, quebecYearSum[7] = {0},
           bcYearCount[7] = {0}, bcYearSum[7] = {0},
           albertaYearCount[7] = {0}, albertaYearSum[7] = {0},
           canadaYearCount[7] = {0}, canadaYearSum[7] = {0},
           ontarioAgeCount[3] = {0}, ontarioAgeSum[3] = {0},
           quebecAgeCount[3] = {0}, quebecAgeSum[3] = {0},
           bcAgeCount[3] = {0}, bcAgeSum[3] = {0},
           albertaAgeCount[3] = {0}, albertaAgeSum[3] = {0},
           canadaAgeCount[3] = {0}, canadaAgeSum[3] = {0},
           ontarioYearAverage[6], quebecYearAverage[6],
           bcYearAverage[6], albertaYearAverage[6],
           canadaYearAverage[6];

    while (fgets(line, MaxLineLength, statscan) != NULL)
    {

        sscanf(line, "%[^,\n],%[^,\n],%*[^,],%[^,\n],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,\n]", refDate, geo, ageGroup, value);

        removeQuotation(refDate);
        removeQuotation(geo);
        removeQuotation(ageGroup);
        removeQuotation(value);

        // calculate provincial averages
        if (strcmp(geo, "Ontario") == 0 && strlen(value) > 0)
        {
            ontarioCount++;
            ontarioSum += atof(value);
        }
        if (strcmp(geo, "Quebec") == 0 && strlen(value) > 0)
        {
            quebecCount++;
            quebecSum += atof(value);
        }
        if (strcmp(geo, "British Columbia") == 0 && strlen(value) > 0)
        {
            bcCount++;
            bcSum += atof(value);
        }
        if (strcmp(geo, "Alberta") == 0 && strlen(value) > 0)
        {
            albertaCount++;
            albertaSum += atof(value);
        }

        // calculate national average
        if (strcmp(geo, "Canada (excluding territories)") == 0 && strlen(value) > 0)
        {
            canadaCount++;
            canadaSum += atof(value);
        }

        // calculate averages by year
        for (int i = 0; i <= 6; i++)
        {
            int year = atoi(refDate);
            if (year == 2015 + i && strlen(value) > 0)
            {
                if (strcmp(geo, "Ontario") == 0)
                {
                    ontarioYearCount[i]++;
                    ontarioYearSum[i] += atof(value);
                }
                else if (strcmp(geo, "Quebec") == 0)
                {
                    quebecYearCount[i]++;
                    quebecYearSum[i] += atof(value);
                }
                else if (strcmp(geo, "British Columbia") == 0)
                {
                    bcYearCount[i]++;
                    bcYearSum[i] += atof(value);
                }
                else if (strcmp(geo, "Alberta") == 0)
                {
                    albertaYearCount[i]++;
                    albertaYearSum[i] += atof(value);
                }
                else if (strcmp(geo, "Canada (excluding territories)") == 0)
                {
                    canadaYearCount[i]++;
                    canadaYearSum[i] += atof(value);
                }
            }
        }

        // calculate averages by age group
        for (int i = 0; i <= 2; i++)
        {
            if (strcmp(ageGroup, ageGroupArray[i]) == 0 && strlen(value) > 0)
            {
                if (strcmp(geo, "Ontario") == 0)
                {
                    ontarioAgeCount[i]++;
                    ontarioAgeSum[i] += atof(value);
                }
                else if (strcmp(geo, "Quebec") == 0)
                {
                    quebecAgeCount[i]++;
                    quebecAgeSum[i] += atof(value);
                }
                else if (strcmp(geo, "British Columbia") == 0)
                {
                    bcAgeCount[i]++;
                    bcAgeSum[i] += atof(value);
                }
                else if (strcmp(geo, "Alberta") == 0)
                {
                    albertaAgeCount[i]++;
                    albertaAgeSum[i] += atof(value);
                }
                else if (strcmp(geo, "Canada (excluding territories)") == 0)
                {
                    canadaAgeCount[i]++;
                    canadaAgeSum[i] += atof(value);
                }
            }
        }
    }

    // province with highest/lowest average
    double averages[] = {ontarioSum / ontarioCount, quebecSum / quebecCount, bcSum / bcCount, albertaSum / albertaCount, canadaSum / canadaCount};
    char *provinceArray[4] = {"Ontario", "Quebec", "British Columbia", "Alberta"};

    for (int i = 0; i < 4; i++)
    {
        int min = i;
        for (int j = 1 + i; j < 4; j++)
        {
            if (averages[j] < averages[min])
            {
                min = j;
            }
        }
        double tempDouble = averages[i];
        char *tempChar = provinceArray[i];
        averages[i] = averages[min];
        provinceArray[i] = provinceArray[min];
        averages[min] = tempDouble;
        provinceArray[min] = tempChar;
    }

    // provinces above/below national average
    double nationalAverage = canadaSum / canadaCount,
           belowNationalAverage[4],
           aboveNationalAverage[4];

    int belowCount = 0, aboveCount = 0;

    char *belowProvinceArray[4],
        *aboveProvinceArray[4];

    for (int i = 0; i < 4; i++)
    {
        if (averages[i] < nationalAverage)
        {
            belowNationalAverage[belowCount] = averages[i];
            belowProvinceArray[belowCount] = provinceArray[i];
            belowCount++;
        }
        else
        {
            aboveNationalAverage[aboveCount] = averages[i];
            aboveProvinceArray[aboveCount] = provinceArray[i];
            aboveCount++;
        }
    }

    // which province and year had the highest/lowest average
    for (int i = 0; i < 6; i++)
    {
        ontarioYearAverage[i] = ontarioYearSum[i] / ontarioYearCount[i];
        quebecYearAverage[i] = quebecYearSum[i] / quebecYearCount[i];
        bcYearAverage[i] = bcYearSum[i] / bcYearCount[i];
        albertaYearAverage[i] = albertaYearSum[i] / albertaYearCount[i];
        canadaYearAverage[i] = canadaYearSum[i] / canadaYearCount[i];
    }

    double highest = ontarioYearAverage[0], lowest = ontarioYearAverage[0];
    int highestYear, lowestYear;
    char *highestProvince, *lowestProvince;

    for (int i = 0; i < 6; i++)
    {
        if (ontarioYearAverage[i] > highest)
        {
            highest = ontarioYearAverage[i];
            highestProvince = "Ontario";
            highestYear = 2015 + i;
        }
        if (ontarioYearAverage[i] < lowest)
        {
            lowest = ontarioYearAverage[i];
            lowestProvince = "Ontario";
            lowestYear = 2015 + i;
        }
        if (quebecYearAverage[i] > highest)
        {
            highest = quebecYearAverage[i];
            highestProvince = "Quebec";
            highestYear = 2015 + i;
        }
        if (quebecYearAverage[i] < lowest)
        {
            lowest = quebecYearAverage[i];
            lowestProvince = "Quebec";
            lowestYear = 2015 + i;
        }
        if (bcYearAverage[i] > highest)
        {
            highest = bcYearAverage[i];
            highestProvince = "British Columbia";
            highestYear = 2015 + i;
        }
        if (bcYearAverage[i] < lowest)
        {
            lowest = bcYearAverage[i];
            lowestProvince = "British Columbia";
            lowestYear = 2015 + i;
        }
        if (albertaYearAverage[i] > highest)
        {
            highest = albertaYearAverage[i];
            highestProvince = "Alberta";
            highestYear = 2015 + i;
        }
        if (albertaYearAverage[i] < lowest)
        {
            lowest = albertaYearAverage[i];
            lowestProvince = "Alberta";
            lowestYear = 2015 + i;
        }
    }

    // print results

    printf("Question 1.\n");
    // print provincial averages
    printf("-----Provincial/National Averages-----\n");
    printf("Ontario:\t\t\t%.2lf\n", ontarioSum / ontarioCount);
    printf("Quebec:\t\t\t\t%.2lf\n", quebecSum / quebecCount);
    printf("British Columbia:\t\t%.2lf\n", bcSum / bcCount);
    printf("Alberta:\t\t\t%.2lf\n", albertaSum / albertaCount);
    // print national average
    printf("Canada:\t\t\t\t%.2lf\n\n", canadaSum / canadaCount);

    // print averages by year
    printf("------------------------------- Yearly Averages ------------------------------\n");
    printf("\t\t\t2015\t2016\t2017\t2018\t2019\t2020\t2021\n");
    printf("Ontario\t\t\t");
    for (int i = 0; i <= 6; i++)
    {
        printf("%.2lf\t", ontarioYearSum[i] / ontarioYearCount[i]);
    }
    printf("\n");

    printf("Quebec\t\t\t");
    for (int i = 0; i <= 6; i++)
    {
        printf("%.2lf\t", quebecYearSum[i] / quebecYearCount[i]);
    }
    printf("\n");

    printf("British Columbia\t");
    for (int i = 0; i <= 6; i++)
    {
        printf("%.2lf\t", bcYearSum[i] / bcYearCount[i]);
    }
    printf("\n");

    printf("Alberta\t\t\t");
    for (int i = 0; i <= 6; i++)
    {
        printf("%.2lf\t", albertaYearSum[i] / albertaYearCount[i]);
    }
    printf("\n");

    printf("Canada-wide\t\t");
    for (int i = 0; i <= 6; i++)
    {
        printf("%.2lf\t", canadaYearSum[i] / canadaYearCount[i]);
    }
    printf("\n\n");

    // print averages by age group
    printf("---------------------------- Averages by Age Group ---------------------------\n");
    printf("\t\t\t35 to 49 years\t50 to 64 years\t65 years and over\n");
    printf("Ontario\t\t\t");
    for (int i = 0; i <= 2; i++)
    {
        printf("%.2lf\t\t", ontarioAgeSum[i] / ontarioAgeCount[i]);
    }
    printf("\n");
    printf("Quebec\t\t\t");
    for (int i = 0; i <= 2; i++)
    {
        printf("%.2lf\t\t", quebecAgeSum[i] / quebecAgeCount[i]);
    }
    printf("\n");
    printf("British Columbia\t");
    for (int i = 0; i <= 2; i++)
    {
        printf("%.2lf\t\t", bcAgeSum[i] / bcAgeCount[i]);
    }
    printf("\n");
    printf("Alberta\t\t\t");
    for (int i = 0; i <= 2; i++)
    {
        printf("%.2lf\t\t", albertaAgeSum[i] / albertaAgeCount[i]);
    }
    printf("\n");
    printf("Canada-wide\t\t");
    for (int i = 0; i <= 2; i++)
    {
        printf("%.2lf\t\t", canadaAgeSum[i] / canadaAgeCount[i]);
    }
    printf("\n\n");

    // highest and lowest provincial averages
    printf("Question 2.\n");
    printf("The province with the highest average is %s with %.2lf percent.\n", provinceArray[3], averages[3]);
    printf("The province with the lowest average is %s with %.2lf percent.\n\n", provinceArray[0], averages[0]);

    // provinces with higher averages than national average
    printf("Question 3.\n");
    printf("The national average is %.2lf percent.\n", canadaSum / canadaCount);
    printf("Province(s) with lower averages than the national average:\n");
    for (int i = 0; i < belowCount; i++)
    {
        printf("- %s with %.2lf percent.\n", belowProvinceArray[i], belowNationalAverage[i]);
    }
    printf("Province(s) with higher averages than the national average:\n");
    for (int i = 0; i < aboveCount; i++)
    {
        printf("- %s with %.2lf percent.\n\n", aboveProvinceArray[i], aboveNationalAverage[i]);
    }

    // province and year with highest/lowest average
    printf("Question 4.\n");
    printf("The province with the highest average is %s with %.2lf percent in %d.\n", highestProvince, highest, highestYear);
    printf("The province with the lowest average is %s with %.2lf percent in %d.\n\n", lowestProvince, lowest, lowestYear);

    // plotting the data
    fprintf(plot1, "Year Ontario Quebec Alberta BritishColumbia Canada\n");
    for (int i = 0; i <= 6; i++)
    {
        fprintf(plot1, "%d %.2lf %.2lf %.2lf %.2lf %.2lf\n", 2015 + i, ontarioYearAverage[i], quebecYearAverage[i], albertaYearAverage[i], bcYearAverage[i], canadaYearAverage[i]);
    }

    fprintf(plot2, "AgeGroup Canada\n");
    for (int i = 0; i <= 2; i++)
    {
        fprintf(plot2, "\"%s\" %.2lf\n", ageGroupArray[i], canadaAgeSum[i] / canadaAgeCount[i]);
    }

    fclose(statscan);

    return 0;
}