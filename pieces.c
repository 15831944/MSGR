#include "ops.h"

int CalculateFaceMountTiles(int x; int y; char fileName[], int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y)
{
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    int time;


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

        if(totaNumUnits != 0)
        {
            time = time + 1200;
        }

        time = ((45 * totalCutCount) + (240 * totalCutCount) +  (24 * totalNumUnits) + (1500 * (numColours - 1)) + (24 * totalNumUnits) + );


    fclose(fileOut);
    }
return time;
}

int CalculateHorizTile(int x; int y; char fileName[], int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y)
{
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    int time;


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

        if(totaNumUnits != 0)
        {
            time = time + 300;
        }

        time = ((45 * totalCutCount) + (240 * totalNumUnits));


    fclose(fileOut);
    }
return time;
}
