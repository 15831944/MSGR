#ifndef MSGR_H
#define MSGR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Entry 
{
        char *str;
        int iVal;
} Entry;

int NumRows(char fileName[]);
int NumColumns(char fileName[]);
void TokenizeLine(int x; int y; char currentLineStr[], Entry eTable[x][y], int yIndex, int x, int y);
#endif
