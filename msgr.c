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
    int yCount;
    int xCount;
    
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
      
      printf("%s\n", currentLineStr);       
      TokenizeLine(currentLineStr, eTable, yIndex, x, y);
      printf("%s\n", eTable[0][yIndex].str);
      yIndex++;
            
      while(fgets(currentLineStr, 8192, fileIn) != NULL)
      {
            printf("%i\n", yIndex);
            printf("%s\n", currentLineStr);
            TokenizeLine(currentLineStr, eTable, yIndex, x, y);
           // printf("%s\n", eTable[0][1].str);
           // printf("%s\n", eTable[0][2].str);
            yIndex++;
      }
      fclose(fileIn);
      /*
      for(yCount = 1; yCount < y; yCount++)
      {
              for(xCount = 1; xCount < x; xCount++)
                    printf("%s\n", eTable[xCount][yCount].str);
      }
      */
      
    }
    
  
    //SearchForId(stringToFind, eTable, idInstances, x, y);
    //printf("%i\n", idInstances[0]);
   
    printf("%s\n", eTable[0][0].str);
    printf("%s\n", eTable[0][1].str);
    printf("%s\n", eTable[1][0].str);
    printf("%s\n", eTable[0][1].str);
    
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
         //idInstances[idIndex] = index;
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
  //printf("%s\n", currentLineStr);

  while(tokPtr != NULL)
  {
        if(IsDouble(tokPtr))
        {
             //printf("%s\n", tokPtr);
             eTable[xIndex][yIndex].str = NULL;
             eTable[xIndex][yIndex].dVal = atof(tokPtr);
             //printf("%f\n", eTable[xIndex][yIndex].dVal);  
        }
        else
        {       
              eTable[xIndex][yIndex].str = tokPtr;
              //printf("%s\n", eTable[xIndex][yIndex].str);
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
    //printf("%i\n", yIndex);
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
