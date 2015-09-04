#ifndef PIECES_H
#define PIECES_H

#include <stdio.h>
#include <stdlib.h>

void calculateTimes(int eTablex; int eTabley; int tTablex; int tTabley; Entry eTable[eTablex][eTabley], int eTablex,
                    int eTabley, Entry tTable[tTablex][tTabley], int tTablex, int tTabley,
                    int idInstances[eTabley], int rowQuantity[eTabley], int *numEntries, double *totalTime, char outputFile[]);

#endif // PIECES_H
