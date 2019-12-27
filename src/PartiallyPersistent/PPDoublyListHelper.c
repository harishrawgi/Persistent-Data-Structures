#include "PPDoublyListHelper.h"

#include <stdio.h>
#include <stdlib.h>

//function to create a new pp modification with supplied parameters
//returns pointer to the created modification structure if succesfull, NULL otherwise
PPDMods createPPDModification(PPDLNode p_next, PPDLNode p_prev,  int d_version){

  //input validating
  //p_next is allowed to be NULL, because we might modify a node to point to NULL
  //same for p_prev
  if(d_version < 0){
    printf("\nError in function createPPDModification(): Invalid input parameters.\n");
    return NULL;
  }

  //allocate memory for a new modification
  PPDMods mod = (PPDMods) malloc(sizeof(struct ppdMods));
  if(!mod){
    printf("\nError in function createPPDModification(): unable to allocate memory for a new modification.\n");
    return NULL;
  }

  //populating the modification
  mod->d_version = d_version;
  mod->p_next = p_next;
  mod->p_prev = p_prev;

  //return the created modification
  return mod;
}

//function to free the pp modification
int freePPDModification(PPDMods mod){
  //validating inputs
  if(!mod){
    printf("\nError in function freePPDModification(): Invalid input parameters.\n");
    return 0;
  }

  if(mod->p_next){
    //free(mod->p_next);
    mod->p_next = NULL;
  }

  if(mod->p_prev){
    //free(mod->p_prev);
    mod->p_prev = NULL;
  }

  free(mod);
  mod = NULL;

  return 1;
}

//function to create a new node for the pp doubly linked list
PPDLNode createNewPPDLNode(int d_data, int d_version){

  //validating inputs
  if(d_version < 1){
    printf("\nError in function createNewPPDLNode(): Invalid input parameters.\n");
    return NULL;
  }

  //allocate memory for a new node
  PPDLNode node = (PPDLNode) malloc(sizeof(struct ppdlNode));
  if(!node){
    printf("\nError in function createNewPPDLNode(): unable to allocate memory for a new node.\n");
    return NULL;
  }

  //populating the node
  node->d_data = d_data;
  node->d_version = d_version;
  node->p_next = NULL;
  node->p_prev = NULL;
  node->p_inverse = NULL;
  node->p_mods = NULL;

  //return the created node
  return node;
}

//function to modify a node to point to a new next node
int modifyNodePPDList(PPDLNode prev, PPDLNode newNext, int nextVersion){

  //validating inputs
  if(!prev || nextVersion < 0){
    printf("\nError in function modifyNodePPDList(): Invalid input parameter.\n");
    return 0;
  }

  //if the modification is empty we add the new modification
  if(!prev->p_mods){

    PPDMods mod = createPPDModification(newNext, prev->p_prev, nextVersion);
    if(!mod){
      printf("\nError in modifyNodePPDList(): Unable to create a new modification.\n");
      return 0;
    }
    prev->p_mods = mod;
    if(newNext){
      newNext->p_inverse = prev;
      newNext->p_prev = prev;
    }

  }
  //if there is already a modification present we need to create a copy node and cascade the changes
  else{

    PPDLNode newNode = createNewPPDLNode(prev->d_data, nextVersion);
    if(!newNode){
      printf("\nError in modifyNodePPDList(): Unable to create a new node.\n");
      return 0;
    }

    newNode->p_next = newNext;
    if(newNext){
      newNext->p_inverse = newNode;
      newNext->p_prev = newNode;
    }
    newNode->p_inverse = prev->p_inverse;
    newNode->p_prev = prev->p_prev;
    if(newNode->p_inverse){
      if(!modifyNodePPDList(newNode->p_inverse, newNode, nextVersion)){
        printf("\nError in modifyNodePPDList(): Unable to modify the required node.\n");
        return 0;
      }
    }

  }

  return 1;
}
