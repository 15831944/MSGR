#ifndef PIECES_H
#define PIECES_H

#include <stdio.h>
#include <stdlib.h>

void calculateTimes(int eTablex; int eTabley; int tTablex; int tTabley; Entry eTable[eTablex][eTabley], int eTablex,
                    int eTabley, Entry tTable[tTablex][tTabley], int tTablex, int tTabley,
                    int idInstances[eTabley], int rowQuantity[eTabley], int *numEntries);

double CalculateFaceMountTiles(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int numEntries, int x, int y);
int CalculateHorizTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y);
int CalculateMagTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y);
int CalculateFramelessTile(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int *numEntries, int x, int y);

#endif // PIECES_H
