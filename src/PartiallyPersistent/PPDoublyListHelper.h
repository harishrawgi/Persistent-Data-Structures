#ifndef PPDOUBLYLISTHELPER_H
#define PPDOUBLYLISTHELPER_H

#include "PPDoublyList.h"

struct ppdMods;
struct ppdlNode;

//structure representing a modification
typedef struct ppdMods{

  //stores the modified next pointer
  struct ppdlNode* p_next;

  //stores the modified previous pointer
  struct ppdlNode* p_prev;

  //stores the version of the modification
  int d_version;

}* PPDMods;

//structure which represents a node for the partially persistent singly linked list
typedef struct ppdlNode{

  //the field for storing the data
  int d_data;

  //the pointer to the next node in the linked list
  struct ppdlNode* p_next;

  //the pointer to the previous node in the linked list
  struct ppdlNode* p_prev;

  //the pointer for storing the inverse link (needed for persistence)
  struct ppdlNode* p_inverse;

  //the pointer for storing the modification
  PPDMods p_mods;

  //field to store the version number of this node
  int d_version;

}* PPDLNode;

//function to create a new pp modification with supplied parameters
//returns pointer to the created modification structure if succesfull, NULL otherwise
PPDMods createPPDModification(PPDLNode p_next, PPDLNode p_prev, int d_version);

//function to free the pp modification
int freePPDModification(PPDMods mod);

//function to create a new node for the pp singly linked list
PPDLNode createNewPPDLNode(int d_data, int d_version);

//function to modify a node to point to a new next node
int modifyNodePPDList(PPDLNode prev, PPDLNode newNext, int nextVersion);


#endif
