#include "ops.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
void freePtrArray(char** array, int count)
{
    int i;

    for(i=0; i<count; ++i)
        free(++array[i]);
}

//////////////////////////////////////////////////////////////////////
void populateTable(int x; int y; Entry table[x][y], int x, int y, char fileName[])
{
    char currentLineStr[LENGTH_OF_CURRENT_LINE];
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
        fgets(currentLineStr, LENGTH_OF_CURRENT_LINE, fileIn);

        while (currentLineStr[0] == '#')
            fgets(currentLineStr, LENGTH_OF_CURRENT_LINE, fileIn);

        TokenizeLine(currentLineStr, table, yIndex, x, y);

        yIndex++;
        while(fgets(currentLineStr, LENGTH_OF_CURRENT_LINE, fileIn) != NULL)
        {
            TokenizeLine(currentLineStr, table, yIndex, x, y);

            yIndex++;
        }

        fclose(fileIn);
    }
}

//////////////////////////////////////////////////////////////////////
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
/*
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
                if (n > temp)
                    temp = n;

                goto Tokenize;
            }
        }
    }
    return temp;
}
*/

//////////////////////////////////////////////////////////////////////
double stdDev(int x; int y; int idInstances[y], int totalNumUnits, int rowQuantity[y], Entry eTable[x][y], int x, int y, int *numEntries)
{
    double total = 0;
    double tmp = 0;
    int index;
    double mean;
    double standardDev = 0;

    double xval;
    double yval;
    double zval;


    for(index = 0; index < *numEntries; index++)
    {
        tmp = ((eTable[11][(idInstances[index]-1)].dVal / 1000) *
               (eTable[12][(idInstances[index]-1)].dVal / 1000));

        tmp = tmp * eTable[21][(idInstances[index] - 1)].dVal;
        total = total + tmp;
    }
    mean = total/totalNumUnits;

    for(index = 0; index < *numEntries; index++)
    {
        xval = ((eTable[11][(idInstances[index]-1)].dVal / 1000) *
                (eTable[12][(idInstances[index]-1)].dVal / 1000));

        yval = xval * eTable[21][(idInstances[index] - 1)].dVal;
        zval = pow((yval - mean), 2);
        total = total + zval;
    }
    printf("%.2f\n",standardDev);
    standardDev = total/totalNumUnits;
    return standardDev;
}

//////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////
int checkColourDiff(int x; int y; int idInstances[y], Entry eTable[x][y], int x, int y, int *numEntries)
{
    int offSet = 1;
    int diffCount = 0;
    int index = 0;
    int flag = 1;
    int compareResult;

    while(flag)
    {
        if(index == *numEntries ||
                (strlen(eTable[5][(idInstances[index + offSet]-1)].str)) > strlen(eTable[5][(idInstances[index]-1)].str))
        {
            if(*numEntries == 0)
                diffCount = 0;

            flag = 0;
            break;
        }

        compareResult = strcmp(eTable[5][(idInstances[index]-1)].str, eTable[5][(idInstances[index + offSet]-1)].str);

        if(compareResult != 0)
        {
            if(offSet > 1)
            {
                index = (offSet + index);
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

    if((*numEntries != 0) && (index <= diffCount))
        diffCount++;

    if (*numEntries == 1)
        diffCount = 1;

    return diffCount;
}
//////////////////////////////////////////////////////////////////////
int countColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int index, int *numEntries)
{
    int count = 0;
    int tmp = 0;
    int counter = 0;

    for(counter = 0; counter < *numEntries; counter++)
    {
        if(strcmp(eTable[5][(idInstances[counter]-1)].str, codes[index]) == 0)
        {
            tmp = eTable[21][(idInstances[counter]-1)].dVal;
            count = count + tmp;
        }
    }
    return count;
}
//////////////////////////////////////////////////////////////////////
void getColourCodes(int x; int y; int numColours; int idInstances[y], Entry eTable[x][y], char *codes[numColours], int x, int y, int numColours, int *numEntries)
{
    int index = 0;
    int cIndex = 0;;
    int offset = 1;
    int tableLen;
    int tableOffsetLen;
    int cmpResult;
    int tmp;
    int flag = 1;

    char *table;
    char *tableOffset;

    while(flag)
    {
        printf("%i\n", *numEntries);
        if((index) > (*numEntries))
        {
            flag = 0;
            continue;
        }

        table = malloc(strlen(eTable[5][idInstances[index]-1].str) + 1);
        strcpy(table, eTable[5][idInstances[index]-1].str);

        tableOffset = malloc(strlen(eTable[5][idInstances[index + offset]-1].str) + 1);
        strcpy(tableOffset, eTable[5][idInstances[index + offset]-1].str);


        tableLen = strlen(table);
        tableOffsetLen = strlen(tableOffset);

        if(numColours == 1)
        {
            codes[cIndex] = malloc(strlen(table) + 1);
            strcpy(codes[cIndex], table);
            free(table);
            free(tableOffset);
            break;
        }
        if(tableLen != tableOffsetLen)
        {
            codes[cIndex] = malloc(strlen(table) + 1);
            strcpy(codes[cIndex], table);
            cIndex++;
            index++;
            free(table);
            free(tableOffset);
            continue;
        }

        cmpResult = strcmp(table,tableOffset);

        if(cmpResult == 0)
        {
            tmp = index + offset;
            index = tmp;
        }
        else if(cmpResult != 0)
        {

            codes[cIndex] = malloc(strlen(table) + 1);
            strcpy(codes[cIndex], table);
            cIndex++;
            index++;
            offset = 1;
        }

        free(table);
        free(tableOffset);
    }

}
//////////////////////////////////////////////////////////////////////
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

    *numEntries = 0;
//start at one to skip headers
    for(index = 1; index < y; index++)
    {
        strToCmp = malloc(strlen(eTable[0][index].str) + 1);
        strcpy(strToCmp, eTable[0][index].str);


        strToCmpLen = strlen(strToCmp);
        strToFindLen = strlen(stringToFind);


        if(strToCmpLen == strToFindLen)
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

        /*       if(strToCmpLen != strToFindLen)
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
               }*/
        free(strToCmp);
    }
    if(*numEntries == 0)
        return 0;
}
//////////////////////////////////////////////////////////////////////
int IsDouble(const char *str)
{
    char *endPtr = 0;
    strtod(str, &endPtr);

    if(*endPtr != '\0' || endPtr == str)
        return 0;

    return 1;
}
//////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////
int NumRows(char fileName[])
{
    int yIndex = 0;
    char currentLineStr[LENGTH_OF_CURRENT_LINE];

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
        fgets(currentLineStr, LENGTH_OF_CURRENT_LINE, fileIn);
        while (currentLineStr[0] == '#')
            fgets(currentLineStr, LENGTH_OF_CURRENT_LINE, fileIn);

        yIndex++;
        while(fgets(currentLineStr, LENGTH_OF_CURRENT_LINE, fileIn) != NULL)
            yIndex++;
    }
    fclose(fileIn);
    return yIndex;
}
//////////////////////////////////////////////////////////////////////
int NumColumns(char fileName[])
{
    char currentLineStr[LENGTH_OF_CURRENT_LINE];
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
        fgets(currentLineStr, LENGTH_OF_CURRENT_LINE, fileIn);
        while (currentLineStr[0] == '#')
            fgets(currentLineStr, LENGTH_OF_CURRENT_LINE, fileIn);

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
