/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>

//int count(int [], int);
void print(int [], int);
void partition(int [], int, int);

void partitionTestIncreasing(int [], int, int);
int increasing(int [], int);

void partitionTestDecreasing(int [], int, int);
int decreasing(int [], int);

void partitionTestOdd(int [], int, int);
int odd(int [], int);

void partitionTestEven(int [], int, int);
int even(int [], int);

void partitionTestOddEven(int [], int, int);
int oddeven(int [], int);

void partitionTestPrime(int [], int, int);
int prime(int [], int);



/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */


void partitionAll(int value)
{
  
  int arr[MAXLENGTH];
  //  int i;
  int j = 0;

  printf("partitionAll %d\n", value);
  //  for (i = 1; i <= value; i ++)
  //    {
  //      arr[0] = i;
  partition(arr, value, j);
  //    }
}

void partition(int arr[], int value, int i)
{
  int j;
 
  // applied the methods learned from class

  if (value == 0 /*&& count(arr, i - 1) == input*/)
    {
      print(arr, i);
      return;
    }
  for (j = 1; j <= value; j++)
    {
      arr[i] = j;
      partition(arr, value - j, i + 1);
    }
    
}
void print(int arr[], int length)
{
  int i;
    
  for (i = 0; i < length; i++)
    {
      if (i == 0)
        {
	  printf("= ");
        }
      printf("%d", arr[i]);
        
      if (i < length - 1)
        {
	  printf(" + ");
        }
      else
        {
	  printf("\n");
        }
    }
}

/*int count(int arr[], int length)
  {
  int i;
  int j = 0;
    
  for (i = 0; i < length; i ++)
  {
  j += arr[i];
  }
  return j;
  }*/
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionIncreasing(int value)

{
  int arr[MAXLENGTH];
  //  int i;
  int j = 0;
  printf("partitionIncreasing %d\n", value);
  //  for (i = 1; i <= value; i ++)
  //    {
  //      arr[0] = i;
  partitionTestIncreasing(arr, value, j);
  //    }
}

void partitionTestIncreasing(int arr[], int value, int i)
{
  int j;
    
  if (value == 0 /*&& count(arr, i - 1) == input)*/ && increasing(arr, i))
    {
      print(arr, i);
      return;
    }
  for (j = 1; j <= value; j++)
    {
      arr[i] = j;
      partitionTestIncreasing(arr, value - j, i + 1);
    }
}

int increasing(int arr[], int length)
{
  int x = 0;
  int i;
  int j = 1;
    
  for (i = 0; i < length; i++)
    {
      if (arr[i] > x) // compare the element with the largest number
        {
	  x = arr[i]; // store the largest number
        }
      else
        {
	  return 0;
        }
    }
  return j;
}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionDecreasing(int value)
{
  int arr[MAXLENGTH];
  //  int i;
  int j = 0;
  printf("partitionDecreasing %d\n", value);
  //  for (i = 1; i <= value; i ++)
  //    {
  //      arr[0] = i;
  partitionTestDecreasing(arr, value, j);
  //    }

}

void partitionTestDecreasing(int arr[], int value, int i)
{
  int j;
    
  if (value == 0 /*&& count(arr, i - 1) == input) */&& decreasing(arr, i))
    {
      print(arr, i);
      return;
    }
  for (j = 1; j <= value; j++)
    {
      arr[i] = j;
      partitionTestDecreasing(arr, value - j, i + 1);
    }
}

int decreasing(int arr[], int length)
{
  int x = 100;
  int i;
  int j = 1;
    
  for (i = 0; i < length; i++)
    {
      if (arr[i] < x) // compare the element with the smallest number
        {
	  x = arr[i]; // store the smallest number
        }
      else
        {
	  return 0;
        }
    }
  return j;
}
/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOdd(int value)
{
  int arr[MAXLENGTH];
  //  int i;
  int j = 0;
  printf("partitionOdd %d\n", value);
  //  for (i = 1; i <= value; i ++)
  //    {
  //      arr[0] = i;
  partitionTestOdd(arr, value, j);
  //    }
}
void partitionTestOdd(int arr[], int value, int i)
{
  int j;
    
  if (value == 0 /*&& count(arr, i - 1) == input)*/ && odd(arr, i ))
    {
      print(arr, i);
      return;
    }
  for (j = 1; j <= value; j++)
    {
      arr[i] = j;
      partitionTestOdd(arr, value - j, i + 1);
    }
}

int odd(int arr[], int length)
{
  int i;
  int j = 1;
    
  for (i = 0; i < length; i++)
    {
      if (arr[i] % 2 == 1) // if the number cannot be modded by 2 means the number is odd
        {
        }
      else
        {
	  return 0;
        }
    }
  return j;
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionEven(int value)
{
  int arr[MAXLENGTH];
  //  int i;
  int j = 0;
  printf("partitionEven %d\n", value);
  //  for (i = 1; i <= value; i ++)
  //    {
  //      arr[0] = i;
  partitionTestEven(arr, value, j);
  //    }
}
void partitionTestEven(int arr[], int value, int i)
{
  int j;
    
  if (value == 0 /*&& count(arr, i - 1) == input)*/ && even(arr, i))
    {
      print(arr, i );
      return;
    }
  for (j = 1; j <= value; j++)
    {
      arr[i] = j;
      partitionTestEven(arr, value - j, i + 1);
    }
}

int even(int arr[], int length)
{
  int i;
  int j = 1;
    
  for (i = 0; i < length; i++) // if the number can be modded by two means its even
    {
      if (arr[i] % 2 == 0)
        {
        }
      else
        {
	  return 0;
        }
    }
  return j;
}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOddAndEven(int value)
{
  int arr[MAXLENGTH];
  //  int i;
  int j = 0;
  printf("partitionOddAndEven %d\n", value);
  //  for (i = 1; i <= value; i ++)
  //    {
  //      arr[0] = i;
  partitionTestOddEven(arr, value, j);
  //    }
}
void partitionTestOddEven(int arr[], int value, int i)
{
  int j;
    
  if (value == 0 /*&& count(arr, i - 1) == input)*/ && oddeven(arr, i))
    {
      print(arr, i);
      return;
    }
  for (j = 1; j <= value; j++)
    {
      arr[i] = j;
      partitionTestOddEven(arr, value - j, i + 1);
    }
}

int oddeven(int arr[], int length)
{
  int i;
  int j = 1;
    
  if (length == 1)
    {
      if (arr[0] % 2 == 0) // if the value inputted is even return 0
	{
	  return 0;
	}
    }
  for (i = 0; i < length - 1; i += 2)
    {
      if (arr[i] % 2 == 1 && arr[i + 1] % 2 == 0 && (arr[length - 2] % 2 ==0 && arr[length - 1] % 2 == 1)) // compare the array elements, also the last two elements
        {  
        }
      else if (arr[i] % 2 == 1 && arr[i + 1] % 2 == 0 && (arr[length - 2] % 2 == 1 &&arr[length - 1] % 2 == 0)) // compre the array, also the last two elements
        {
        }
      else
        {
	  return 0;
        }
    }
  return j;
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */



void partitionPrime(int value)
{
  int arr[MAXLENGTH];
  //  int i;
  int j = 0;
  printf("partitionPrime %d\n", value);
  //  for (i = 1; i <= value; i ++)
  //    {
  //      arr[0] = i;
  partitionTestPrime(arr, value, j);
  //    }
}
void partitionTestPrime(int arr[], int value, int i)
{
  int j;
    
  if (value == 0 /*&& count(arr, i - 1) == input)*/ && prime(arr, i))
    {
      print(arr, i);
      return;
    }
  for (j = 1; j <= value; j++)
    {
      arr[i] = j;
      partitionTestPrime(arr, value - j, i + 1);
    }
}

int prime(int arr[], int length)
{
  int i;
  int j = 1;
  int k;
    
  for (i = 0; i < length; i ++)
    {
      if (arr[i] == 1) // if array has one, return 0
        {
	  return 0;
        }
      for (k = 2; k < arr[i] - 1; k++)
        {
	  if (arr[i] % k == 0) // if the element modded by k is 0, return 0
            {
	      return 0;
            }
        }
    }
  return j;
}
