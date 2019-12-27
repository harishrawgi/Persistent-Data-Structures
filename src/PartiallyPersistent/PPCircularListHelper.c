#include "PPCircularListHelper.h"

#include <stdio.h>
#include <stdlib.h>

//function to create a new pp modification with supplied parameters
//returns pointer to the created modification structure if succesfull, NULL otherwise
PPCMods createPPCModification(PPCLNode p_next, int d_version){

  //input validating
  //p_next is allowed to be NULL, because we might modify a node to point to NULL
  if(d_version < 0){
    printf("\nError in function createPPCModification(): Invalid input parameters.\n");
    return NULL;
  }

  //allocate memory for a new modification
  PPCMods mod = (PPCMods) malloc(sizeof(struct ppcMods));
  if(!mod){
    printf("\nError in function createPPCModification(): unable to allocate memory for a new modification.\n");
    return NULL;
  }

  //populating the modification
  mod->d_version = d_version;
  mod->p_next = p_next;

  //return the created modification
  return mod;
}

//function to free the pp modification
int freePPCModification(PPCMods mod){
  //validating inputs
  if(!mod){
    printf("\nError in function freePPCModification(): Invalid input parameters.\n");
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

//function to create a new node for the pp Circular linked list
PPCLNode createNewPPCLNode(int d_data, int d_version){

  //validating inputs
  if(d_version < 1){
    printf("\nError in function createNewPPCLNode(): Invalid input parameters.\n");
    return NULL;
  }

  //allocate memory for a new node
  PPCLNode node = (PPCLNode) malloc(sizeof(struct ppclNode));
  if(!node){
    printf("\nError in function createNewPPCLNode(): unable to allocate memory for a new node.\n");
    return NULL;
  }

  //populating the node
  node->d_data = d_data;
  node->d_version = d_version;
  node->p_next = NULL;
  node->p_inverse = NULL;
  node->p_copy = NULL;
  node->p_mods = NULL;

  //return the created node
  return node;
}
