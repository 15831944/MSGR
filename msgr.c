#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msgr.h"
#include "ops.h"
#include "pieces.h"

#define BOUNDS(a) ((sizeof (a))/(sizeof ((a)[0])))

int main(int argc, char *argv[])
{

    char stringToFind[256] = {"DWL_FaceMountTile"};
    char fileName[64] = {"rtest.txt"};
    char timeFile[64] = {"timefile.msgr"};
    int numEntries = 0;
    int x;
    int y;
    double time;
    double temp;

    x = NumColumns(fileName);
    y = NumRows(fileName);

    Entry eTable[x][y];
    Entry tTable[36][21];

    int idInstances[y];
    int rowQuantity[y];
    double clipLines[x][y];

    populateTable(tTable,x,y,timeFile);
   // populateTable(eTable,x,y,fileName);

    int xindex;
    int yindex;

    printf("%s\n",tTable[0][0].str);
    printf("%f\n",tTable[1][0].dVal);
    printf("%f\n",tTable[2][0].dVal);
    printf("%f\n",tTable[3][0].dVal);
    printf("%f\n",tTable[4][0].dVal);
    printf("%f\n",tTable[5][0].dVal);
    printf("%f\n",tTable[6][0].dVal);

    printf("%s\n",tTable[0][1].str);
    printf("%f\n",tTable[1][1].dVal);
    printf("%f\n",tTable[2][1].dVal);
    printf("%f\n",tTable[3][1].dVal);
    printf("%f\n",tTable[4][1].dVal);
    printf("%f\n",tTable[5][1].dVal);
    printf("%f\n",tTable[6][1].dVal);

for(yindex = 0; yindex < 0; yindex++)
{
    for(xindex = 0; xindex < 35; xindex++)
    {
        printf("%s\n",tTable[xindex][yindex].str);
        printf("%f\n",tTable[xindex][yindex].dVal);
    }
}

    temp = CalculateFaceMountTiles(idInstances, rowQuantity, eTable, &numEntries, x, y);
    time = temp;
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

