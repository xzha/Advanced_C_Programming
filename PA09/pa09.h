#ifndef PA09_H
#define PA09_H
#include <stdio.h>

typedef struct _huffnode {
    int value; 
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next;
    HuffNode * node;
} Stack;

Stack * Stack_create(HuffNode * hn);
Stack * Stack_push(Stack * st, HuffNode * hn);
Stack * Stack_pop(Stack * st);
HuffNode * HuffNode_create(int value);
HuffNode * readbyByte(FILE *fh);
void Huff_postOrderPrint(HuffNode *tree); // temporary

#endif

