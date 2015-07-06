#include <stdio.h>
#include <stdlib.h>

#include "msgr.h"

#define BOUNDS(a) ((sizeof (a))/(sizeof ((a)[0])))

int main(int argc, char *argv[])
{
    char currentLineStr[8192];
    char fileName[64] = {"dtest.txt"};

    int x = 150;
    int y = 300;
    int yIndex = 0;
    
    x = NumColumns(fileName);
    y = NumRows(fileName);
    
    Entry eTable[x][y];
    
    printf("sizeof eTable = %u\n", (unsigned) sizeof eTable);
     
    printf("1st dimension = %u\n", (unsigned) BOUNDS(eTable));
   
    printf("2nd dimension = %u\n", (unsigned) BOUNDS(eTable[0]));
    
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
      
      for(int yCount = 0; yCount < y; yCount++)
      {
              for(int xCount = 0; xCount < x; xCount++)
              {
                      printf("%s\n", eTable.str  
    }
    system("PAUSE");	
    return 0;
}

void TokenizeLine(int x; int y; char currentLineStr[], Entry eTable[x][y], int yIndex, int x, int y)
{
  char *tokPtr;
  int xIndex = 0;

  tokPtr = strtok(currentLineStr, "|");

  while(tokPtr != NULL)
  {
        eTable[xIndex][yIndex].str = tokPtr;
        printf("%s\n", eTable[xIndex][yIndex].str);
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
