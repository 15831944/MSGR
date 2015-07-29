#include "ops.h"

int CalculateFaceMountTiles(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y)
{
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    int time;
    int tmp;
    char fileName[] = {"DWL_FaceMountTile"};

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
            tmp =  1200;
        else
            tmp = 0;

        time = tmp + ((45 * totalCutCount) + (240 * totalCutCount) +  (24 * totalNumUnits) + (1500 * (numColours - 1)) + (24 * totalNumUnits));


    fclose(fileOut);
    }
return time;
}

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
