#ifndef OPS_H
#define OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msgr.h"

void freePtrArray(char** array, int count);
void populateTable(int x; int y; Entry table[x][y], int x, int y, char fileName[], char tableName[]);
int NumRows(char fileName[]);
int NumColumns(char fileName[]);
void TokenizeLine(int x; int y; char currentLineStr[], Entry eTable[x][y], int yIndex, int x, int y);
int SearchForId(int x; int y; char stringToFind[], Entry eTable[x][y], int idInstances[y], int x, int y, int *numEntries);
int IsDouble(const char *str);
char* mystrsep(char** stringp, const char* delim);
int checkColourDiff(int x; int y; int idInstances[y], Entry eTable[x][y], int x, int y, int *numEntries);
void getColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int *numEntries);
int countColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int index, int *numEntries);
int numCuts(int x; int y; int idInstances[y], Entry eTable[x][y], int x, int y, int *numEntries);
int numUnits(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries);
int extractDoubles(int x; int y; int idInstances[y], double clipLines[x][y], Entry eTable[x][y], int x, int y, int *numEntries, int column);
double stdDev(int x; int y; int idInstances[y], int totalNumUnits, int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries);

double avgSize(int x; int y; int idInstances[y], int totalNumUnits, int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries);

#endif // OPS_H_INCLUDED
