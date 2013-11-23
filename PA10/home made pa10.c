
#include "pa10.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#define MAXIMUM_LENGTH 11
#define TRUE 1
#define FALSE 0
char * * readString (char * , int * numString);
void printString(char ** arrString, int numString);
void freeString(char * * arrString, int numString);


void printUsage(char * argv0)
{
    printf("\n"
	   "   Usage: %s <cmd> <arg>\n"
	   "\n"
	   "      <cmd> can be one of 'sort', 'sortable',\n"
	   "      or 'shapes'.\n"
	   "\n"
	   "      If <cmd> is 'sort' or 'sortable', then\n"
	   "      <arg> must be a unique sequence of\n"
	   "      digits from [0-9]. 'sort' will sort them,\n"
	   "      and 'sortable' will print 'Y' or 'N'\n"
	   "      depending on whether they are stack-\n"
	   "      sortable.\n"
	   "\n"
	   "      If <cmd> is 'shapes', then <arg> must be\n"
	   "      a digit from [1..9] inclusive, and will\n"
	   "      print all the _unique_ shapes of binary\n"
	   "      trees with that many nodes.\n"
	   "\n"
	   , basename(argv0));
}

int charcmp(const void * a, const void * b)
{
    return *((char*)a) - *((char*)b);
}

int checkArrayStr(const char * str)
{
    int len = strlen(str);
    if(len == 0)
      {
	printf("LENGTH\n");
	return FALSE;
      }
    int ret = TRUE;
    char * cpy = strdup(str);
    qsort(cpy, len, sizeof(char), charcmp);

    if(cpy[0] < '0' || cpy[len-1] > '9')
      {
	printf("OUT OF BOUNDS\n");
	ret = FALSE;
      }

    // Now just check for duplicates...
    int i;
    for(i = 1; i < len && ret; ++i)
      {
	if(cpy[i] == cpy[i-1])
	  {
	    printf("DUPLICATES\n");
	    ret = FALSE;
	  }
      }

    free(cpy);
    return ret;
}

int main(int argc, char * * argv)
{
  if(argc != 3) 
    {
      printUsage(argv[0]);
      return EXIT_FAILURE;
    }


  int ret = EXIT_SUCCESS;
  const char * cmd = argv[1];
  int * array = NULL;
  int len = 0;
  int i;
  int yo;
  char * * arrString = NULL;
  int numString = 0;
  int sortable = 0;
  int sortcheck = 0;
  int shapescheck = 0;

  if(strcmp(cmd, "sort") == 0 || strcmp(cmd, "sortable") == 0) 
    {
      //READ STRING
      arrString = readString(argv[2], & numString);
      printString(arrString, numString);
      for (yo = 0; yo < numString; yo ++)
	{
	  const char * arrstr = arrString[yo];

	  //CHECK 
	  if(!checkArrayStr(arrstr)) 
	    {
	      fprintf(stderr, "Invalid array, aborting\n");
	      return EXIT_FAILURE;
	    }
	  len = strlen(arrstr) - 2;
	  array = malloc(sizeof(int) * len);
	  for(i = 0; i < len; ++i) 
	    array[i] = arrstr[i] - '0';

	  if(strcmp(cmd, "sort") == 0) 
	    {
	      sortcheck = 1;
	      stackSort(array, len);
	      for(i = 0; i < len; ++i)
		printf("%d", array[i]);
	      printf("\n");
	    }
	

	  else if(strcmp(cmd, "sortable") == 0) 
	    {
	      if(isStackSortable(array, len))
		{
		  sortable++;
		}
	      else
		{
		
		}
	    }
	  free(array);
	}
    }
   
  else if(strcmp(cmd, "shapes") == 0) 
    {
      shapescheck = 1;
      len = atoi(argv[2]);
      if(len < 1 || len > 9) 
	{
	  fprintf(stderr, "Invalid number of shapes... "
		  "aborting\n");
	  ret = EXIT_FAILURE;
	} 
      else 
	{
	  genShapes(len);
	}
    }
  else 
    {
      fprintf(stderr, "Invalid command: '%s', aborting\n", cmd);
    }

  
  if (sortable == numString && !shapescheck && !sortcheck)
    {
      printf("YES\n");
    }
  else if (sortable == 0 && !shapescheck && !sortcheck)
    {
      printf("NO\n");
    }

    freeString(arrString, numString);
    return ret;
}

char * * readString(char * filename, int  *numString)
{
  char temp[MAXIMUM_LENGTH];
  FILE * fh;
  int i = 0;
  char * * arrstr;

  fh = fopen(filename, "r");
  if (fh != NULL)
    {
      while (fgets(temp, MAXIMUM_LENGTH, fh) != NULL)
	{
	  (* numString) ++;
	}
      arrstr = malloc(*numString * sizeof(char *));
      fseek(fh, 0, SEEK_SET);
      while (fgets(temp, MAXIMUM_LENGTH, fh) != NULL)
	{
	  arrstr[i] = malloc((strlen(temp) + 1) * sizeof(char *));
	  strcpy(arrstr[i], temp);
	  i++;
	}
      fclose(fh);
      return arrstr;
    }
  else 
    {
      fclose(fh);
      return NULL;
    }
}

void printString(char * * arrString, int numString)
{
  int i;
  for (i = 0; i < numString; i ++)
    {
      //int x = strlen(arrString[i]);
      //printf("%s", arrString[i]);
      /*if (arrString[i][x] != 10)
	{
	  arrString[i][x] = 10;
	  arrString[i][x + 1] = 0;
	  }*/
    }
}

void freeString(char * * arrString, int numString)
{
  int i;

  for (i = 0; i < numString; i++)
    {
      free(arrString[i]);
    }
  free(arrString);
}
