#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

int main (int argc, char ** argv)
{
  if (argc != 3)
    {
      printf("\n\n\nERROR \n");
      printf("FORMAT: ./pa09 input output\n");
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;

}

