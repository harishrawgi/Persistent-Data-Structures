#ifndef PPCIRCULARLISTHELPER_H
#define PPCIRCULARLISTHELPER_H

#include "PPCircularList.h"

struct ppcMods;
struct ppclNode;

//structure representing a modification
typedef struct ppcMods{

  //stores the modified next pointer
  struct ppclNode* p_next;

  //stores the version of the modification
  int d_version;

}* PPCMods;

//structure which represents a node for the partially persistent Circular linked list
typedef struct ppclNode{

  //the field for storing the data
  int d_data;

  //the pointer to the next node in the linked list
  struct ppclNode* p_next;

  //the pointer for storing the inverse link (needed for persistence)
  struct ppclNode* p_inverse;

  //the pointer to keep track of the copy node
  struct ppclNode* p_copy;

  //the pointer for storing the modification
  PPCMods p_mods;

  //field to store the version number of this node
  int d_version;

}* PPCLNode;

//function to create a new pp modification with supplied parameters
//returns pointer to the created modification structure if succesfull, NULL otherwise
PPCMods createPPCModification(PPCLNode p_next, int d_version);

//function to free the pp modification
int freePPCModification(PPCMods mod);

//function to create a new node for the pp Circular linked list
PPCLNode createNewPPCLNode(int d_data, int d_version);



#endif
