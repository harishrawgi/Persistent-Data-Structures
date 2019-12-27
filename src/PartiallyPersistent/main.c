#include "PPSinglyList.h"
#include "PPDoublyList.h"
#include "PPStack.h"
#include "PPCircularList.h"
#include "PPQueue.h"
#include "PPDEQueue.h"
#include <stdio.h>
#include <stdlib.h>

int testPPSList(){

  PPSList list = init_PPSList();
  if(!list){
    printf("\nError in testPPSList(): Unable to initialize a pp singly linked list.\n");
    return 0;
  }

  for(int i=0; i<10; i++){
    if(!insertNodePPSList(list, i)){
      printf("\nError in testPPSList(): Unable to insert (%d) in a pp singly linked list.\n", i);
      return 0;
    }
  }

  printPPSList(list, 6);
  printPPSList(list, 10);

  for(int i=0; i<10; i+=2){
    if(!deleteNodePPSList(list, i)){
      printf("\nError in testPPSList(): Unable to delete (%d) in a pp singly linked list.\n", i);
      return 0;
    }
  }

  if(!deleteNodePPSList(list, 9)){
    printf("\nError in testPPSList(): Unable to delete (%d) in a pp singly linked list.\n", 9);
    return 0;
  }

  printPPSList(list, 10);
  printPPSList(list, 11);
  printPPSList(list, 12);
  printPPSList(list, 13);
  printPPSList(list, 14);
  printPPSList(list, 15);
  printPPSList(list, 16);

  int res = searchPPSList(list, 6, 16);
  printf("\nResult of searching (%d) in version (%d): (%d)\n", 6, 16, res);

  res = searchPPSList(list, 6, 13);
  printf("\nResult of searching (%d) in version (%d): (%d)\n", 6, 13, res);

  if(!freePPSList(list)){
    printf("\nError in testPPSList(): Unable to free the pp singly linked list.\n");
    return 0;
  }

  return 1;
}

int testPPCList(){

  PPCList list = init_PPCList();
  if(!list){
    printf("\nError in testPPCList(): Unable to initialize a pp circular linked list.\n");
    return 0;
  }

  for(int i=0; i<10; i++){

    if(i%2 == 0){
      if(!insertNodeEndPPCList(list, i)){
        printf("\nError in testPPCList(): Unable to insert (%d) in a pp circular linked list.\n", i);
        return 0;
      }
      printPPCList(list, i+1);
    }
    else{
      if(!insertNodeBeginPPCList(list, i)){
        printf("\nError in testPPCList(): Unable to insert (%d) in a pp circular linked list.\n", i);
        return 0;
      }
      printPPCList(list, i+1);
    }

  }

  for(int i=0; i<10; i+=2){
    if(!deleteNodePPCList(list, i)){
      printf("\nError in testPPCList(): Unable to delete (%d) in a pp circular linked list.\n", i);
      return 0;
    }
  }

  if(!deleteNodePPCList(list, 9)){
    printf("\nError in testPPCList(): Unable to delete (%d) in a pp circular linked list.\n", 9);
    return 0;
  }

  printPPCList(list, 10);
  printPPCList(list, 11);
  printPPCList(list, 12);
  printPPCList(list, 13);
  printPPCList(list, 14);
  printPPCList(list, 15);
  printPPCList(list, 16);

  int res = searchPPCList(list, 6, 16);
  printf("\nResult of searching (%d) in version (%d): (%d)\n", 6, 16, res);

  res = searchPPCList(list, 6, 13);
  printf("\nResult of searching (%d) in version (%d): (%d)\n", 6, 13, res);

/*
  if(!freePPCList(list)){
    printf("\nError in testPPCList(): Unable to free the pp singly linked list.\n");
    return 0;
  }
*/

  return 1;
}

int testPPDList(){

  PPDList list = init_PPDList();
  if(!list){
    printf("\nError in testPPDList(): Unable to initialize a pp doubly linked list.\n");
    return 0;
  }

  for(int i=0; i<10; i++){
    if(!insertNodePPDList(list, i)){
      printf("\nError in testPPDList(): Unable to insert (%d) in a pp doubly linked list.\n", i);
      return 0;
    }
  }

  printPPDList(list, 6);
  printPPDList(list, 10);

  for(int i=0; i<10; i+=2){
    if(!deleteNodePPDList(list, i)){
      printf("\nError in testPPDList(): Unable to delete (%d) in a pp doubly linked list.\n", i);
      return 0;
    }
  }

  if(!deleteNodePPDList(list, 9)){
    printf("\nError in testPPDList(): Unable to delete (%d) in a pp doubly linked list.\n", 9);
    return 0;
  }

  printPPDList(list, 10);
  printPPDList(list, 11);
  printPPDList(list, 12);
  printPPDList(list, 13);
  printPPDList(list, 14);
  printPPDList(list, 15);
  printPPDList(list, 16);

  int res = searchPPDList(list, 6, 16);
  printf("\nResult of searching (%d) in version (%d): (%d)\n", 6, 16, res);

  res = searchPPDList(list, 6, 13);
  printf("\nResult of searching (%d) in version (%d): (%d)\n", 6, 13, res);

/*
  if(!freePPDList(list)){
    printf("\nError in testPPDList(): Unable to free the pp doubly linked list.\n");
    return 0;
  }
*/

  return 1;
}

int testPPStack(){

  PPStack stack = init_PPStack();
  if(!stack){
    printf("\nError in testPPStack(): Unable to initialize a pp stack.\n");
    return 0;
  }

  for(int i=0; i<10; i++){
    if(!pushPPStack(stack, i)){
      printf("\nError in testPPStack(): Unable to push (%d) in the pp stack.\n", i);
      return 0;
    }
  }

  printPPStack(stack, 6);
  printPPStack(stack, 10);

  for(int i=0; i<10; i++){
    if(!popPPStack(stack)){
      printf("\nError in testPPStack(): Unable to pop in the pp stack.\n");
      return 0;
    }
  }


  printPPStack(stack, 10);
  printPPStack(stack, 12);
  printPPStack(stack, 14);
  printPPStack(stack, 16);
  printPPStack(stack, 18);
  printPPStack(stack, 20);

  int top;
  topPPStack(stack, 13, &top);
  printf("\nTop of the stack in version (%d): (%d)\n", 13, top);

  topPPStack(stack, 5, &top);
  printf("\nTop of the stack in version (%d): (%d)\n", 5, top);

  int res = 0;
  isEmptyPPStack(stack, 18, &res);
  if(!res){
    printf("\nStack is not empty in version (%d)\n", 18);
  }
  else{
    printf("\nStack is empty in version (%d)\n", 18);
  }

  isEmptyPPStack(stack, 20, &res);
  if(!res){
    printf("\nStack is not empty in version (%d)\n", 20);
  }
  else{
    printf("\nStack is empty in version (%d)\n", 20);
  }

/*
  if(!freePPStack(stack)){
    printf("\nError in testPPStack(): Unable to free the pp stack.\n");
    return 0;
  }
*/

  return 1;
}

int testPPQueue(){

  PPQueue Queue = init_PPQueue();
  if(!Queue){
    printf("\nError in testPPQueue(): Unable to initialize a pp Queue.\n");
    return 0;
  }

  for(int i=0; i<10; i++){
    if(!enqueuePPQueue(Queue, i)){
      printf("\nError in testPPQueue(): Unable to insert (%d) in the pp Queue.\n", i);
      return 0;
    }
  }


  for(int i=0; i<10; i++){
    if(!dequeuePPQueue(Queue)){
      printf("\nError in testPPQueue(): Unable to delete in the pp Queue.\n");
      return 0;
    }
    printPPQueue(Queue, i+11);
  }


  int front, rear;
  frontPPQueue(Queue, 13, &front);
  rearPPQueue(Queue, 13, &rear);
  printf("\nFront of the Queue in version (%d): (%d)\n", 13, front);
  printf("\nRear of the Queue in version (%d): (%d)\n", 13, rear);

  frontPPQueue(Queue, 5, &front);
  rearPPQueue(Queue, 5, &rear);
  printf("\nFront of the Queue in version (%d): (%d)\n", 5, front);
  printf("\nRear of the Queue in version (%d): (%d)\n", 5, rear);

  int res = 0;
  isEmptyPPQueue(Queue, 18, &res);
  if(!res){
    printf("\nQueue is not empty in version (%d)\n", 18);
  }
  else{
    printf("\nQueue is empty in version (%d)\n", 18);
  }

  isEmptyPPQueue(Queue, 20, &res);
  if(!res){
    printf("\nQueue is not empty in version (%d)\n", 20);
  }
  else{
    printf("\nQueue is empty in version (%d)\n", 20);
  }

/*
  if(!freePPQueue(Queue)){
    printf("\nError in testPPQueue(): Unable to free the pp Queue.\n");
    return 0;
  }
*/

  return 1;
}

int testPPDEQueue(){

  PPDEQueue Queue = init_PPDEQueue();
  if(!Queue){
    printf("\nError in testPPDEQueue(): Unable to initialize a pp Queue.\n");
    return 0;
  }

  for(int i=0; i<10; i++){
    if(i%2 == 0){
      if(!insertRearPPDEQueue(Queue, i)){
        printf("\nError in testPPDEQueue(): Unable to insert (%d) in the pp Queue.\n", i);
        return 0;
      }
    }
    else{
      if(!insertFrontPPDEQueue(Queue, i)){
        printf("\nError in testPPDEQueue(): Unable to insert (%d) in the pp Queue.\n", i);
        return 0;
      }
    }
  }

  printPPDEQueue(Queue, 10);

  for(int i=0; i<10; i++){
    if(i%2 ==0){
      if(!deleteFrontPPDEQueue(Queue)){
        printf("\nError in testPPDEQueue(): Unable to delete in the pp Queue.\n");
        return 0;
      }
    }
    else{
      if(!deleteRearPPDEQueue(Queue)){
        printf("\nError in testPPDEQueue(): Unable to delete in the pp Queue.\n");
        return 0;
      }
    }
    printPPDEQueue(Queue, i+11);
  }


  int front, rear;
  frontPPDEQueue(Queue, 13, &front);
  rearPPDEQueue(Queue, 13, &rear);
  printf("\nFront of the Queue in version (%d): (%d)\n", 13, front);
  printf("\nRear of the Queue in version (%d): (%d)\n", 13, rear);

  frontPPDEQueue(Queue, 5, &front);
  rearPPDEQueue(Queue, 5, &rear);
  printf("\nFront of the Queue in version (%d): (%d)\n", 5, front);
  printf("\nRear of the Queue in version (%d): (%d)\n", 5, rear);

  int res = 0;
  isEmptyPPDEQueue(Queue, 18, &res);
  if(!res){
    printf("\nQueue is not empty in version (%d)\n", 18);
  }
  else{
    printf("\nQueue is empty in version (%d)\n", 18);
  }

  isEmptyPPDEQueue(Queue, 20, &res);
  if(!res){
    printf("\nQueue is not empty in version (%d)\n", 20);
  }
  else{
    printf("\nQueue is empty in version (%d)\n", 20);
  }

/*
  if(!freePPDEQueue(Queue)){
    printf("\nError in testPPDEQueue(): Unable to free the pp Queue.\n");
    return 0;
  }
*/

  return 1;
}

int main(){

  printf("\nWhat do you wanna test: \n");
  printf("\n1. Partially persistent singly linked list\n");
  printf("\n2. Partially persistent doubly linked list\n");
  printf("\n3. Partially persistent stack\n");
  printf("\n4. Partially persistent circularly linked list\n");
  printf("\n5. Partially persistent queue\n");
  printf("\n6. Partially persistent double-ended queue\n");
  int ch;
  scanf("%d", &ch);

  switch(ch){
    case 1: if(!testPPSList()){
              printf("\nError in main(): Unable to execute testPPSList().\n");
              exit(0);
            }
            break;

    case 2: if(!testPPDList()){
              printf("\nError in main(): Unable to execute testPPDList().\n");
              exit(0);
            }
            break;

    case 3: if(!testPPStack()){
              printf("\nError in main(): Unable to execute testPPStack().\n");
              exit(0);
            }
            break;

    case 4: if(!testPPCList()){
              printf("\nError in main(): Unable to execute testPPCList().\n");
              exit(0);
            }
            break;

    case 5: if(!testPPQueue()){
              printf("\nError in main(): Unable to execute testPPQueue().\n");
              exit(0);
            }
            break;

    case 6: if(!testPPDEQueue()){
              printf("\nError in main(): Unable to execute testPPDEQueue().\n");
              exit(0);
            }
            break;

    default:  printf("\nError in main(): Invalid choice.\n");
              exit(0);
  }

  return 0;

}
