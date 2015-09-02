#include "ops.h"

void freePtrArray(char** array, int count)
{
    int i;

    for(i=0; i<count; ++i)
        free(++array[i]);
}

void populateTable(int x; int y; Entry table[x][y], int x, int y, char fileName[], char tableName[])
{
    char currentLineStr[8192];
    int yIndex = 0;
    int xIndex = 0;

    FILE *fileIn;
    FILE *fileOut;

    fileIn = fopen(fileName, "r");

    if(fileIn == 0)
    {
        perror("Cannot open input file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        fgets(currentLineStr, 8192, fileIn);

        while (currentLineStr[0] == '#')
            fgets(currentLineStr, 8192, fileIn);

        TokenizeLine(currentLineStr, table, yIndex, x, y);
        //fgets(currentLineStr, 8192, fileIn);

        yIndex++;
        while(fgets(currentLineStr, 8192, fileIn) != NULL)
        {
            TokenizeLine(currentLineStr, table, yIndex, x, y);

            yIndex++;
        }

        fclose(fileIn);
    }

    fileOut = fopen(tableName, "w");
    if(fileOut == 0)
    {
        perror("Could open output file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        /*
                for(yIndex = 0; yIndex < (y); yIndex++)
                {
                    for(xIndex = 0; xIndex < (x+1); xIndex++)
                    {
                        fprintf(fileOut,"%s", table[xIndex][yIndex].str);
                        fprintf(fileOut,"%s"," ");
                        fprintf(fileOut,"%.1f", table[xIndex][yIndex].dVal);
                        fprintf(fileOut,"%s","|");
                    }
                    fprintf(fileOut,"\n");

                }
        */
        fclose(fileOut);

    }
}


int numUnits(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries)
{
    int index;
    int total = 0;

    for(index = 0; index < *numEntries; index++)
    {
        rowQuantity[index] = eTable[21][(idInstances[index]-1)].dVal;
    }

    for(index = 0; index < *numEntries; index++)
    {
        total = total + rowQuantity[index];
    }
    return total;
}

int extractDoubles(int x; int y; int idInstances[y], double clipLines[x][y], Entry eTable[x][y], int x, int y, int *numEntries, int column)
{
    char *tokPtr;
    char *current;
    int index = 0;
    int n;
    int temp;

    for(index = 0; index < *numEntries; index++)
    {
        current = eTable[column][(idInstances[index] - 1)].str;

        tokPtr = mystrsep(&current, " m:");
        n = 0;
Tokenize:
        while(tokPtr != NULL)
        {
            printf("%s\n", tokPtr);
            if(IsDouble(tokPtr) && tokPtr != 0)
            {
                clipLines[n][index] = atof(tokPtr);
            }
            else
            {
                tokPtr = mystrsep(&current, " m:");
                goto Tokenize;
            }
            tokPtr = mystrsep(&current, " m:");

            if(tokPtr != NULL)
            {
                n++;
                if( n > temp)
                    temp = n;

                goto Tokenize;
            }
        }
    }
    return temp;
}

double avgSize(int x; int y; int idInstances[y], int totalNumUnits, int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries)
{
    double total = 0;
    double tmp = 0;
    int index;

    for(index = 0; index < *numEntries; index++)
    {
        tmp = ((eTable[11][(idInstances[index]-1)].dVal / 1000) *
               (eTable[12][(idInstances[index]-1)].dVal / 1000));

        tmp = tmp * eTable[21][(idInstances[index] - 1)].dVal;
        total = total + tmp;
    }
    total = total/totalNumUnits;
    return total;
}
int numCuts(int x; int y; int idInstances[y], Entry eTable[x][y], int x, int y, int *numEntries)
{
    int index;
    int numCuts = 0;

    for(index = 0; index < *numEntries; index++)
    {
        if(eTable[10][(idInstances[index] - 1)].dVal > eTable[12][(idInstances[index] - 1)].dVal)
            numCuts++;
        else if(eTable[11][(idInstances[index] - 1)].dVal > eTable[13][(idInstances[index] - 1)].dVal)
            numCuts++;
    }
    return numCuts;
}

int checkColourDiff(int x; int y; int idInstances[y], Entry eTable[x][y], int x, int y, int *numEntries)
{
    int offSet = 1;
    int diffCount = 0;
    int index = 0;
    int flag = 1;
    int compareResult;

    while(flag)
    {


        //if(index == *numEntries)
        if(index == *numEntries ||
                (strlen(eTable[5][(idInstances[index + offSet]-1)].str)) > strlen(eTable[5][(idInstances[index]-1)].str))
        {
            if(*numEntries == 0)
                diffCount = 0;

            flag = 0;
            break;
        }
        // printf("\n");
        // printf("%s\n", eTable[5][(idInstances[index] - 1)].str);
        // printf("%s\n", eTable[5][(idInstances[index + offSet] - 1)].str);
        //printf("\n");

        compareResult = strcmp(eTable[5][(idInstances[index]-1)].str, eTable[5][(idInstances[index + offSet]-1)].str);

        if(compareResult != 0)
        {
            if(offSet > 1)
            {
                index = (offSet + index);
                //index--;
            }
            else
            {
                index++;
            }

            offSet = 1;
            diffCount++;
        }
        else if(compareResult == 0)
        {
            offSet++;
        }

        if(index == *numEntries)
        {
            flag = 0;
            break;
        }
    }
    if(*numEntries != 0)
        diffCount++;
    return diffCount;
}

int countColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int index, int *numEntries)
{
    int count = 0;
    int tmp = 0;

    for(x = 0; x < *numEntries; x++)
    {
        if(strcmp(eTable[5][(idInstances[x]-1)].str, codes[index]) == 0)
        {
            tmp = eTable[21][(idInstances[x]-1)].dVal;
            count = count + tmp;
        }
    }
    return count;
}

void getColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int *numEntries)
{
    int cmpResult = 0;;
    int index = 0;
    int codeIndex = 0;
    int flag = 1;
    int offset = 1;
    int eTableLen;
    int eTableOffsetLen;

    while(flag && ((index + offset) < *numEntries))
    {
        printf("%i\n", *numEntries);
        if(*numEntries == 0)
        {
            flag = 0;
            continue;
        }

        if(strlen(eTable[5][(idInstances[index]-1)].str) != strlen(eTable[5][(idInstances[index + offset]-1)].str))
            cmpResult = 1;
        else
            cmpResult = strcmp(eTable[5][(idInstances[index]-1)].str, eTable[5][(idInstances[index + offset]-1)].str);

        if(cmpResult != 0)
        {
            codes[codeIndex] = malloc(strlen(eTable[5][(idInstances[index]-1)].str) + 1);
            strcpy(codes[codeIndex], eTable[5][(idInstances[index]-1)].str);
            printf("%s\n", codes[codeIndex]);
            codeIndex++;
            index++;
            continue;
        }

        else if(cmpResult == 0)
        {
            codes[codeIndex] = malloc(strlen(eTable[5][(idInstances[index]-1)].str) + 1);
            strcpy(codes[codeIndex], eTable[5][(idInstances[index]-1)].str);
            printf("%s\n", codes[codeIndex]);

            codeIndex++;
            offset++;
            if((index + offset) > *numEntries)
            {
            flag = 0;
            continue;
            }

            eTableLen = strlen(eTable[5][(idInstances[index]-1)].str);
            eTableOffsetLen = strlen(eTable[5][(idInstances[index + offset]-1)].str);

            if(eTableLen != eTableOffsetLen)
                cmpResult = 1;
            else
                cmpResult = strcmp(eTable[5][(idInstances[index]-1)].str, eTable[5][(idInstances[index + offset]-1)].str);

            while((cmpResult == 0) && ((index + offset) < *numEntries))
            {
                offset++;
                if((index + offset) > *numEntries)
                {
                    flag = 0;
                    continue;
                }

                eTableLen = strlen(eTable[5][(idInstances[index]-1)].str);
                printf("%s\n", eTable[5][(idInstances[index + offset]-1)].str);
                printf("%i\n",offset);
                eTableOffsetLen = strlen(eTable[5][(idInstances[index + offset]-1)].str);

                if(eTableLen != eTableOffsetLen)
                    cmpResult = 1;
                else
                    cmpResult = strcmp(eTable[5][(idInstances[index]-1)].str, eTable[5][(idInstances[index + offset]-1)].str);
            }
            int tmp;
            tmp = index + offset;
            index = tmp;
            offset = 1;
            continue;
        }
    }
    /*        while(flag)
            {

                if(strlen(eTable[5][(idInstances[index]-1)].str) != strlen(eTable[5][(idInstances[index + offset]-1)].str))
                {
                    cmpResult = 1;
                }
                else
                {
                    cmpResult = strcmp(eTable[5][(idInstances[index]-1)].str, eTable[5][(idInstances[index + offset]-1)].str);
                }

                cmpResult = strcmp(eTable[5][(idInstances[index]-1)].str, eTable[5][(idInstances[index + offset]-1)].str);
                printf("%s\n", eTable[5][(idInstances[index]-1)].str);
                printf("%s\n", eTable[5][(idInstances[index + offset]-1)].str);
                printf("%i\n", cmpResult);
                printf("\n");

          //  Redo:
                if(cmpResult != 0)
                {
                    if(offset > 1)
                    {
                        int tmp;
                        tmp = index + offset;
                        index = tmp;
                    }
                   // printf("%s\n", eTable[5][(idInstances[index]-1)].str);
                    codes[codeIndex] = malloc(strlen(eTable[5][(idInstances[index]-1)].str) + 1);
                strcpy(codes[codeIndex], eTable[5][(idInstances[index]-1)].str);
                    //codes[codeIndex] = eTable[5][(idInstances[index]-1)].str;
                    offset = 1;
                    index++;
                    codeIndex++;
                }

                if(cmpResult == 0)
                {
                    if(offset > 1)
                    {
                        int tmp;
                        tmp = index + offset;
                        index = tmp;
                    }
                codes[codeIndex] = malloc(strlen(eTable[5][(idInstances[index]-1)].str) + 1);
                strcpy(codes[codeIndex], eTable[5][(idInstances[index]-1)].str);
                    offset++;
                   // goto Redo;
                }
                if(index == *numEntries ||
                   ((strlen(eTable[5][idInstances[index + offset]-1].str)) > (strlen(eTable[5][idInstances[index]-1].str))))
                {
                    flag = 0;
                }

            }


    */












    /*
    int offSet = 1;
    int diffCount = 0;
    int index = 0;
    int codeIndex = 0;
    int flag = 1;
    int compareResult;
    //@TODO problem with repitition checking dc11 appears twice.
    while(flag)
    {
        if(index == *numEntries ||
           ((strlen(eTable[5][idInstances[index + offSet]-1].str)) > (strlen(eTable[5][idInstances[index]-1].str))))
        {
            flag = 0;
            break;
        }
        compareResult = strcmp(eTable[5][(idInstances[index]-1)].str, eTable[5][(idInstances[index + offSet]-1)].str);
        //compareResult = strcmp(eTable[5][(idInstances[index])].str, eTable[5][(idInstances[index + offSet])].str);

        if(compareResult != 0)
        {
            codes[codeIndex] = malloc(strlen(eTable[5][(idInstances[index]-1)].str) + 1);
            strcpy(codes[codeIndex], eTable[5][(idInstances[index]-1)].str);

            if(offSet > 1)
            {
                index = (offSet + index);
                //////////////////////////
                //index--;
                //////////////////////////
            }
            else
            {
                index++;
            }

            offSet = 1;
            diffCount++;
            codeIndex++;
        }
        else if(compareResult == 0)
        {
            offSet++;
        }
    }
    */
}

//search for the AlternateOptionID stored int the 1st column of the arrray
int SearchForId(int x; int y; char stringToFind[], Entry eTable[x][y], int idInstances[y], int x, int y, int *numEntries)
{
    int index;
    int idIndex = 0;
    int temp;
    int strToCmpLen = 0;
    int strToFindLen = 0;
    int cmpResult;

    char *strToCmp;
    // char *longerStr;

    *numEntries = 0;
//start at one to skip headers
    for(index = 1; index < y; index++)
    {
        //strToCmp = malloc(strlen(eTable[0][index].str) + 1);
        //strcpy(longerStr, eTable[0][index].str);

        strToCmp = eTable[0][index].str;

        strToCmpLen = strlen(strToCmp);
        strToFindLen = strlen(stringToFind);

        if(strToCmpLen != strToFindLen)
        {
            continue;
        }
        else
        {
            cmpResult = strcmp(strToCmp, stringToFind);

            if(cmpResult == 0)
            {
                temp = index + 1;
                idInstances[idIndex] = temp;
                idIndex++;
                (*numEntries)++;

            }
        }
        free(strToCmp);
    }
    if(*numEntries == 0)
        return 0;
}

int IsDouble(const char *str)
{
    char *endPtr = 0;
    strtod(str, &endPtr);

    if(*endPtr != '\0' || endPtr == str)
        return 0;

    return 1;
}

char* mystrsep(char** stringp, const char* delim)
{
    char *start = *stringp;
    char *p;

    p = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (p == NULL)
    {
        *stringp = NULL;
    }
    else
    {
        *p = '\0';
        *stringp = p + 1;
    }

    return start;
}

void TokenizeLine(int x; int y; char currentLineStr[], Entry table[x][y], int yIndex, int x, int y)
{
    char *tokPtr;
    char *current;
    int xIndex = 0;

    current = currentLineStr;
    tokPtr = mystrsep(&current, "|");

    while(tokPtr != NULL)
    {
        if(IsDouble(tokPtr))
        {
            table[xIndex][yIndex].str = NULL;
            table[xIndex][yIndex].dVal = atof(tokPtr);
        }
        else
        {
            table[xIndex][yIndex].str = malloc(strlen(tokPtr) + 1);
            strcpy(table[xIndex][yIndex].str, tokPtr);
            table[xIndex][yIndex].dVal = 0;
        }

        tokPtr = mystrsep(&current, "|");
        xIndex++;
    }
}

int NumRows(char fileName[])
{
    int yIndex = 0;
    char currentLineStr[8192];

    FILE *fileIn;
    fileIn = fopen(fileName, "r");
    if (fileIn == 0)
    {
        perror("Cannot open input file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        fgets(currentLineStr, 8192, fileIn);
        while (currentLineStr[0] == '#')
            fgets(currentLineStr, 8192, fileIn);

        yIndex++;
        while(fgets(currentLineStr, 8192, fileIn) != NULL)
            yIndex++;
    }
    fclose(fileIn);
    return yIndex;
}

int NumColumns(char fileName[])
{
    char currentLineStr[8192];
    int xIndex = 0;
    char *tokPtr;

    FILE *fileIn;
    fileIn = fopen(fileName, "r");
    if(fileIn == 0)
    {
        perror("Cannot open input file\n");
        system("PAUSE");
        exit(-1);
    }
    else
    {
        //Get first line of file then iterate through lines until
        //beginning comments are passed over
        fgets(currentLineStr, 8192, fileIn);
        while (currentLineStr[0] == '#')
            fgets(currentLineStr, 8192, fileIn);

        tokPtr = strtok(currentLineStr, "|");
        xIndex++;
        //count remaining rows
        while (tokPtr != NULL)
        {
            tokPtr = strtok(NULL, "|");
            xIndex++;
        }
    }
    fclose(fileIn);
    return xIndex;
}
