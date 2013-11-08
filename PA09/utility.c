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

/*******************************************************
 * Print the huffman tree
 *
 * Input argument: the root of the tree
 * Return: NULL
 *
 ******************************************************/
/* DO NOT MODIFY THIS FUNCTION!!! */
void Huff_postOrderPrint(HuffNode *tree)
{
    // Base case: empty subtree
    if (tree == NULL) {
		return;
    }

    // Recursive case: post-order traversal

    // Visit left
    printf("Left\n");
    Huff_postOrderPrint(tree->left);
	printf("Back\n");
    // Visit right
    printf("Right\n");
    Huff_postOrderPrint(tree->right);
	printf("Back\n");
    // Visit node itself (only if leaf)
    if (tree->left == NULL && tree->right == NULL) {
		printf("Leaf: %c\n", tree->value);
    }
    

}
