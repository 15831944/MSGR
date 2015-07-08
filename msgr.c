#include <stdio.h>
#include <stdlib.h>

#include "msgr.h"

#define BOUNDS(a) ((sizeof (a))/(sizeof ((a)[0])))

int main(int argc, char *argv[])
{
    char currentLineStr[8192];
    char stringToFind[256] = {"DWL_FaceMountTile"};
    char fileName[64] = {"rtest.txt"};

    int x = 150;
    int y = 300;
    int yIndex = 0;
    
    int row;
    x = NumColumns(fileName);
    y = NumRows(fileName);
    
    Entry eTable[x][y];
    int idInstances[y];
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
    
    SearchForId(stringToFind, eTable, idInstances, x, y);
    printf("%i\n", idInstances[0]);
    
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
         printf("%s\n", index);
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

void TokenizeLine(int x; int y; char currentLineStr[], Entry eTable[x][y], int yIndex, int x, int y)
{
  char *tokPtr;
  int xIndex = 0;

  tokPtr = strtok(currentLineStr, "|");

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
        tokPtr = strtok(NULL, "|");      
        xIndex++;
  } 
}

int NumRows(char fileName[])
{
    int yIndex = 0;
    char *tokPtr;
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
