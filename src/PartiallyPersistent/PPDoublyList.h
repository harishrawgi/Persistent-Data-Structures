#ifndef PPDOUBLYLIST_H
#define PPDOUBLYLIST_H

#include "PPDoublyListHelper.h"

#define MAX_VERSIONS 100

//the partial persistent doubly linked list
typedef struct ppDList{

  //the array of pointers to the head nodes of diff versions of list
  struct ppdlNode* ar_heads[MAX_VERSIONS];

  //holds the current live version on which any modifications will be performed
  int d_liveVersion;

}* PPDList;

//function to initialize the pp doubly linked list
PPDList init_PPDList();

//function to insert a new node in the list (at the beginning)
int insertNodePPDList(PPDList list, int d_data);

//function to searching in a particular version of the list
int searchPPDList(PPDList list, int key, int version);

//function to delete a node in the list
int deleteNodePPDList(PPDList list, int key);

//function to delete a node in the list
int deleteGivenNodePPDList(PPDList list, struct ppdlNode* node);

//function to print the list of a particular version
int printPPDList(PPDList list, int version);

//function to free the pp doubly linked list
int freePPDList(PPDList list);

#endif
