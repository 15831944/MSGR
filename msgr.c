#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msgr.h"
#include "ops.h"
#include "pieces.h"

#define BOUNDS(a) ((sizeof (a))/(sizeof ((a)[0])))

int main(int argc, char *argv[])
{
    char currentLineStr[8192];
    char stringToFind[256] = {"DWL_FaceMountTile"};
    char fileName[64] = {"dtest.txt"};

    int x = 150;
    int y = 300;
    int yIndex = 0;
    int i;
    int temp;
    double time;
    int n;
    int diffCount;
    int numEntries = 0;
    int cutCount;
    int totalNumUnits;

    x = NumColumns(fileName);
    y = NumRows(fileName);

    Entry eTable[x][y];
    int idInstances[y];
    int rowQuantity[y];
    double clipLines[x][y];
    FILE *fileIn;
    FILE *fileOut;
    fileIn = fopen(fileName, "r");

    if(fileIn == 0)
    {
        perror("Cannot open input file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        printf("%s\n", "fileIn Opened");
        fgets(currentLineStr, 8192, fileIn);

        while (currentLineStr[0] == '#')
            fgets(currentLineStr, 8192, fileIn);

        TokenizeLine(currentLineStr, eTable, yIndex, x, y);
        yIndex++;

        while(fgets(currentLineStr, 8192, fileIn) != NULL)
        {
            TokenizeLine(currentLineStr, eTable, yIndex, x, y);
            yIndex++;
        }
        fclose(fileIn);
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
        printf("%i\n", x);
        for(i = 0; i < y; i++)
        {
            for( n = 0; (n < (x - 1)); n++)
            {
                if(eTable[n][i].dVal != 0)
                {
                    fprintf(fileOut, "%f", eTable[n][i].dVal);
                    fprintf(fileOut, "%s", "|");
                }
                else
                {
                    fprintf(fileOut, "%s", eTable[n][i].str);
                    fprintf(fileOut, "%s", "|");
                }
            }
            fprintf(fileOut, "%s", "\n");
        }
    }

    fileOut = fopen("searchdata.txt", "w");

    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        SearchForId(stringToFind, eTable, idInstances, x, y, &numEntries);
    // print line numbers for each intance returned from search
        for(n = 0; n < numEntries; n++)
            printf("%i\n", idInstances[n]);
        diffCount = checkColourDiff(idInstances, eTable, x, y, &numEntries);
        cutCount = numCuts(idInstances, eTable, x, y, &numEntries);
        totalNumUnits = numUnits(idInstances, rowQuantity, eTable, x, y, &numEntries);
        extractDoubles(idInstances, clipLines, eTable, x, y, &numEntries, 35);

        fprintf(fileOut, "%s", stringToFind);
        fprintf(fileOut, "%s", "|");
        fprintf(fileOut, "%i", diffCount);
        fprintf(fileOut, "%s", "|");
        fprintf(fileOut, "%i", totalNumUnits);
        fprintf(fileOut, "%s", "|");
        fprintf(fileOut, "%i", cutCount);
        fprintf(fileOut, "%s", "\n");

        SearchForId("DWL_LowMadonna", eTable, idInstances, x, y, &numEntries);
    // print line numbers for each intance returned from search
        for(n = 0; n < numEntries; n++)
            printf("%i\n", idInstances[n]);
        diffCount = checkColourDiff(idInstances, eTable, x, y, &numEntries);
        cutCount = numCuts(idInstances, eTable, x, y, &numEntries);
        totalNumUnits = numUnits(idInstances, rowQuantity, eTable, x, y, &numEntries);
        extractDoubles(idInstances, clipLines, eTable, x, y, &numEntries, 35);

        fprintf(fileOut, "%s", "DWL_LowMadonna");
        fprintf(fileOut, "%s", "|");
        fprintf(fileOut, "%i", diffCount);
        fprintf(fileOut, "%s", "|");
        fprintf(fileOut, "%i", totalNumUnits);
        fprintf(fileOut, "%s", "|");
        fprintf(fileOut, "%i", cutCount);
        fprintf(fileOut, "%s", "\n");

    }

    temp = CalculateFaceMountTiles("DWL_FaceMountTile", idInstances, rowQuantity, eTable, &numEntries, x, y);
    time = (double)temp;
    printf("%f\n", time);
    printf("sizeof eTable = %u\n", (unsigned) sizeof eTable);

    printf("1st dimension = %u\n", (unsigned) BOUNDS(eTable));

    printf("2nd dimension = %u\n", (unsigned) BOUNDS(eTable[0]));

    system("PAUSE");
    return 0;
}

