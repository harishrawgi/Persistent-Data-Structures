#ifndef PPQUEUE_H
#define PPQUEUE_H

#include "PPCircularList.h"

typedef struct ppQueue{

  struct ppCList* list;

}* PPQueue;

//function to initialize an empty Queue
PPQueue init_PPQueue();

//function to insert an element on to the Queue
int enqueuePPQueue(PPQueue queue, int key);

//function to check if a specified version of the Queue is empty
int isEmptyPPQueue(PPQueue queue, int version, int *result);

//function which returns the element at the front of the Queue of specified version
int frontPPQueue(PPQueue queue, int version, int* result);

//function which returns the element at the front of the Queue of specified version
int rearPPQueue(PPQueue queue, int version, int* result);

//function to dequeu the top element of the Queue
int dequeuePPQueue(PPQueue queue);

//function to print Queue of a specified version
int printPPQueue(PPQueue queue, int version);

//function to free the Queue
int freePPQueue(PPQueue queue);

#endif
