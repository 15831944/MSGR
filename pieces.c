#include "ops.h"
void calculateTimes(int eTablex; int eTabley; int tTablex; int tTabley;
                    Entry eTable[eTablex][eTabley], int eTablex, int eTabley,
                    Entry tTable[tTablex][tTabley], int tTablex, int tTabley,
                    int idInstances[eTabley], int rowQuantity[eTabley], int *numEntries, double *totalTime)
{
    int index;
    int cIndex;
    int numColours;
    int totalCutCount;
    int totalNumUnits;
    int panelSaw;
    int woodCnc;
    int finishingLine;
    int clipping;
    int tmp;
    int codeCount;

    double veneerRoom;
    double panelSawChangeBlade;
    double veneerWrapper;
    double magTileLine;
    double veneerPress;
    double stainBooth;
    double fabricGlueBooth;
    double paintBooth;
    double fabricWrap;
    double averageTileSize;
    double time;
    double standardDev;
    char *partName;

    FILE *fileOut;
    fileOut = fopen("output.txt", "w");
    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        for(index = 0; index < (tTabley - 1); index++)
        {
            if(tTable[1][index].dVal == 1)
            {
                numColours = 0;
                totalCutCount = 0;
                totalNumUnits = 0;
                averageTileSize = 0;
                panelSaw = 0;
                woodCnc = 0;
                finishingLine = 0;
                clipping = 0;
                time = 0;
                codeCount = 0;
                standardDev = 0;

                partName = malloc(strlen(tTable[0][index].str) + 1);
                strcpy(partName,tTable[0][index].str);

                if(SearchForId(partName, eTable, idInstances, eTablex, eTabley, numEntries))
                {
                    numColours = checkColourDiff(idInstances, eTable, eTablex, eTabley, numEntries);

                    char *codes[numColours];//Must be defined after numColours has been assigned a value

                    getColourCodes(idInstances, eTable, codes, eTablex, eTabley, numColours, numEntries);
                    totalCutCount = numCuts(idInstances, eTable, eTablex, eTabley, numEntries);
                    totalNumUnits = numUnits(idInstances, rowQuantity, eTable, eTablex, eTabley, numEntries);
                    averageTileSize = avgSize(idInstances, totalNumUnits, rowQuantity, eTable, eTablex, eTabley, numEntries);
                    standardDev = stdDev(idInstances, totalNumUnits, rowQuantity, eTable, eTablex, eTabley, numEntries);


                    veneerRoom = tTable[2][index].dVal * averageTileSize;

                    panelSaw = (tTable[3][index].dVal * totalNumUnits);

                    if(tTable[4][index].dVal != 0)
                        panelSawChangeBlade = tTable[4][index].dVal;
                    else
                        panelSawChangeBlade = 0;

                    veneerWrapper = tTable[5][index].dVal * averageTileSize;

                    magTileLine = tTable[6][index].dVal * totalNumUnits;

                    veneerPress = tTable[7][index].dVal * totalNumUnits;

                    // no value for lineal ft in msgr file how to measure?
                    //Perforator = tTable[8][index].dVal

                    woodCnc = (tTable[9][index].dVal * totalNumUnits);

                    stainBooth = tTable[10][index].dVal * totalNumUnits;

                    fabricGlueBooth = tTable[11][index].dVal * totalNumUnits;

                    paintBooth = tTable[9][index].dVal;

                    finishingLine = ((tTable[13][index].dVal * totalNumUnits) +
                                     (tTable[15][index].dVal * (numColours - 1)) +
                                     ((tTable[14][index].dVal * totalNumUnits) * numColours));

                    clipping = (tTable[16][index].dVal * totalNumUnits);

                    fabricWrap = tTable[17][index].dVal * totalNumUnits;

                    time = ((double)(veneerRoom + panelSaw + panelSawChangeBlade + veneerWrapper + magTileLine +
                                     veneerPress + woodCnc + stainBooth + fabricGlueBooth + paintBooth +paintBooth +
                                     finishingLine + clipping + fabricWrap))/60;

                    *totalTime = *totalTime + time;

                    fprintf(fileOut,"%s\n", "----------------------------------------------------------------------------");
                    fprintf(fileOut,"%s", "Part Name: ");
                    fprintf(fileOut,"%s\n", partName);

                    fprintf(fileOut,"%s", "Average tile size: ");
                    fprintf(fileOut,"%.1f", averageTileSize);
                    fprintf(fileOut,"%s\n"," m^2");
                    fprintf(fileOut,"%s", "        ");
                    fprintf(fileOut,"%s", "Std Dev:");
                    fprintf(fileOut,"%.1f\n", standardDev);

                    fprintf(fileOut,"%s","Predicted Time: ");
                    fprintf(fileOut,"%.1f", time);
                    fprintf(fileOut,"%s\n", " mins");

                    fprintf(fileOut,"%s","Panel Saw: ");
                    fprintf(fileOut,"%.1f", (((double)panelSaw)/60));
                    fprintf(fileOut,"%s\n"," min");

                    fprintf(fileOut,"%s","CNC: ");
                    fprintf(fileOut,"%.1f",(((double)woodCnc)/60));
                    fprintf(fileOut,"%s\n"," min");

                    fprintf(fileOut,"%s","Finishing Line: ");
                    fprintf(fileOut,"%.1f",(((double)finishingLine)/60));
                    fprintf(fileOut,"%s\n"," min");

                    fprintf(fileOut,"%s","    ");
                    fprintf(fileOut,"%i", (numColours));
                    fprintf(fileOut,"%s\n", " Colour(s)");

                    fprintf(fileOut,"%s","    ");
                    fprintf(fileOut,"%s\n", "Colour Codes: ");

                    for(cIndex = 0; cIndex < (numColours); cIndex++)
                    {
                        fprintf(fileOut,"%s", "        ");
                        fprintf(fileOut,"%s", codes[cIndex]);
                        fprintf(fileOut,"%s", " - ");
                        codeCount = countColourCodes(idInstances, eTable, codes, eTablex, eTabley, numColours, cIndex, numEntries);
                        fprintf(fileOut,"%s", "Number of Units: ");
                        fprintf(fileOut,"%i\n", codeCount);
                    }

                    fprintf(fileOut,"%s","clipping: ");
                    fprintf(fileOut,"%.1f",(((double)clipping)/60));
                    fprintf(fileOut,"%s\n"," min");

                    fprintf(fileOut,"%s", "Total Predicted time for ");
                    fprintf(fileOut,"%s", partName);
                    fprintf(fileOut,"%s", ": ");
                    fprintf(fileOut,"%.1f", time);
                    fprintf(fileOut,"%s\n", " mins");
                    fprintf(fileOut,"%s\n", "----------------------------------------------------------------------------");
                    fprintf(fileOut,"\n");

                    free(partName);
                    freePtrArray(codes, numColours);
                }
                else
                {
                partName = malloc(strlen(tTable[0][index].str) + 1);
                strcpy(partName,tTable[0][index].str);
                fprintf(fileOut,"%s", partName);
                fprintf(fileOut,"%s\n", " was ommited not Found in file");
                fprintf(fileOut,"\n");

                free(partName);

                }
            }
            else
            {
                partName = malloc(strlen(tTable[0][index].str) + 1);
                strcpy(partName,tTable[0][index].str);
                fprintf(fileOut,"%s", partName);
                fprintf(fileOut,"%s\n", " was ommited not in production");
                fprintf(fileOut,"\n");

                free(partName);
            }
            free(partName);
        }
        fclose(fileOut);
    }
}
