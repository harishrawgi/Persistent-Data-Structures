#ifndef PPSINGLYLIST_H
#define PPSINGLYLIST_H

#include "PPSinglyListHelper.h"

#define MAX_VERSIONS 100

//the partial persistent singly linked list
typedef struct ppSList{

  //the array of pointers to the head nodes of diff versions of list
  struct ppslNode* ar_heads[MAX_VERSIONS];

  //holds the current live version on which any modifications will be performed
  int d_liveVersion;

}* PPSList;

//function to initialize the pp singly linked list
PPSList init_PPSList();

//function to insert a new node in the list (at the beginning)
int insertNodePPSList(PPSList list, int d_data);

//function to searching in a particular version of the list
int searchPPSList(PPSList list, int key, int version);

//function to delete a node in the list
int deleteNodePPSList(PPSList list, int key);

//function to print the list of a particular version
int printPPSList(PPSList list, int version);

//function to free the pp singly linked list
int freePPSList(PPSList list);

#endif
