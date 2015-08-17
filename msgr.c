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
    char fileName[64] = {"rtest.txt"};

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


    temp = CalculateFaceMountTiles(idInstances, rowQuantity, eTable, &numEntries, x, y);
    time = (double)temp;
    printf("%f\n", time);
/*
    temp = CalculateHorizTile(idInstances, rowQuantity, eTable, &numEntries, x, y);
    time = (double)temp;
    printf("%f\n", time);

    temp = CalculateMagTile(idInstances, rowQuantity, eTable, &numEntries, x, y);
    time = (double)temp;
    printf("%f\n", time);
*/

    printf("sizeof eTable = %u\n", (unsigned) sizeof eTable);

    printf("1st dimension = %u\n", (unsigned) BOUNDS(eTable));

    printf("2nd dimension = %u\n", (unsigned) BOUNDS(eTable[0]));

    system("PAUSE");
    return 0;
}

