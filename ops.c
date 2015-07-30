#include "ops.h"

int numUnits(int x; int y; int idInstances[y], int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries)
{
    int index;
    int total = 0;

    for(index = 0; index < *numEntries; index++)
    {
        rowQuantity[index] = eTable[21][(idInstances[index] - 1)].dVal;
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
    //printf("%s\n", eTable[column][(idInstances[index] - 1)].str);
    for(index = 0; index < *numEntries; index++)
    {
     //printf("%s\n", eTable[column][(idInstances[index] - 1)].str);
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
        compareResult = strcmp(eTable[5][(idInstances[index] - 1)].str, eTable[5][(idInstances[index + offSet] - 1)].str);

        if(compareResult != 0)
        {
            if(offSet > 1)
                index = (offSet + index);
            else
                index++;

            offSet = 1;
            diffCount++;
        }
        else if(compareResult == 0)
        {
            offSet++;
        }

        if(index == *numEntries)
            flag = 0;
    }
    return diffCount;
}

void getColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int *numEntries)
{
    int offSet = 1;
    int diffCount = 0;
    int index = 0;
    int flag = 1;
    int compareResult;

    while(flag)
    {
        compareResult = strcmp(eTable[5][(idInstances[index] - 1)].str, eTable[5][(idInstances[index + offSet] - 1)].str);

        if(compareResult != 0)
        {
            codes[codeIndex] = (eTable[5][(idInstances[index] - 1)].str);

            if(offSet > 1)
                index = (offSet + index);
            else
                index++;

            offSet = 1;
            diffCount++;
            codeIndex++;
        }
        else if(compareResult == 0)
        {
            offSet++;
        }

        if(index == *numEntries)
            flag = 0;
    }
}

//search for the AlternateOptionID stored int the 1st column of the arrray
void SearchForId(int x; int y; char stringToFind[], Entry eTable[x][y], int idInstances[y], int x, int y, int *numEntries)
{
    int index;
    int idIndex = 0;
    int temp;

    *numEntries = 0;

    for(index = 0; index < y; index++)
    {
        if(strncmp(eTable[0][index].str, stringToFind, strlen(stringToFind)) == 0)
        {
            temp = index + 1;
            //printf("%i\n", temp);
            idInstances[idIndex] = temp;
            // printf("%i\n", idInstances[0]);
            idIndex++;
            (*numEntries)++;
        }
    }
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

void TokenizeLine(int x; int y; char currentLineStr[], Entry eTable[x][y], int yIndex, int x, int y)
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
            //eTable[xIndex][yIndex].str = NULL;
            eTable[xIndex][yIndex].dVal = atof(tokPtr);
            //           printf("%i\n", eTable[xIndex][yIndex].dVal);
        }
        else
        {
            eTable[xIndex][yIndex].str = malloc(strlen(tokPtr) + 1);
            strcpy(eTable[xIndex][yIndex].str, tokPtr);
            eTable[xIndex][yIndex].dVal = 0;
            //printf("%s\n", eTable[xIndex][yIndex].str);
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
    //printf("%i\n",xIndex);
    return xIndex;
}
