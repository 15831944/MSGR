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
    char fileName[64];
    char timeFile[64] = {"timefile.msgr"};

    int numEntries = 0;
    double totalTime = 0;
    int x;
    int y;
    int tTableXdim;
    int tTableYdim;

    double time;

    FILE *fileOut;

    printf("%s\n","Input file to process: ");
    scanf("%s",fileName);
    printf("%s\n",fileName);


    tTableXdim = NumColumns(timeFile);
    tTableYdim = NumRows(timeFile);
    x = NumColumns(fileName);
    y = NumRows(fileName);


    Entry eTable[x][y];
    Entry tTable[tTableXdim][tTableYdim];

    int idInstances[y];
    int rowQuantity[y];
    double clipLines[x][y];

    populateTable(eTable,x,y,fileName, "eTable.txt");
    populateTable(tTable,tTableXdim,tTableYdim,timeFile, "tTable.txt");

    calculateTimes(eTable,x,y,tTable,tTableXdim,tTableYdim,idInstances,rowQuantity,&numEntries, &totalTime);

    fileOut = fopen("output.txt", "a");
    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        fprintf(fileOut,"%s","Predicted Time For All Tiles: ");
        fprintf(fileOut,"%.2f", totalTime);
        fprintf(fileOut,"%s\n","min");
    }
    fclose(fileOut);
    printf("sizeof eTable = %u\n", (unsigned) sizeof eTable);

    printf("1st dimension = %u\n", (unsigned) BOUNDS(eTable));

    printf("2nd dimension = %u\n", (unsigned) BOUNDS(eTable[0]));

    printf("sizeof tTable = %u\n", (unsigned) sizeof tTable);

    printf("1st dimension = %u\n", (unsigned) BOUNDS(tTable));

    printf("2nd dimension = %u\n", (unsigned) BOUNDS(tTable[0]));

    system("PAUSE");
    return 0;
}

