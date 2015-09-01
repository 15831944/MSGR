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

        fgets(currentLineStr, 8192, fileIn);
        //TokenizeLine(currentLineStr, table, yIndex, x, y);
        //yIndex++;
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
        for(yIndex = 0; yIndex < (y); yIndex++)
        {
            for(xIndex = 0; xIndex < (x); xIndex++)
            {
                fprintf(fileOut,"%s", table[xIndex][yIndex].str);
                fprintf(fileOut,"%s"," ");
                fprintf(fileOut,"%.1f", table[xIndex][yIndex].dVal);
                fprintf(fileOut,"%s","|");
            }
                fprintf(fileOut,"\n");
        }
    }
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
        tmp = ((eTable[11][(idInstances[index] - 1)].dVal / 1000) *
               (eTable[12][(idInstances[index] - 1)].dVal / 1000));

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
        //printf("\n");
        //printf("%s\n", eTable[6][(idInstances[index] - 1)].str);
        //printf("%s\n", eTable[6][(idInstances[index + offSet] - 1)].str);
        //printf("\n");
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
        {
            flag = 0;
        }
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

        printf("\n");
        printf("%s\n", eTable[5][(idInstances[index] - 1)].str);
        printf("%s\n", eTable[5][(idInstances[index + offSet] - 1)].str);
             printf("\n");
        compareResult = strcmp(eTable[5][(idInstances[index] - 1)].str, eTable[5][(idInstances[index + offSet] - 1)].str);

        if(compareResult != 0)
        {
            codes[codeIndex] = malloc(strlen(eTable[5][(idInstances[index] - 1)].str) + 1);
            strcpy(codes[codeIndex], eTable[5][(idInstances[index] - 1)].str);

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
        {
            //codes[*numEntries] = NULL;
            flag = 0;
        }
    }
}

//search for the AlternateOptionID stored int the 1st column of the arrray
int SearchForId(int x; int y; char stringToFind[], Entry eTable[x][y], int idInstances[y], int x, int y, int *numEntries)
{
    int index;
    int idIndex = 0;
    int temp;
    char *stringToCompare;
    char *longerStr;
    int strToCmpLen = 0;
    int strToFindLen = 0;
    *numEntries = 0;

    for(index = 0; index < y; index++)
    {
        //stringToCompare = malloc(strlen(eTable[0][index].str) + 1);
        //strcpy(longerStr, eTable[0][index].str);

        stringToCompare = eTable[0][index].str;

        strToCmpLen = strlen(stringToCompare);
        strToFindLen = strlen(stringToFind);

        if((strToCmpLen < strToFindLen) || (strToCmpLen == strToFindLen))
        {
            longerStr = malloc(strlen(stringToFind) + 1);
            strcpy(longerStr, stringToFind);
        }
        else if(strToCmpLen > strToFindLen)
        {
           longerStr = malloc(strlen(stringToCompare) + 1);
           strcpy(longerStr, stringToCompare);
        }

        if(strncmp(stringToCompare, stringToFind, strlen(longerStr)) == 0)
        //if(strncmp(eTable[0][index].str, stringToFind, strlen(eTable[0][index].str)) == 0)
        //if(strncmp(eTable[0][index].str, stringToFind, strlen(stringToFind)) == 0)
        {
            temp = index + 1;
            idInstances[idIndex] = temp;
            idIndex++;
            (*numEntries)++;
        }
        free(stringToCompare);
        free(longerStr);
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
