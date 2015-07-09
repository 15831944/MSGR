#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msgr.h"

#define BOUNDS(a) ((sizeof (a))/(sizeof ((a)[0])))

int main(int argc, char *argv[])
{
    char currentLineStr[8192];
    //char stringToFind[256] = {"DWL_FaceMountTile"};
    char fileName[64] = {"rtest.txt"};

    int x = 150;
    int y = 300;
    int yIndex = 0;
    int i;
    int n;
    
    //int row;
    x = NumColumns(fileName);
    y = NumRows(fileName);
    
    Entry eTable[x][y];
    //int idInstances[y];
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
      
      TokenizeLine(currentLineStr, eTable, yIndex, x, y);
      yIndex++;
            
      while(fgets(currentLineStr, 8192, fileIn) != NULL)
      {
            TokenizeLine(currentLineStr, eTable, yIndex, x, y);
            yIndex++;
      }
      fclose(fileIn);
    }
     for(i = 0; i < y; i++)
     {
           for(n = 0; n < x; n++)
           {
                 if(eTable[n][i].str == NULL)
                 {
                       printf("%f", eTable[n][i].dVal);
                       printf("%s", "|");
                       if(n == 3)
                       printf("%s\n", " ");
                 }
                 else
                 {
                     printf("%s", eTable[n][i].str);
                     printf("%s", "|");
                     if(n == 3)
                     printf("%s\n", " ");
                 }
                 
           }
     }
            
    printf("%s", eTable[0][0].str);
    printf("%s", " | ");
    printf("%s", eTable[1][0].str);
    printf("%s", " | ");
    printf("%s\n", eTable[2][0].str);
    
    
    printf("%s", eTable[0][1].str);
    printf("%s", " | ");
    printf("%i", eTable[1][1].dVal);
    printf("%s", " | ");
    printf("%s\n", eTable[2][1].str);
    
    
    printf("%s", eTable[0][2].str);
    printf("%s", " | ");
    printf("%s", eTable[1][2].str);
    printf("%s", " | ");
    printf("%s\n", eTable[2][2].str);
   
    //SearchForId(stringToFind, eTable, idInstances, x, y);
    
    printf("sizeof eTable = %u\n", (unsigned) sizeof eTable);
     
    printf("1st dimension = %u\n", (unsigned) BOUNDS(eTable));
   
    printf("2nd dimension = %u\n", (unsigned) BOUNDS(eTable[0]));
    
    system("PAUSE");	
    return 0;
}

//search for the AlternateOptionID stored int the 1st column of the arrray

void SearchForId(int x; int y; char stringToFind[], Entry eTable[x][y], int idInstances[y], int x, int y)
{
    int index;
    int idIndex;
    for(index = 0; index < y; index++)
    {
      if(strcmp(eTable[0][index].str, stringToFind) == 0)
      {
         //printf("%s\n", index);
         idInstances[idIndex] = index;
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
  char* start = *stringp;
  char* p;

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
                eTable[xIndex][yIndex].str = NULL;
                eTable[xIndex][yIndex].dVal = atof(tokPtr);
            }
            else
            {       
                eTable[xIndex][yIndex].str = malloc(strlen(tokPtr) + 1);
                strcpy(eTable[xIndex][yIndex].str, tokPtr);
            }
            
        tokPtr = mystrsep(&current, "|");
        
        if(tokPtr == "|")
        {
        printf("%s\n", "tok is null");
        printf("%i\n", xIndex);
            }
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
