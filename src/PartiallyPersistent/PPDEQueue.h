#ifndef PPDEQUEUE_H
#define PPDEQUEUE_H

#include "PPCircularList.h"

typedef struct ppDeQueue{

  struct ppCList* list;

}* PPDEQueue;

//function to initialize an empty Queue
PPDEQueue init_PPDEQueue();

//function to insert an element on the end of Queue
int insertRearPPDEQueue(PPDEQueue queue, int key);

//function to insert an element on the front of Queue
int insertFrontPPDEQueue(PPDEQueue queue, int key);

//function to check if a specified version of the Queue is empty
int isEmptyPPDEQueue(PPDEQueue queue, int version, int *result);

//function which returns the element at the front of the Queue of specified version
int frontPPDEQueue(PPDEQueue queue, int version, int* result);

//function which returns the element at the front of the Queue of specified version
int rearPPDEQueue(PPDEQueue queue, int version, int* result);

//function to delete the rear element of the Queue
int deleteRearPPDEQueue(PPDEQueue queue);

//function to delete the front element of the Queue
int deleteFrontPPDEQueue(PPDEQueue queue);

//function to print Queue of a specified version
int printPPDEQueue(PPDEQueue queue, int version);

//function to free the Queue
int freePPDEQueue(PPDEQueue queue);

#endif
