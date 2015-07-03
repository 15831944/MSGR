#include <string.h>
#include "msgr.h"

#define BOUNDS(a) ((sizeof (a))/(sizeof ((a)[0])))

int main(int argc, char *argv[])
{
    char * tokPtr;
  int x;
  int y;
  char hWorld[] = {"Hello World"};
  char fileName[64];
  char ch;
  char strTemp[8192];
  char strTemp2[8192];
  int c = '\n';;
   
  int pLines = 0;
  int charIndex = 0;
  int lines = 0;
  int la = 0;
  int prev;
  int xindex = 0;
  
    
  //printf("%s\n", "Enter FileName( max char 64):");
 // scanf("%s", fileName);
//  printf("%s\n", fileName);
  
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
      /*
      c = fgetc(fileIn);
      fgets(strTemp, 2048, fileIn);
      c = fgetc(fileIn);
      fgets(strTemp, 2048, fileIn); 
      printf("%s\n", strTemp);
      fclose(fileIn);
      */
      
      fgets(strTemp, 8192, fileIn); 
      while (strTemp[0] == '#')
      {
            fgets(strTemp, 8192, fileIn);
            
            }
        strcpy(strTemp2, strTemp);
            printf("%c\n", strTemp[0]);
            printf("%s\n", strTemp);
            tokPtr = strtok(strTemp, "|");
            xindex++;
            printf("%s\n", tokPtr);
      
      while (tokPtr != NULL)
      {
            //printf("%s\n", tokPtr);
            tokPtr = strtok(NULL, "|");
            
            //printf("%s\n", eTable[xindex][0].str);
            xindex++;
            }
            x = xindex;
            y = xindex*2;
            Entry eTable[x][y];
            printf("%i\n", xindex);
            
            tokPtr = strtok(strTemp2, "|");
      xindex = 0;      
      while(tokPtr != NULL)
      {
      tokPtr = strtok(NULL, "|");
      eTable[xindex][0].str = tokPtr;
      printf("%s\n", eTable[xindex][0].str = tokPtr);
      printf("%i\n", xindex);
      xindex++;
      }
           /*
           prev = c;
           c = fgetc(fileIn);
           if(c == '#' && prev == '\n')
           {
                while(c != '\n')
                {
                 c = fgetc(fileIn);
                 printf("%c", c);
                }
           pLines++;
            } 
            else if(prev == '\n')
            {
            lines++;
            }
            else if(prev == '\n' && c != '#')
            {
                 
                 while(prev != '|' || c != '\n')
                 {
                         prev = c;
                         c = fgetc(fileIn);
                         
                         strTemp[charIndex] = c;
                         charIndex++;
                 }
                 
                 strTemp[1] = c;
                 printf("%s\n", strTemp);
                 charIndex = 0;
            */
      
  }

  // printf("%c", prev);
  // printf("%c", c);
 //  printf("%i", pLines);
 //  printf("%i", lines);
 //  printf("%c", '\n');
 //  printf("%i", la);
 //  printf("%c", '\n');
 //  fclose(fileIn);
  /*  
    size_t destination_size = sizeof (eTable[0][0].str);

    strncpy(eTable[1][1].str, hWorld, destination_size);
    eTable[1][0].str[destination_size - 1] = '\0';
    eTable[0][1].iVal = 1;
    eTable[1][2].iVal = 2;
    
    printf("%d\n", destination_size);
    printf("%d\n", eTable[1][0].iVal);
    printf("%s\n", *eTable[0][0].str);


    
     printf("sizeof eTable = %u\n", (unsigned) sizeof eTable);
     
     printf("1st dimension = %u\n", (unsigned) BOUNDS(eTable));
   
     printf("2nd dimension = %u\n", (unsigned) BOUNDS(eTable[0]));
   */  
  system("PAUSE");	
  return 0;
}

