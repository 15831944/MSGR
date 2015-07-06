#include <string.h>
#include "msgr.h"

#define BOUNDS(a) ((sizeof (a))/(sizeof ((a)[0])))

int main(int argc, char *argv[])
{
  
  int x;
  int y;
  int xIndex = 0;
  int yIndex = 0;
 
  char *tokPtr;
  char fileName[64] = {"dtest.txt"};
  char currentLineStr[8192];
  
  //printf("%s\n", "Enter FileName( max char 64):");
  //scanf("%s", fileName);
  //printf("%s\n", fileName);
  
//find required dim of array and assign
  x = NumRows(fileName);
  y = NumColumns(fileName);
 
  Entry eTable[x][y];
  
  printf("sizeof eTable = %u\n", (unsigned) sizeof eTable);
     
  printf("1st dimension = %u\n", (unsigned) BOUNDS(eTable));
   
  printf("2nd dimension = %u\n", (unsigned) BOUNDS(eTable[0]));
  
  
  FILE *fileIn;
  fileIn = fopen("dtest.txt", "r");
  
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
      
      //Start adding values to array. current line held by currentLineStr
      //is assigned first
      TokenizeLine(currentLineStr, eTable, yIndex, x, y);
      
      yIndex++;
      while(fgets(currentLineStr, 8192, fileIn) != NULL)
      {
            TokenizeLine(currentLineStr, eTable, yIndex, x, y);
            yIndex++;
      }     
  }
  system("PAUSE");	
  return 0;
}

void TokenizeLine(int x; int y; char currentLineStr[], Entry eTable[x][y], int yIndex, int x, int y)
{
  char *tokPtr;
  int xIndex = 0;

  tokPtr = strtok(currentLineStr, "|");
  eTable[xIndex][yIndex].str = tokPtr;

  while(tokPtr != NULL)
  {
        tokPtr = strtok(NULL, "|");
        eTable[xIndex][yIndex].str = tokPtr;
        printf("%s\n", eTable[xIndex][yIndex].str);
        printf("%i\n", xIndex);
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
      {
            fgets(currentLineStr, 8192, fileIn);
      }
      
      yIndex++;
      while(fgets(currentLineStr, 8192, fileIn) != NULL)
        {
        yIndex++;
        }
    }
    fclose(fileIn);
    printf("%i\n", yIndex);
    return yIndex++;
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
      {
            fgets(currentLineStr, 8192, fileIn);
      }
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
      printf("%i\n",xIndex);
      return xIndex;
}

