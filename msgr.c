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
    int tTableXdim;
    int tTableYdim;

    tTableXdim = NumColumns(timeFile);
    tTableYdim = NumRows(timeFile);
    x = NumColumns(fileName);
    y = NumRows(fileName);


    Entry eTable[x][y];
    Entry tTable[tTableXdim][tTableYdim];

    int idInstances[y];
    int rowQuantity[y];
    double clipLines[x][y];

    populateTable(eTable,x,y,fileName);
    populateTable(tTable,tTableXdim,tTableYdim,timeFile);
    printf("%s\n", tTable[0][0].str);
    printf("%f\n", tTable[1][0].dVal);

    //printf("%s\n", table[2][0].str);
    printf("%f\n", tTable[2][0].dVal);

    //printf("%s\n", table[3][0].str);
    printf("%f\n", tTable[3][0].dVal);

        int ty;
        int tx;
        //for(ty = 0; y < tTableYdim; ty++)
        //{

            for(tx = 0; x < tTableXdim; tx++)
            {
                printf("%f\n",tTable[0][tx].dVal);
            }

        //}

    calculateTimes(eTable,x,y,tTable,tTableXdim,tTableYdim,idInstances,rowQuantity,&numEntries);


    /*
    temp = CalculateFaceMountTiles(idInstances, rowQuantity, eTable, &numEntries, x, y);
    time = temp;
    printf("%f\n", time);
    */
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

    printf("sizeof tTable = %u\n", (unsigned) sizeof tTable);

    printf("1st dimension = %u\n", (unsigned) BOUNDS(tTable));

    printf("2nd dimension = %u\n", (unsigned) BOUNDS(tTable[0]));

    system("PAUSE");
    return 0;
}

