#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msgr.h"
#include "ops.h"
#include "pieces.h"

#define BOUNDS(a) ((sizeof (a))/(sizeof ((a)[0])))
#define FILENAME_SIZE 64

int main(int argc, char *argv[])
{


    char fileName[FILENAME_SIZE];
    char timeFile[FILENAME_SIZE] = {"timefile.msgr"};
    char outputFile[FILENAME_SIZE];
    int numEntries = 0;
    double totalTime = 0;
    int x;
    int y;
    int tTableXdim;
    int tTableYdim;

    FILE *fileOut;
/*
    if ( argc != 3 )
    {
        printf("usage: %s filename", argv[0] );
        printf("usage: %s input File", argv[1] );
        printf("usage: %s output File", argv[2] );
    }
    else
    {
        strcpy(fileName, argv[1]);
        strcpy(outputFile, argv[2]);
    }
  */

    strcpy(fileName, "dtest.txt");
    strcpy(outputFile, "output.txt");

    tTableXdim = NumColumns(timeFile);
    tTableYdim = NumRows(timeFile);
    x = NumColumns(fileName);
    y = NumRows(fileName);


    Entry eTable[x][y];
    Entry tTable[tTableXdim][tTableYdim];

    int idInstances[y];
    int rowQuantity[y];
//    double clipLines[x][y];

    populateTable(eTable,x,y,fileName);
    populateTable(tTable,tTableXdim,tTableYdim,timeFile);

    calculateTimes(eTable,x,y,tTable,tTableXdim,tTableYdim,idInstances,rowQuantity,&numEntries, &totalTime, outputFile);

    fileOut = fopen(outputFile, "a");
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

