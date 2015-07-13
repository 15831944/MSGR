#ifndef MSGR_H
#define MSGR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Entry 
{
        char *str;
        double dVal;
} Entry;

int NumRows(char fileName[]);
int NumColumns(char fileName[]);
void TokenizeLine(int x; int y; char currentLineStr[], Entry eTable[x][y], int yIndex, int x, int y);
void SearchForId(int x; int y; char stringToFind[], Entry eTable[x][y], int idInstances[y], int x, int y, int *numEntries);
int IsDouble(const char *str);
char* mystrsep(char** stringp, const char* delim);
int checkColourDiff(int x; int y; int idInstances[y], Entry eTable[x][y], int x, int y, int *numEntries);
#endif
