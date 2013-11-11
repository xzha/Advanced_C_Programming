#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa09.h"

int main (int argc, char ** argv)
{
  if (argc != 3)
    {
      printf("ERROR\n");
      printf("FORMAT: ./pa09 <input> <output>\n");
      return EXIT_FAILURE;
    }
  
  //OPEN FILE
  FILE * fh;
  fh = fopen(argv[1], "r");
  if (fh == NULL)
    {
      printf("ERROR\n");
      printf("INVALID INPUT FILE\n");
      return EXIT_FAILURE;
    }

  //CHECK METHOD
  const char * filename = argv[1];
  int size = strlen(filename);
  int method = 0; // DO BYTE
  if (filename[size - 1] == 't')
    {
      method = 1;
    }
  
  //CREATE TREE
  HuffNode * root = NULL;
  if (!method)
    {
      //do byte
      root = readbyByte(fh);
    }
  else
    {
      //do bit
      root = readbyBit(fh);
    }

  //PRINT TREE
  FILE * fptr;
  fptr = fopen(argv[2], "w");
  if (fptr == NULL)
    {
      HuffNode_destroy(root);
      fclose(fh);
      printf("ERROR\n");
      printf("INVALID OUTPUT FILE\n");
      return EXIT_FAILURE;
    }
  printtoFile(fptr, root);

  //FREE
  HuffNode_destroy(root);
  fclose(fh);
  fclose(fptr);

  return EXIT_SUCCESS;

}

