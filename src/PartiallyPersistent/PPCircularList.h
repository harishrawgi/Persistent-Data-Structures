#ifndef PPCIRCULARLIST_H
#define PPCIRCULARLIST_H

#include "PPCircularListHelper.h"

#define MAX_VERSIONS 100

//the partial persistent Circular linked list
typedef struct ppCList{

  //the array of pointers to the last nodes of diff versions of list
  struct ppclNode* ar_lasts[MAX_VERSIONS];

  //holds the current live version on which any modifications will be performed
  int d_liveVersion;

}* PPCList;

//function to initialize the pp Circular linked list
PPCList init_PPCList();

//function to insert a new node in the list (at the end)
int insertNodeEndPPCList(PPCList list, int d_data);

//function to insert a new node in the list (at the beginning)
int insertNodeBeginPPCList(PPCList list, int d_data);

//function to searching in a particular version of the list
int searchPPCList(PPCList list, int key, int version);

//function to delete a node in the list
int deleteNodePPCList(PPCList list, int key);

//function to print the list of a particular version
int printPPCList(PPCList list, int version);

//function to free the pp Circular linked list
int freePPCList(PPCList list);

//function to modify a node to point to a new next node
int modifyNodePPCList(PPCList list, struct ppclNode* prev, struct ppclNode* newNext, int nextVersion);

//helper function to free the node and nodes next to it Recursively
int freePPCListHelper(struct ppclNode* node);


#endif
