#include "ops.h"

void populateTable(int x; int y; Entry table[x][y], int x, int y, char fileName[])
{
    char currentLineStr[8192];
    int yIndex = 0;

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
        fgets(currentLineStr, 8192, fileIn);

        while (currentLineStr[0] == '#')
            fgets(currentLineStr, 8192, fileIn);

        TokenizeLine(currentLineStr, table, yIndex, x, y);
        yIndex++;
        while(fgets(currentLineStr, 8192, fileIn) != NULL)
        {
            TokenizeLine(currentLineStr, table, yIndex, x, y);

            yIndex++;
            //printf("%i\n",yIndex);
        }

        fclose(fileIn);
    }

    printf("%s\n", table[0][0].str);
    printf("%f\n", table[1][0].dVal);

    //printf("%s\n", table[2][0].str);
    printf("%f\n", table[2][0].dVal);

    //printf("%s\n", table[3][0].str);
    printf("%f\n", table[3][0].dVal);

}

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

double avgSize(int x; int y; int idInstances[y], int totalNumUnits, int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries)
{
    double total = 0;
    double tmp = 0;
    int index;
    //int totalNumUnits;

    //totalNumUnits = numUnits(idInstances, rowQuantity, eTable, x, y, &numEntries);

    for(index = 0; index < *numEntries; index++)
    {
        tmp = ((eTable[11][(idInstances[index] - 1)].dVal / 1000) *
               (eTable[12][(idInstances[index] - 1)].dVal / 1000));
        printf("%f\n", tmp);
        tmp = tmp * eTable[21][(idInstances[index] - 1)].dVal;

        printf("%f\n", eTable[11][(idInstances[index] - 1)].dVal);
        printf("%f\n", eTable[12][(idInstances[index] - 1)].dVal);
        printf("%f\n", tmp);
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

int countColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int index, int *numEntries)
{
    int count = 0;
    int tmp = 0;

    for(x = 0; x < *numEntries; x++)
    {
        if(strcmp(eTable[5][(idInstances[x] - 1)].str, codes[index]) == 0)
            {
                tmp = eTable[21][(idInstances[x] - 1)].dVal;
                count = count + tmp;
            }
    }
    return count;
}

void getColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int *numEntries)
{
    int offSet = 1;
    int diffCount = 0;
    int index = 0;
    int codeIndex = 0;
    int flag = 1;
    int compareResult;
//@TODO problem with repitition checking dc11 appears twice.
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
            //printf("%f\n",tokPtr);
            table[xIndex][yIndex].str = NULL;
            table[xIndex][yIndex].dVal = atof(tokPtr);
           // printf("%i\n", xIndex);
           // printf("%i\n", yIndex);
            //printf("%f\n", table[xIndex][yIndex].dVal);

        }
        else
        {
            table[xIndex][yIndex].str = malloc(strlen(tokPtr) + 1);
            strcpy(table[xIndex][yIndex].str, tokPtr);
            table[xIndex][yIndex].dVal = 0;
            //printf("%i\n", xIndex);
            //printf("%i\n", yIndex);
            //printf("%s\n", table[xIndex][yIndex].str);
        }

        tokPtr = mystrsep(&current, "|");
        //printf("%i\n", xIndex);
        //printf("%i\n", yIndex);
        //printf("%s\n", table[0][0].str);
        //printf("%f\n", table[0][1].dVal);
        //printf("%s\n", table[xIndex][yIndex].str);
        //printf("%f\n", table[xIndex][yIndex].dVal);
        //printf("\n");
        xIndex++;
    }
    //printf("%s\n", table[0][0].str);
    //printf("%f\n", table[1][0].dVal);
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
