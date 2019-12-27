#include "PPSinglyListHelper.h"

#include <stdio.h>
#include <stdlib.h>

//function to create a new pp modification with supplied parameters
//returns pointer to the created modification structure if succesfull, NULL otherwise
PPMods createPPModification(PPSLNode p_next, int d_version){

  //input validating
  //p_next is allowed to be NULL, because we might modify a node to point to NULL
  if(d_version < 0){
    printf("\nError in function createPPModification(): Invalid input parameters.\n");
    return NULL;
  }

  //allocate memory for a new modification
  PPMods mod = (PPMods) malloc(sizeof(struct ppMods));
  if(!mod){
    printf("\nError in function createPPModification(): unable to allocate memory for a new modification.\n");
    return NULL;
  }

  //populating the modification
  mod->d_version = d_version;
  mod->p_next = p_next;

  //return the created modification
  return mod;
}

//function to free the pp modification
int freePPModification(PPMods mod){
  //validating inputs
  if(!mod){
    printf("\nError in function freePPModification(): Invalid input parameters.\n");
    return 0;
  }

  if(mod->p_next){
    //free(mod->p_next);
    mod->p_next = NULL;
  }

  free(mod);
  mod = NULL;

  return 1;
}


//function to create a new node for the pp singly linked list
PPSLNode createNewPPSLNode(int d_data, int d_version){

  //validating inputs
  if(d_version < 1){
    printf("\nError in function createNewPPSLNode(): Invalid input parameters.\n");
    return NULL;
  }

  //allocate memory for a new node
  PPSLNode node = (PPSLNode) malloc(sizeof(struct ppslNode));
  if(!node){
    printf("\nError in function createNewPPSLNode(): unable to allocate memory for a new node.\n");
    return NULL;
  }

  //populating the node
  node->d_data = d_data;
  node->d_version = d_version;
  node->p_next = NULL;
  node->p_inverse = NULL;
  node->p_mods = NULL;

  //return the created node
  return node;
}

//function to modify a node to point to a new next node
int modifyNodePPSList(PPSLNode prev, PPSLNode newNext, int nextVersion){

  //validating inputs
  if(!prev || nextVersion < 0){
    printf("\nError in function modifyNodePPSList(): Invalid input parameter.\n");
    return 0;
  }

  //if the modification is empty we add the new modification
  if(!prev->p_mods){

    PPMods mod = createPPModification(newNext, nextVersion);
    if(!mod){
      printf("\nError in modifyNodePPSList(): Unable to create a new modification.\n");
      return 0;
    }
    prev->p_mods = mod;
    if(newNext){
      newNext->p_inverse = prev;
    }

  }
  //if there is already a modification present we need to create a copy node and cascade the changes
  else{

    PPSLNode newNode = createNewPPSLNode(prev->d_data, nextVersion);
    if(!newNode){
      printf("\nError in modifyNodePPSList(): Unable to create a new node.\n");
      return 0;
    }

    newNode->p_next = newNext;
    if(newNext){
      newNext->p_inverse = newNode;
    }
    newNode->p_inverse = prev->p_inverse;
    if(newNode->p_inverse){
      if(!modifyNodePPSList(newNode->p_inverse, newNode, nextVersion)){
        printf("\nError in modifyNodePPSList(): Unable to modify the required node.\n");
        return 0;
      }
    }

  }

  return 1;
}
