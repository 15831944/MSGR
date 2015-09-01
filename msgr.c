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
    int tTableXdim;
    int tTableYdim;

    double time;

    tTableXdim = NumColumns(timeFile);
    tTableYdim = NumRows(timeFile);
    x = NumColumns(fileName);
    y = NumRows(fileName);
    x++;
    y++;

    Entry eTable[x][y];
    Entry tTable[tTableXdim][tTableYdim];

    int idInstances[y];
    int rowQuantity[y];
    double clipLines[x][y];

    populateTable(eTable,x,y,fileName,"eTable.txt");
    populateTable(tTable,tTableXdim,tTableYdim,timeFile,"tTable.txt");

    printf("%i\n",strncmp("DWL_FaceMountTile","DWL_FaceMountTileSet",strlen("DWL_FaceMountTile")));
    printf("%i\n",strncmp("DWL_FaceMountTile","DWL_FaceMountTileSet",strlen("DWL_FaceMountTileSet")));
    printf("%i\n",strncmp("DWL_FaceMountTileSet","DWL_FaceMountTile",strlen("DWL_FaceMountTile")));
    //printf("%i\n",strncmp("DWL_FaceMountTileSet","DWL_FaceMountTile",strlen("DWL_FaceMountTileSet")));

<<<<<<< HEAD

    calculateTimes(eTable,x,y,tTable,tTableXdim,tTableYdim,idInstances,rowQuantity,&numEntries);

=======
>>>>>>> parent of ea73c0b... problem with strcmp simlilar dwl codes
    calculateTimes(eTable,x,y,tTable,tTableXdim,tTableYdim,idInstances,rowQuantity,&numEntries);

    printf("sizeof eTable = %u\n", (unsigned) sizeof eTable);

    printf("1st dimension = %u\n", (unsigned) BOUNDS(eTable));

    printf("2nd dimension = %u\n", (unsigned) BOUNDS(eTable[0]));

    printf("sizeof tTable = %u\n", (unsigned) sizeof tTable);

    printf("1st dimension = %u\n", (unsigned) BOUNDS(tTable));

    printf("2nd dimension = %u\n", (unsigned) BOUNDS(tTable[0]));

    system("PAUSE");
    return 0;
}

