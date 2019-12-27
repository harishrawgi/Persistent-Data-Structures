#include "PPStack.h"
#include <stdio.h>
#include <stdlib.h>

//function to initialize an empty stack
PPStack init_PPStack(){

  //allocate memory for the new pp stack
  PPStack stack = (PPStack) malloc(sizeof(struct ppStack));
  if(!stack){
    printf("\nError in function init_ppStack(): unable to allocate memory for a new stack.\n");
    return NULL;
  }

  stack->list = init_PPSList();
  if(!stack->list){
    printf("\nError in function init_ppStack(): unable to create an empty list for a new stack.\n");
    return NULL;
  }

  return stack;
}

//function to push an element on to the stack
int pushPPStack(PPStack stack, int key){

  //validating inputs
  if(!stack){
    printf("\nError in function pushPPStack(): Invalid input parameter.\n");
    return 0;
  }

  //add the key to the front of the list
  if(!insertNodePPSList(stack->list, key)){
    printf("\nError in function pushPPStack(): Unable to push the element on to the stack.\n");
    return 0;
  }

  return 1;
}

//function to check if a specified version of the stack is empty
int isEmptyPPStack(PPStack stack, int version, int *result){

  //validating inputs
  if(!stack || version < 1){
    printf("\nError in function isEmptyPPStack(): Invalid input parameter.\n");
    return 0;
  }
  if(!stack->list){
    printf("\nError in function isEmptyPPStack): Empty stack.\n");
    return 0;
  }

  //check if someone is asking for future
  if(stack->list->d_liveVersion < version){
    printf("\nError in function isEmptyPPStack(): Can't travel to future.\n");
    return 0;
  }

  //check if the stack of the supplied version is empty
  if(!stack->list->ar_heads[version]){
    *result = 1;
  }
  else{
    *result = 0;
  }

  return 1;

}

//function which returns the element at the top of the stack of specified version
int topPPStack(PPStack stack, int version, int* result){

  //validating inputs
  if(!stack || version < 1){
    printf("\nError in function topPPStack(): Invalid input parameter.\n");
    return 0;
  }
  if(!stack->list){
    printf("\nError in function topPPStack(): Empty stack.\n");
    return 0;
  }

  //check if someone is asking for future
  if(stack->list->d_liveVersion < version){
    printf("\nError in function topPPStack(): Can't travel to future.\n");
    return 0;
  }

  //check if the stack of the supplied version is empty
  if(!stack->list->ar_heads[version]){
    printf("\nError in function topPPStack(): Empty stack in the version (%d).\n", version);
    return 0;
  }
  //if not, then we return the first element in the list of the specified version
  else{
    *result = stack->list->ar_heads[version]->d_data;
  }

  return 1;
}

//function to pop the top element of the stack
int popPPStack(PPStack stack){

  //validating inputs
  if(!stack){
    printf("\nError in function popPPStack(): Invalid input parameter.\n");
    return 0;
  }
  if(!stack->list){
    printf("\nError in function popPPStack(): Empty stack.\n");
    return 0;
  }

  int liveVersion = stack->list->d_liveVersion;

  //check if the stack of the supplied version is empty
  if(!stack->list->ar_heads[liveVersion]){
    printf("\nError in function popPPStack(): Empty stack in the live version (%d).\n", liveVersion);
    return 0;
  }
  //if not, then we return the first element in the list of the specified version
  else{
    //fetch the top_key, we'll delete this from list
    int top_key = stack->list->ar_heads[liveVersion]->d_data;

    //perform deletion
    if(!deleteNodePPSList(stack->list, top_key)){
      printf("\nError in function popPPStack(): Unable to pop (%d) from stack in the live version (%d).\n", top_key, liveVersion);
      return 0;
    }
  }

  return 1;
}

//function to print stack of a specified version
int printPPStack(PPStack stack, int version){

  //validating inputs
  if(!stack || version < 1){
    printf("\nError in function printPPStack(): Invalid input parameter.\n");
    return 0;
  }
  if(!stack->list){
    printf("\nError in function printPPStack(): Empty stack.\n");
    return 0;
  }

  //check if someone is asking for future
  if(stack->list->d_liveVersion < version){
    printf("\nError in function printPPStack(): Can't travel to future.\n");
    return 0;
  }

  //check if the stack of the supplied version is empty
  if(!stack->list->ar_heads[version]){
    printf("\nError in function printPPStack(): Empty stack in the version (%d).\n", version);
    return 0;
  }
  //print the stack if it is not empty
  else{
    if(!printPPSList(stack->list, version)){
      printf("\nError in function printPPStack(): Unable to print the stack in the version (%d).\n", version);
      return 0;
    }
  }

  return 1;
}

//function to free the stack
int freePPStack(PPStack stack){
  //validating inputs
  if(!stack){
    printf("\nError in function freePPStack(): Invalid input parameter.\n");
    return 0;
  }

  //free the list if it is not null
  if(stack->list){
    if(!freePPSList(stack->list)){
      printf("\nError in function freePPStack(): unable to free the stack.\n");
      return 0;
    }
    stack->list = NULL;
  }

  //free the stack
  free(stack);
  stack = NULL;

  return 1;
}
