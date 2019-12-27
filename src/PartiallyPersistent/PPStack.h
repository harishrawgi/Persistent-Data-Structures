#ifndef PPSTACK_H
#define PPSTACK_H

#include "PPSinglyList.h"

typedef struct ppStack{

  struct ppSList* list;

}* PPStack;

//function to initialize an empty stack
PPStack init_PPStack();

//function to push an element on to the stack
int pushPPStack(PPStack stack, int key);

//function to check if a specified version of the stack is empty
int isEmptyPPStack(PPStack stack, int version, int *result);

//function which returns the element at the top of the stack of specified version
int topPPStack(PPStack stack, int version, int* result);

//function to pop the top element of the stack
int popPPStack(PPStack stack);

//function to print stack of a specified version
int printPPStack(PPStack stack, int version);

//function to free the stack
int freePPStack(PPStack stack);

#endif
