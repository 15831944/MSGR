#ifndef PIECES_H
#define PIECES_H

#include <stdio.h>
#include <stdlib.h>

double CalculateFaceMountTiles(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int numEntries, int x, int y);
int CalculateHorizTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y);
int CalculateMagTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y);
int CalculateFramelessTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y);

#endif // PIECES_H
