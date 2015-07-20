#ifndef OPS_H
#define OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msgr.h"

int NumRows(char fileName[]);
int NumColumns(char fileName[]);
void TokenizeLine(int x; int y; char currentLineStr[], Entry eTable[x][y], int yIndex, int x, int y);
void SearchForId(int x; int y; char stringToFind[], Entry eTable[x][y], int idInstances[y], int x, int y, int *numEntries);
int IsDouble(const char *str);
char* mystrsep(char** stringp, const char* delim);
int checkColourDiff(int x; int y; int idInstances[y], Entry eTable[x][y], int x, int y, int *numEntries);
int numCuts(int x; int y; int idInstances[y], Entry eTable[x][y], int x, int y, int *numEntries);
int numUnits(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries);
int extractDoubles(int x; int y; int idInstances[y], double clipLines[x][y], Entry eTable[x][y], int x, int y, int *numEntries, int column);

#endif // OPS_H_INCLUDED
