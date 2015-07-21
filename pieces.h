#ifndef PIECES_H
#define PIECES_H

#include <stdio.h>
#include <stdlib.h>

int CalculateFaceMountTiles(int x; int y; char fileName[], int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int numEntries, int x, int y);
int CalculateHorizTile(int x; int y; char fileName[], int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y);
int CalculateMagTile(int x; int y; char fileName[], int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y);

#endif // PIECES_H
