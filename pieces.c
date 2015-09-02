#include "ops.h"
void calculateTimes(int eTablex; int eTabley; int tTablex; int tTabley;
                    Entry eTable[eTablex][eTabley], int eTablex, int eTabley,
                    Entry tTable[tTablex][tTabley], int tTablex, int tTabley,
                    int idInstances[eTabley], int rowQuantity[eTabley], int *numEntries)
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

    double averageTileSize;
    double time;

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
        for(index = 0; index < (tTabley); index++)
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

                printf("%s\n", tTable[0][index].str);
                printf("%s\n", eTable[5][8].str);


                partName = malloc(strlen(tTable[0][index].str) + 1);
                strcpy(partName,tTable[0][index].str);

                if(SearchForId(partName, eTable, idInstances, eTablex, eTabley, numEntries))
                {
                    numColours = checkColourDiff(idInstances, eTable, eTablex, eTabley, numEntries);

                    char *codes[numColours];//Must be defined after numColours has been assigned a value
                     printf("%i\n", numColours);
                     printf("%i\n", *numEntries);



                    getColourCodes(idInstances, eTable, codes, eTablex, eTabley, numColours, numEntries);
                    //int foo;
                    //for(foo = 0; 0 < numEntries; foo++)
/*
                        printf("%i\n",idInstances[0]);
                        printf("%i\n",idInstances[1]);
                        printf("%i\n",idInstances[2]);
                        printf("\n");

                        printf("%s\n", eTable[5][1].str);
                        printf("%s\n", eTable[5][2].str);
                        printf("%s\n", eTable[5][3].str);
                          printf("\n");

                        printf("%s\n", eTable[5][2].str);
                        printf("%s\n", eTable[5][3].str);
                        printf("%s\n", eTable[5][4].str);
                        printf("\n");
*/

                    //codes[0] = eTable[5][1].str;
                    //codes[1] = eTable[5][2].str;
                    //codes[2] = eTable[5][3].str;
                    //codes[0] = eTable[5][5].str;
                    //codes[4] = eTable[5][5].str;

                    totalCutCount = numCuts(idInstances, eTable, eTablex, eTabley, numEntries);
                    totalNumUnits = numUnits(idInstances, rowQuantity, eTable, eTablex, eTabley, numEntries);
                    averageTileSize = avgSize(idInstances, totalNumUnits, rowQuantity, eTable, eTablex, eTabley, numEntries);

                    panelSaw = (tTable[3][index].dVal * totalCutCount);
                    woodCnc = (tTable[8][index].dVal * totalNumUnits);

                    finishingLine = ((tTable[12][index].dVal * totalNumUnits) + (tTable[14][index].dVal * (numColours - 1)) +
                                     ((tTable[13][index].dVal * totalNumUnits) * numColours));

                    clipping = (tTable[15][index].dVal * totalNumUnits);

                    time = ((double)(panelSaw + woodCnc + finishingLine + clipping))/60;
/*
                    printf("%s\n",eTable[5][0].str);
                    printf("%s\n",eTable[5][1].str);
                    printf("%s\n",eTable[5][2].str);
                    printf("%s\n",eTable[5][3].str);
                    printf("%s\n",eTable[5][4].str);
                    printf("%s\n",eTable[5][5].str);
                    printf("\n");
  */

                    //printf("%s\n", codes[4]);
                    //printf("%s\n", codes[5]);

                    fprintf(fileOut,"%s\n", "----------------------------------------------------------------------------");
                    fprintf(fileOut,"%s", "Part Name: ");
                    fprintf(fileOut,"%s\n", partName);

                    fprintf(fileOut,"%s", "Average tile size: ");
                    fprintf(fileOut,"%f\n", averageTileSize);

                    fprintf(fileOut,"%s","Predicted Time: ");
                    fprintf(fileOut,"%.1f", time);
                    fprintf(fileOut,"%s\n", "mins");

                    fprintf(fileOut,"%s","Panel Saw: ");
                    fprintf(fileOut,"%i", (panelSaw/60));
                    fprintf(fileOut,"%s\n","min");

                    fprintf(fileOut,"%s","CNC: ");
                    fprintf(fileOut,"%i",(woodCnc/60));
                    fprintf(fileOut,"%s\n","min");

                    fprintf(fileOut,"%s","Finishing Line: ");
                    fprintf(fileOut,"%i",(finishingLine/60));
                    fprintf(fileOut,"%s\n","min");

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
                    fprintf(fileOut,"%i",(clipping/60));
                    fprintf(fileOut,"%s\n","min");

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
        }
        fclose(fileOut);
    }
}
