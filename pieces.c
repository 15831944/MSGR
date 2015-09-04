#include "ops.h"

void calculateTimes(int eTablex; int eTabley; int tTablex; int tTabley;
                    Entry eTable[eTablex][eTabley], int eTablex, int eTabley,
                    Entry tTable[tTablex][tTabley], int tTablex, int tTabley,
                    int idInstances[eTabley], int rowQuantity[eTabley], int *numEntries,
                    double *totalTime, char outputFile[])
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
    int codeCount;

    double fabricWrap;
    double microFilm;
    double doorLine;
    double profileSander;
    double metalDoubleSaw;
    double metalCnc;
    double ceilingTrackPunch;
    double upperPunch;
    double lowerPunch;
    double wingPunch;
    double doubleHaunch;
    double singleHaunch;
    double doorHaunch;
    double kitting;
    double assembly;
    double powderCoat;
    double toolCrib;
    double veneerRoom;
    double veneerWrapper;
    double magTileLine;
    double veneerPress;
    double stainBooth;
    double fabricGlueBooth;
    double paintBooth;
    double averageTileSize;
    double time;
    double standardDev;
    char *partName;

    FILE *fileOut;
    fileOut = fopen(outputFile, "w");
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
                fabricWrap = 0;
                microFilm = 0;
                doorLine = 0;
                profileSander = 0;
                metalDoubleSaw = 0;
                metalCnc = 0;
                ceilingTrackPunch = 0;
                upperPunch = 0;
                lowerPunch = 0;
                wingPunch = 0;
                doubleHaunch = 0;
                singleHaunch = 0;
                doorHaunch = 0;
                kitting = 0;
                assembly = 0;
                powderCoat = 0;
                toolCrib = 0;

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
                        panelSaw = panelSaw +tTable[4][index].dVal;

                    veneerWrapper = tTable[5][index].dVal * averageTileSize;

                    magTileLine = tTable[6][index].dVal * totalNumUnits;

                    veneerPress = tTable[7][index].dVal * totalNumUnits;

                    // no value for lineal ft in msgr file how to measure?
                    //Perforator = tTable[8][index].dVal

                    woodCnc = (tTable[9][index].dVal * totalNumUnits);

                    stainBooth = tTable[10][index].dVal * totalNumUnits;

                    fabricGlueBooth = tTable[11][index].dVal * totalNumUnits;

                    paintBooth = tTable[12][index].dVal * totalNumUnits;

                    finishingLine = ((tTable[13][index].dVal * totalNumUnits) +
                                     (tTable[15][index].dVal * (numColours - 1)) +
                                     ((tTable[14][index].dVal * totalNumUnits) * numColours));

                    clipping = (tTable[16][index].dVal * totalNumUnits);

                    fabricWrap = tTable[17][index].dVal * totalNumUnits;

                    microFilm = tTable[18][index].dVal * totalNumUnits;
                    doorLine = tTable[19][index].dVal * totalNumUnits;
                    profileSander = tTable[20][index].dVal * totalNumUnits;
                    // bpgEdgePrep = tTable[17][index].dVal
                    //  bpgMasking
                    metalDoubleSaw = tTable[23][index].dVal * totalNumUnits;
                    metalCnc = tTable[24][index].dVal * totalNumUnits;
                    ceilingTrackPunch = tTable[25][index].dVal * totalNumUnits;
                    upperPunch = tTable[26][index].dVal * totalNumUnits;
                    lowerPunch = tTable[27][index].dVal * totalNumUnits;
                    wingPunch = tTable[28][index].dVal * totalNumUnits;
                    doubleHaunch = tTable[29][index].dVal * totalNumUnits;
                    singleHaunch = tTable[30][index].dVal * totalNumUnits;
                    doorHaunch = tTable[31][index].dVal * totalNumUnits;
                    kitting = tTable[32][index].dVal * totalNumUnits;
                    assembly = tTable[33][index].dVal * totalNumUnits;
                    powderCoat = tTable[34][index].dVal * totalNumUnits;
                    toolCrib = tTable[35][index].dVal * totalNumUnits;



                    time = ((double)(veneerRoom + panelSaw + veneerWrapper + magTileLine +
                                     veneerPress + woodCnc + stainBooth + fabricGlueBooth + paintBooth +paintBooth +
                                     finishingLine + clipping + fabricWrap))/60;

                    *totalTime = *totalTime + time;

                    fprintf(fileOut,"%s\n", "----------------------------------------------------------------------------");
                    fprintf(fileOut,"%s", "Part Name: ");
                    fprintf(fileOut,"%s\n", partName);



                    if (averageTileSize != 0)
                    {
                        fprintf(fileOut,"%s", "Average tile size: ");
                        fprintf(fileOut,"%.1f", averageTileSize);
                        fprintf(fileOut,"%s\n"," m^2");
                        fprintf(fileOut,"%s", "        ");
                        fprintf(fileOut,"%s", "Std Dev:");
                        fprintf(fileOut,"%.1f\n", standardDev);
                    }

                    if(veneerRoom != 0)
                    {
                        fprintf(fileOut,"%s","Veneer Room: ");
                        fprintf(fileOut,"%.1f", ((veneerRoom)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(panelSaw != 0)
                    {
                        fprintf(fileOut,"%s","Panel Saw: ");
                        fprintf(fileOut,"%.1f", (((double)panelSaw)/60));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(veneerWrapper != 0)
                    {
                        fprintf(fileOut,"%s","Veneer Wrapper: ");
                        fprintf(fileOut,"%.1f", ((veneerWrapper)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(magTileLine != 0)
                    {
                        fprintf(fileOut,"%s","Veneer Room: ");
                        fprintf(fileOut,"%.1f", ((magTileLine)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(veneerPress != 0)
                    {
                        fprintf(fileOut,"%s","Veneer Press: ");
                        fprintf(fileOut,"%.1f", ((veneerPress)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(woodCnc != 0)
                    {
                        fprintf(fileOut,"%s","CNC: ");
                        fprintf(fileOut,"%.1f",(((double)woodCnc)/60));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(stainBooth != 0)
                    {
                        fprintf(fileOut,"%s","Stain Booth: ");
                        fprintf(fileOut,"%.1f", ((stainBooth)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(fabricGlueBooth != 0)
                    {
                        fprintf(fileOut,"%s","Fabric Glue Booth: ");
                        fprintf(fileOut,"%.1f", ((fabricGlueBooth)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(paintBooth != 0)
                    {
                        fprintf(fileOut,"%s","Paint Booth: ");
                        fprintf(fileOut,"%.1f", ((paintBooth)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if (finishingLine != 0)
                    {
                        fprintf(fileOut,"%s","Finishing Line: ");
                        fprintf(fileOut,"%.1f",(((double)finishingLine)/SECONDS_IN_MINUTE));
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
                    }

                    if(clipping != 0)
                    {
                        fprintf(fileOut,"%s","clipping: ");
                        fprintf(fileOut,"%.1f",(((double)clipping)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(fabricWrap != 0)
                    {
                        fprintf(fileOut,"%s","Fabric Wrap: ");
                        fprintf(fileOut,"%.1f", ((fabricWrap)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(microFilm != 0)
                    {
                        fprintf(fileOut,"%s","Micro Film: ");
                        fprintf(fileOut,"%.1f", ((microFilm)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(doorLine != 0)
                    {
                        fprintf(fileOut,"%s","Door Line: ");
                        fprintf(fileOut,"%.1f", ((doorLine)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(profileSander != 0)
                    {
                        fprintf(fileOut,"%s","Profile Sander: ");
                        fprintf(fileOut,"%.1f", ((profileSander)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(metalDoubleSaw != 0)
                    {
                        fprintf(fileOut,"%s","Metal Double Saw: ");
                        fprintf(fileOut,"%.1f", ((metalDoubleSaw)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(metalCnc != 0)
                    {
                        fprintf(fileOut,"%s","Metal CNC: ");
                        fprintf(fileOut,"%.1f", ((metalCnc)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(ceilingTrackPunch != 0)
                    {
                        fprintf(fileOut,"%s","Ceiling Track Punch: ");
                        fprintf(fileOut,"%.1f", ((ceilingTrackPunch)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(upperPunch != 0)
                    {
                        fprintf(fileOut,"%s","Upper Punch: ");
                        fprintf(fileOut,"%.1f", ((upperPunch)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }
                    if(lowerPunch != 0)
                    {
                        fprintf(fileOut,"%s","Lower Punch ");
                        fprintf(fileOut,"%.1f", ((lowerPunch)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(wingPunch != 0)
                    {
                        fprintf(fileOut,"%s","Wing Punch: ");
                        fprintf(fileOut,"%.1f", ((wingPunch)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(doubleHaunch != 0)
                    {
                        fprintf(fileOut,"%s","Double Haunch: ");
                        fprintf(fileOut,"%.1f", ((doubleHaunch)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(singleHaunch != 0)
                    {
                        fprintf(fileOut,"%s","Single Haunch: ");
                        fprintf(fileOut,"%.1f", ((singleHaunch)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(doorHaunch != 0)
                    {
                        fprintf(fileOut,"%s","Door Haunch: ");
                        fprintf(fileOut,"%.1f", ((doorHaunch)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(kitting != 0)
                    {
                        fprintf(fileOut,"%s","Kitting ");
                        fprintf(fileOut,"%.1f", ((kitting)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(assembly != 0)
                    {
                        fprintf(fileOut,"%s","Assembly: ");
                        fprintf(fileOut,"%.1f", ((assembly)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(powderCoat != 0)
                    {
                        fprintf(fileOut,"%s","Powder Coat: ");
                        fprintf(fileOut,"%.1f", ((powderCoat)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    if(toolCrib != 0)
                    {
                        fprintf(fileOut,"%s","Tool Crib: ");
                        fprintf(fileOut,"%.1f", ((toolCrib)/SECONDS_IN_MINUTE));
                        fprintf(fileOut,"%s\n"," min");
                    }

                    fprintf (fileOut,"%s", "Total Predicted time for ");
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
