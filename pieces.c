#include "ops.h"
void calculateTimes(int eTablex; int eTabley; int tTablex; int tTabley;
                      Entry eTable[eTablex][eTabley], int eTablex, int eTabley,
                      Entry tTable[tTablex][tTabley], int tTablex, int tTabley,
                      int idInstances[eTabley], int rowQuantity[eTabley], int *numEntries)
{
int index;
int numColours;
int totalCutCount;
int totalNumUnits;
int panelSaw;
int woodCnc;
int finishingLine;
int clipping;
int tmp;
int codeCount;

double averageTileSize;
double time;

char *partName;

for(index = 0; index < 21; index++)
{
    if(tTable[1][index].dVal != 1)
    {
        partName = tTable[0][index].str;
        SearchForId(partName, eTable, idInstances, eTablex, eTabley, &numEntries);

        numColours = checkColourDiff(idInstances, eTable, eTablex, eTabley, &numEntries);

        char *codes[numColours];//Must be defined after numColours has been assigned a value

        getColourCodes(idInstances, eTable, codes, eTablex, eTabley, numColours, &numEntries);
        totalCutCount = numCuts(idInstances, eTable, eTablex, eTabley, &numEntries);
        totalNumUnits = numUnits(idInstances, rowQuantity, eTable, eTablex, eTabley, &numEntries);
        averageTileSize = avgSize(idInstances, totalNumUnits, rowQuantity, eTable, eTablex, eTabley, &numEntries);

        panelSaw = (tTable[3][index].dVal * totalCutCount);
        woodCnc = (tTable[8][index].dVal * totalNumUnits);
        finishingLine = (tTable[12][index].dVal * totalNumUnits) + (tTable[14][index].dVal * (numColours - 1));
        clipping = (tTable[15][index].dVal * totalNumUnits);

        time = ((double)(tmp + panelSaw + woodCnc + finishingLine + clipping))/60;
        printf("%f\n",time);
        /*
        printf("%s", "Tiles = ");
        printf("%i", totalNumUnits);
        printf("%s", " ");
        printf("%s","Predicted: ");
        printf("%f", time);
        printf("%s\n", "mins");

        printf("%i", numColours);
        printf("%s\n", " Colour(s)");

        printf("%s\n", "Colour Codes: ");

        for(index = 0; index < (numColours); index++)
        {
            printf("%s", codes[index]);
            printf("%s", "-");
            codeCount = countColourCodes(idInstances, eTable, codes, eTablex, eTabley, numColours, index, &numEntries);
            printf("%s", "Number of Units: ");
            printf("%i\n", codeCount);
        }

        printf("%s","Panel Saw: ");
        printf("%i", (panelSaw/60));
        printf("%s\n","min");

        printf("%s","CNC: ");
        printf("%i",(woodCnc/60));
        printf("%s\n","min");

        printf("%s","Finishing Line: ");
        printf("%i",(finishingLine/60));
        printf("%s\n","min");

        printf("%s","clipping: ");
        printf("%i",(clipping/60));
        printf("%s\n","min");
        */
    }
}
}

double CalculateFaceMountTiles(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y)
{
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    double averageTileSize;
    double time;
    int tmp;
    int codeCount = 0;
    int index;
    int panelSaw;
    int woodCnc;
    int clipping;
    int finishingLine;

    char partName[] = {"DWL_FaceMountTile"};

    FILE *fileOut;
    fileOut = fopen("searchdata.txt", "a");

    SearchForId(partName, eTable, idInstances, x, y, &numEntries);
    numColours = checkColourDiff(idInstances, eTable, x, y, &numEntries);
    char *codes[numColours];

    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {


        getColourCodes(idInstances, eTable, codes, x, y, numColours, &numEntries);
        totalCutCount = numCuts(idInstances, eTable, x, y, &numEntries);
        totalNumUnits = numUnits(idInstances, rowQuantity, eTable, x, y, &numEntries);
        averageTileSize = avgSize(idInstances, totalNumUnits, rowQuantity, eTable, x, y, &numEntries);
        //extractDoubles(idInstances, clipLines, eTable, x, y, &numEntries, 35);
        printf("%i",totalCutCount);
/*
        if(totalNumUnits != 0)
            tmp = 1200;
        else
            tmp = 0;
*/
        tmp = 0;
//ensure that cnc timing is correct

        panelSaw = (45 * totalCutCount);
        woodCnc = (240 * totalNumUnits);
        finishingLine = (24 * totalNumUnits) + (1500 * (numColours - 1));
        clipping = (24 * totalNumUnits);

        time = ((double)(tmp + panelSaw + woodCnc + finishingLine + clipping))/60;


    printf("%s", "Tiles = ");
    printf("%i", totalNumUnits);
    printf("%s", " ");
    printf("%s","Predicted: ");
    printf("%f", time);
    printf("%s\n", "mins");

    printf("%i", numColours);
    printf("%s\n", " Colour(s)");

    printf("%s\n", "Colour Codes: ");

    for(index = 0; index < (numColours); index++)
    {
        printf("%s", codes[index]);
        printf("%s", "-");
        codeCount = countColourCodes(idInstances, eTable, codes, x, y, numColours, index, &numEntries);
        printf("%s", "Number of Units: ");
        printf("%i\n", codeCount);
    }

    printf("%s","Panel Saw: ");
    printf("%i", (panelSaw/60));
    printf("%s\n","min");

    printf("%s","CNC: ");
    printf("%i",(woodCnc/60));
    printf("%s\n","min");

    printf("%s","Finishing Line: ");
    printf("%i",(finishingLine/60));
    printf("%s\n","min");

    printf("%s","clipping: ");
    printf("%i",(clipping/60));
    printf("%s\n","min");


    fclose(fileOut);
    }

    fileOut = fopen("output.txt", "w");

    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
    fprintf(fileOut,"%s", "Part Name: ");
    fprintf(fileOut,"%s\n", partName);

    fprintf(fileOut,"%s", "Average tile size: ");
    fprintf(fileOut,"%f\n", averageTileSize);

    fprintf(fileOut,"%s","Predicted Time: ");
    fprintf(fileOut,"%f", time);
    fprintf(fileOut,"%s\n", "mins");

    fprintf(fileOut,"%s","Panel Saw: ");
    fprintf(fileOut,"%i", (panelSaw/60));
    fprintf(fileOut,"%s\n","min");

    fprintf(fileOut,"%s","CNC: ");
    fprintf(fileOut,"%i",(woodCnc/60));
    fprintf(fileOut,"%s\n","min");

    fprintf(fileOut,"%s","Finishing Line: ");
    fprintf(fileOut,"%i",(finishingLine/60));
    fprintf(fileOut,"%s\n","min");

    fprintf(fileOut,"%s","    ");
    fprintf(fileOut,"%i", numColours);
    fprintf(fileOut,"%s\n", " Colour(s)");

    fprintf(fileOut,"%s","    ");
    fprintf(fileOut,"%s\n", "Colour Codes: ");
    for(index = 0; index < (numColours); index++)
    {
        fprintf(fileOut,"%s", "        ");
        fprintf(fileOut,"%s", codes[index]);
        fprintf(fileOut,"%s", " - ");
        codeCount = countColourCodes(idInstances, eTable, codes, x, y, numColours, index, &numEntries);
        fprintf(fileOut,"%s", "Number of Units: ");
        fprintf(fileOut,"%i\n", codeCount);
    }

    fprintf(fileOut,"%s","clipping: ");
    fprintf(fileOut,"%i",(clipping/60));
    fprintf(fileOut,"%s\n","min");

    fprintf(fileOut,"%s", "Total Predicted time for ");
    fprintf(fileOut,"%s", partName);
    fprintf(fileOut,"%s", ": ");
    fprintf(fileOut,"%f", time);
    fprintf(fileOut,"%s", " mins");

    fclose(fileOut);
    }

return time;
}
/*
int CalculateHorizTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y)
{
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    int time;
    int tmp;
    char fileName[] = {"DWL_FM_HorizTile"};

    FILE *fileOut;
    fileOut = fopen("searchdata.txt", "a");

    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        SearchForId(fileName, eTable, idInstances, x, y, &numEntries);

        numColours = checkColourDiff(idInstances, eTable, x, y, &numEntries);
        totalCutCount = numCuts(idInstances, eTable, x, y, &numEntries);
        totalNumUnits = numUnits(idInstances, rowQuantity, eTable, x, y, &numEntries);
        //extractDoubles(idInstances, clipLines, eTable, x, y, &numEntries, 35);

        if(totalNumUnits != 0)
            tmp = 300;
        else
            tmp = 0;

        time = tmp + ((45 * totalCutCount) + (240 * totalNumUnits));


    fclose(fileOut);
    }
return time;
}

int CalculateMagTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y)
{
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    int time;
    int tmp;
    char fileName[] = {"DWL_FM_MagTile"};


    FILE *fileOut;
    fileOut = fopen("searchdata.txt", "a");

    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        SearchForId(fileName, eTable, idInstances, x, y, &numEntries);

        numColours = checkColourDiff(idInstances, eTable, x, y, &numEntries);
        totalCutCount = numCuts(idInstances, eTable, x, y, &numEntries);
        totalNumUnits = numUnits(idInstances, rowQuantity, eTable, x, y, &numEntries);
        //extractDoubles(idInstances, clipLines, eTable, x, y, &numEntries, 35);

        if(totalNumUnits != 0)
            tmp = 300;
        else
            tmp = 0;

        time = tmp + ((45 * totalCutCount) + (240 * totalNumUnits) + (300 * totalNumUnits));


    fclose(fileOut);
    }
return time;
}

int CalculateFramelessTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y)
{
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    int time;
    int tmp;
    char fileName[] = {"DWL_FM_FramelessTile"};

    FILE *fileOut;
    fileOut = fopen("searchdata.txt", "a");

    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        SearchForId(fileName, eTable, idInstances, x, y, &numEntries);

        numColours = checkColourDiff(idInstances, eTable, x, y, &numEntries);
        totalCutCount = numCuts(idInstances, eTable, x, y, &numEntries);
        totalNumUnits = numUnits(idInstances, rowQuantity, eTable, x, y, &numEntries);
        //extractDoubles(idInstances, clipLines, eTable, x, y, &numEntries, 35);

        if(totalNumUnits != 0)
            tmp = 300;
        else
            tmp = 0;

        time = tmp + ((45 * totalCutCount) + (240 * totalNumUnits) + (300 * totalNumUnits));


    fclose(fileOut);
    }
return time;
}
*/
