#include "pa09.h"
#include <stdio.h>
#include <stdlib.h>

/********************************************************
 * Method: read the file byte by byte
 * 
 * Input Arguments: the file handle of the file
 * Return: the root of the constructed tree
 *
 *******************************************************/
HuffNode * readbyByte (FILE * fh)
{
  int read;
  int readmore;
  int newline = 2;
  Stack * st = NULL;

  while (!feof(fh) && newline)
    {
      read = fgetc(fh);
      if (read == '\n')
	{
	  newline -= 1;
	}
      if (read == '1')
	{
	  readmore = fgetc(fh);
	  HuffNode * hn = HuffNode_create(readmore);
	  st = Stack_push(st, hn);
	}
      if (read == '0')
	{
	  HuffNode * huff = st -> node;
	  st = Stack_pop(st);
	  if (st == NULL)
	    {
	      return huff;
	    }
	  else
	    {
	      HuffNode * node = st -> node;
	      st = Stack_pop(st);
	      HuffNode * more = malloc(sizeof(HuffNode));
	      more -> value = ' ';
	      more -> right = huff;
	      more -> left = node;
	      st = Stack_push(st, more);
	    }
	}
    }

  return NULL;
}

/*******************************************************
 * Create the Huffman node
 *
 * Input argument: the value to be store
 * Return: the huffman node
 *
 ******************************************************/
HuffNode * HuffNode_create(int val)
{
  HuffNode * hn = malloc(sizeof(HuffNode));
  hn -> value = val;
  hn -> left = NULL;
  hn -> right = NULL;
  return hn;
}

/*******************************************************
 * Push huffnode into the stack
 *
 * Input argument: header of stack, and the root
 * Return: header of the stack
 *
 ******************************************************/
Stack * Stack_push(Stack * st, HuffNode * hn)
{
  Stack * newnode = Stack_create(hn);
  newnode -> next = st;
  return newnode;
}

/*******************************************************
 * Create the stack
 *
 * Input argument: huffman node
 * Return: the header of the stack
 *
 ******************************************************/
Stack * Stack_create(HuffNode * hn)
{
  Stack * st = malloc(sizeof(Stack));
  st -> node = hn;
  st -> next = NULL;
  return st;
}

/*******************************************************
 * Pop the stack
 *
 * Input argument: header of the stack
 * Return: the header of the stack
 *
 ******************************************************/
Stack * Stack_pop(Stack * st)
{
  if (st == NULL)
    {
      return st;
    }
  Stack * nextone = st -> next;
  free (st);
  return nextone;
}

/********************************************************
 * Method: read the file bit by bit
 * 
 * Input Arguments: the file handle of the file
 * Return: the root of the constructed tree
 *
 *******************************************************/
HuffNode * readbyBit(FILE * fptr)
{
  int loc = 0;
  int done = 0; // tree not done
  Stack * st = NULL;

  while (! feof (fptr))
    {
      unsigned char firstbyte = fgetc(fptr);
      unsigned char mask[] =  {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
        
      while (!done)
        {
	  loc %= 8;
	  while ((firstbyte & mask[loc]) != 0)
            {
	      unsigned char secondbyte = fgetc(fptr);
	      unsigned char joinedbyte;
	      unsigned char x = firstbyte;
	      unsigned char y = secondbyte;
	      if (loc == 7)
                {
		  unsigned char nextbyte = fgetc(fptr);
		  joinedbyte = secondbyte;
		  loc = 0;
		  firstbyte = nextbyte;
                }
	      else
                {
		  x <<= (loc + 1);
		  y >>= (7 - loc);
		  joinedbyte = x + y;
		  loc ++;
		  firstbyte = secondbyte;
                }
	      HuffNode * hn = HuffNode_create(joinedbyte);
	      st = Stack_push(st, hn);
            }
    
        
	  if ((firstbyte & mask[loc]) == 0)
            {
	      HuffNode * huff = st -> node;
	      st = Stack_pop(st);
	      if (st == NULL)
		{
		  done = 1;
		  return huff;
		}
	      else
		{
		  HuffNode * node = st -> node;
		  st = Stack_pop(st);
		  HuffNode * more = malloc(sizeof(HuffNode));
		  more -> value = ' ';
		  more -> right = huff;
		  more -> left = node;
		  st = Stack_push(st, more);
		}
	      if (loc == 7)
                {
		  unsigned char consecbyte = fgetc(fptr);
		  firstbyte = consecbyte;
		  loc = 0;
                }
	      else
                {
		  loc ++;
                }
            }
        }
    }
      return NULL;
}

/********************************************************
 * Method: print the tree to file
 * 
 * Input Arguments: the file handle of the file and root
 * Return: NULL
 *
 *******************************************************/
void printtoFile(FILE * fh, HuffNode * root)
{
  if (root == NULL)
    {
      return;
    }
  fprintf(fh, "Left\n");
  printtoFile(fh, root -> left);
  fprintf(fh, "Back\n");
  fprintf(fh, "Right\n");
  printtoFile(fh, root -> right);
  fprintf(fh, "Back\n");
  if (root -> left == NULL && root -> right == NULL)
    {
      fprintf(fh, "Leaf: %c\n", root->value);
    }
}

/********************************************************
 * Method: destroy the tree
 * 
 * Input Arguments: the root of the tree
 * Return: NULL
 *
 *******************************************************/
void HuffNode_destroy(HuffNode * root)
{
  if (root == NULL)
    {
      return;
    }
  HuffNode_destroy(root -> left);
  HuffNode_destroy(root -> right);
  free (root);
}
