#include "ops.h"

int CalculateFaceMountTiles(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y)
{
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    int time;
    int tmp;
    int codeCount = 0;
    int index;
    int panelSaw;
    int woodCnc;
    int clipping;
    int finishingLine;

    char fileName[] = {"DWL_FaceMountTile"};

    FILE *fileOut;
    fileOut = fopen("searchdata.txt", "a");

    SearchForId(fileName, eTable, idInstances, x, y, &numEntries);
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

        time = (tmp + panelSaw + woodCnc + finishingLine + clipping)/60;


        printf("%s", "Tiles = ");
    printf("%i", totalNumUnits);
    printf("%s", " ");
    printf("%s","Predicted: ");
    printf("%i", time);
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
    fprintf(fileOut,"%s", "Tiles = ");
    fprintf(fileOut,"%i", totalNumUnits);
    fprintf(fileOut,"%s", " ");
    fprintf(fileOut,"%s","Predicted: ");
    fprintf(fileOut,"%i", time);
    fprintf(fileOut,"%s\n", "mins");

    fprintf(fileOut,"%i", numColours);
    fprintf(fileOut,"%s\n", " Colour(s)");

    fprintf(fileOut,"%s\n", "Colour Codes: ");

    for(index = 0; index < (numColours); index++)
    {
        fprintf(fileOut,"%s", codes[index]);
        fprintf(fileOut,"%s", "-");
        codeCount = countColourCodes(idInstances, eTable, codes, x, y, numColours, index, &numEntries);
        fprintf(fileOut,"%s", "Number of Units: ");
        fprintf(fileOut,"%i\n", codeCount);
    }

    fprintf(fileOut,"%s","Panel Saw: ");
    fprintf(fileOut,"%i", (panelSaw/60));
    fprintf(fileOut,"%s\n","min");

    fprintf(fileOut,"%s","CNC: ");
    fprintf(fileOut,"%i",(woodCnc/60));
    fprintf(fileOut,"%s\n","min");

    fprintf(fileOut,"%s","Finishing Line: ");
    fprintf(fileOut,"%i",(finishingLine/60));
    fprintf(fileOut,"%s\n","min");

    fprintf(fileOut,"%s","clipping: ");
    fprintf(fileOut,"%i",(clipping/60));
    fprintf(fileOut,"%s\n","min");
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
