
#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack * st = malloc(sizeof(Stack));
  st -> list = NULL;
  return st;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
  if (stack == NULL)
    {
      return;
    }

  ListNode * head = stack -> list;
  ListNode * firstone = head;
  ListNode * nextone = head;

  while (firstone != NULL)
    {
      nextone = firstone -> next;
      free(firstone);
      firstone = nextone;
    }

  free(stack);
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if (stack -> list == NULL)
    {
      return TRUE;
    }
    return FALSE;
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{
  ListNode * head = stack -> list;
  int value = head -> value;
  stack -> list = head -> next;
  free(head);
    return value;
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
  ListNode * ln = malloc(sizeof(ListNode));
  ln -> value = value;
  ln -> next = stack -> list;
  stack -> list = ln;
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void stackSort(int * array, int len)
{
  int write_index = 0;
  int i;
  int value;
  int value2;
  Stack * st = Stack_create();

  if (isStackSortable(array, len))
    {
      for (i = 0; i < len; i ++)
	{
	  while (st->list != NULL && array[i] > st->list->value)
	    {
	      value = Stack_pop(st);
	      array[write_index] = value;
	      write_index++;
	    }
	  Stack_push(st, array[i]);
	}
      while (!Stack_isEmpty(st))
	{
	  value2 = Stack_pop(st);
	  array[write_index] = value2;
	  write_index++;
	}
    }
  Stack_destroy(st);
}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int isStackSortable(int * array, int len)
{
  int i;
  int max = 0;
  int maxpos = 0;

  // BASE CASE
  if (len < 3)
    {
      return TRUE;
    }

  // FIND MAXIMUM
  for (i = 0; i < len; i++)
    {
      if (array[i] > max)
	{
	  max = array[i];
	  maxpos = i;
	}
    }

  // SETUP LEFT AND RIGHT ARRAYS
  int * left = array;
  int left_len = maxpos;
  int * right = array + maxpos + 1; 
  int right_len = len - maxpos - 1;

  if(left_len > 0 && right_len > 0) 
    {
      //PARTITION LEFT
      int leftmax = 0;
      int j;

      for (j = 0; j < maxpos; j++)
	{
	  if (left[j] > leftmax)
	    {
	      leftmax = left[j];
	    }
	}

      //PARTITION RIGHT
      int rightmin = 10;
      int k;

      for (k = 0; k < len - maxpos - 1; k ++)
	{
	  if (right[k] < rightmin)
	    {
	      rightmin = right[k];
	    }
	}

      //CHECK
      if (leftmax > rightmin)
	{
	  return FALSE;
	}
    } 

  if (isStackSortable(left, left_len) == 1 && isStackSortable(right, right_len) == 1)
    {
      return TRUE;
    }
  return FALSE;
}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [0..k-1] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */

void permutate (int * array, int base, int length);
void swap (int * one, int * two);

void genShapes(int k)
{
  int i;
  int * array = malloc(sizeof(int) * k);

  for (i = 0; i < k; i ++)
    {
      array[i] = i;
    }
  permutate(array, 0, k);
  free(array);
}

// Create permutations, based on partition function
void permutate (int * array, int i, int length)
{
  int j;
  if (i == length)
    {
      if (isStackSortable(array, length))
	{
	  TreeNode * root = NULL;
	  root = Tree_build(array, length); // call tree.h
	  Tree_printShape(root);
	  Tree_destroy(root);
	}
    }
  for (j = i; j < length; j ++)
    {
      swap(array + i, array + j);
      permutate(array, i + 1, length);
      swap(array + i, array + j);
    }
}

// Swap values
void swap(int * one , int * two)
{
  int temp = * one;
  * one = * two;
  * two = temp;
}
