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
      Huff_postOrderPrint(root);
    }
  else
    {
      //do bit
    }

  return EXIT_SUCCESS;

}

