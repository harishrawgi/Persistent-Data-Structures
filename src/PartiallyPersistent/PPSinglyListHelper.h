#ifndef PPSINGLYLISTHELPER_H
#define PPSINGLYLISTHELPER_H

#include "PPSinglyList.h"

struct ppMods;
struct ppslNode;

//structure representing a modification
typedef struct ppMods{

  //stores the modified next pointer
  struct ppslNode* p_next;

  //stores the version of the modification
  int d_version;

}* PPMods;

//structure which represents a node for the partially persistent singly linked list
typedef struct ppslNode{

  //the field for storing the data
  int d_data;

  //the pointer to the next node in the linked list
  struct ppslNode* p_next;

  //the pointer for storing the inverse link (needed for persistence)
  struct ppslNode* p_inverse;

  //the pointer for storing the modification
  PPMods p_mods;

  //field to store the version number of this node
  int d_version;

}* PPSLNode;

//function to create a new pp modification with supplied parameters
//returns pointer to the created modification structure if succesfull, NULL otherwise
PPMods createPPModification(PPSLNode p_next, int d_version);

//function to free the pp modification
int freePPModification(PPMods mod);

//function to create a new node for the pp singly linked list
PPSLNode createNewPPSLNode(int d_data, int d_version);

//function to modify a node to point to a new next node
int modifyNodePPSList(PPSLNode prev, PPSLNode newNext, int nextVersion);


#endif
