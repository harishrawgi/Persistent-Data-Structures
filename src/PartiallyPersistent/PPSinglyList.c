#include "PPSinglyList.h"

#include <stdio.h>
#include <stdlib.h>

//function to initialize the pp singly linked list
PPSList init_PPSList(){

  //allocate memory for the new pp singly linked list
  PPSList list = (PPSList) malloc(sizeof(struct ppSList));
  if(!list){
    printf("\nError in function init_PPSList(): unable to allocate memory for a new list.\n");
    return NULL;
  }

  //initialize the heads as null for all the versions
  for(int i=0; i<MAX_VERSIONS; i++){
    list->ar_heads[i] = NULL;
  }

  list->d_liveVersion = 0;

  //return the created list
  return list;
}

//function to insert a new node in the list (at the beginning)
int insertNodePPSList(PPSList list, int d_data){

  //validating inputs
  if(!list){
    printf("\nError in function insertNodePPSList(): Invalid input parameter.\n");
    return 0;
  }

  //storing the live version and next version for ease of writing
  int liveVersion = list->d_liveVersion;
  int nextVersion = liveVersion + 1;

  if(nextVersion == MAX_VERSIONS){
    printf("\nError in function insertNodePPSList(): Cannot create more versions.\n");
    return 0;
  }

  //creating a new node with given data; the version of the node would be nextVersion
  PPSLNode newNode = createNewPPSLNode(d_data, nextVersion);
  if(!newNode){
    printf("\nError in function insertNodePPSList(): Unable to create a new node with data: %d, and version: %d.\n", d_data, nextVersion);
    return 0;
  }

  //pointing the node to the previously live head
  newNode->p_next = list->ar_heads[liveVersion];

  //storing the inverse pointer from the previous node to new node
  if(liveVersion){
    list->ar_heads[liveVersion]->p_inverse = newNode;
  }

  //pointing the new version head to the node
  list->ar_heads[nextVersion] = newNode;

  //updating the live version of the list
  list->d_liveVersion = nextVersion;

  return 1;
}

//function to searching in a particular version of the list
int searchPPSList(PPSList list, int key, int version){

  //validating inputs
  if(!list){
    printf("\nError in function searchPPSList(): Invalid input parameter.\n");
    return 0;
  }

  //make sure someone doesn't ask us to travel to future
  if(version > list->d_liveVersion){
    printf("\nError in function searchPPSList(): The asked version does not exist yet, can't go to future.\n");
    return 0;
  }

  //get the head of the list which corresponds to the input version
  PPSLNode head = list->ar_heads[version];

  //curr is used to iterate over the list
  PPSLNode curr = head;

  //iterate over the list till either we find the key or curr becomes NULL
  while(curr){

    //to decide whether to look at the modification or the data in the fields of node
    int useMod = 0;

    //if there is a modification stored in the node
    if(curr->p_mods){
      //get the version of the modification
      int modVersion = curr->p_mods->d_version;

      //if the modification was performed in a version which is higher than what we got
      //in this case we ignore this modification
      if(modVersion > version){
        useMod = 0;
      }
      //otherwise we need to look at the modification
      else{
        useMod = 1;
      }
    }

    //if we are not looking at the mod, then it is a straightforward linked list search
    if(!useMod){

      if(curr->d_data == key){
        printf("\nMessage from searchPPSList(): Key found!\n");
        return 1;
      }
      else{
        curr = curr->p_next;
      }
    }
    //if we have to use the modification, then the code is as follows
    else{
      if(curr->d_data == key){
        printf("\nMessage from searchPPSList(): Key found!\n");
        return 1;
      }
      else{
        //we use th modified next pointer
        curr = curr->p_mods->p_next;
      }
    }
  }

  //return 0 as we didn't find the key
  return 0;
}

//function to delete a node in the list
int deleteNodePPSList(PPSList list, int key){

  //validating inputs
  if(!list){
    printf("\nError in function deleteNodePPSList(): Invalid input parameter.\n");
    return 0;
  }

  int liveVersion = list->d_liveVersion;
  int nextVersion = liveVersion + 1;

  if(nextVersion == MAX_VERSIONS){
    printf("\nError in function deleteNodePPSList(): Cannot create more versions.\n");
    return 0;
  }

  //get the head of the list which corresponds to the input version
  PPSLNode head = list->ar_heads[liveVersion];

  //curr is used to iterate over the list
  PPSLNode curr = head;

  //prev points to the node previous to the one we need to delete
  PPSLNode prev = curr;

  //to decide whether to look at the modification or the data in the fields of node
  int useMod;

  //iterate over the list till either we find the key or curr becomes NULL
  while(curr){

    //initialize to zero for every iteration
    useMod = 0;

    //if there is a modification stored in the node
    if(curr->p_mods){
      useMod = 1;
    }

    //if we are not looking at the mod, then it is a straightforward linked list search
    if(!useMod){

      if(curr->d_data == key){
        printf("\nMessage from deleteNodePPSList(): Key found!\n");
        break;
      }
      else{
        prev = curr;
        curr = curr->p_next;
      }
    }
    //if we have to use the modification, then the code is as follows
    else{
      if(curr->d_data == key){
        printf("\nMessage from deleteNodePPSList(): Key found!\n");
        break;
      }
      else{
        //we use th modified next pointer
        prev = curr;
        curr = curr->p_mods->p_next;
      }
    }
  }
  //we now have the pointer to the previous node

  //return 0 if the key to be modified is not present in the list
  if(!curr){
    printf("\nError in deleteNodePPSList(): Key to be deleted not in list!\n");
    return 0;
  }

  //the node to be deleted is the head node
  if(prev == curr){

    PPSLNode newNext;

    //get the new next pointer on the basis of whether modification exist in curr
    if(useMod){
      newNext = curr->p_mods->p_next;
    }else{
      newNext = curr->p_next;
    }

    //update the heads array for the next version
    list->ar_heads[nextVersion] = newNext;

    //update the liveVersion of the list
    list->d_liveVersion = nextVersion;

    if(newNext){
      newNext->p_inverse = NULL;
    }

    return 1;
  }
  //otherwise we perform the delete operation by modifying the prev node to point to the new next
  else{

    PPSLNode newNext;

    //get the new next pointer on the basis of whether modification exist in curr
    if(useMod){
      newNext = curr->p_mods->p_next;
    }else{
      newNext = curr->p_next;
    }

    if(!modifyNodePPSList(prev, newNext, nextVersion)){
      printf("\nError in deleteNodePPSList(): Unable to perform the required modification.\n");
      return 0;
    }
    //update the heads array for the next version
    list->ar_heads[nextVersion] = list->ar_heads[liveVersion];

    //update the liveVersion of the list
    list->d_liveVersion = nextVersion;
  }

  return 1;
}

//function to print the list of a particular version
int printPPSList(PPSList list, int version){

  //validating inputs
  if(!list){
    printf("\nError in function printPPSList(): Invalid input parameter.\n");
    return 0;
  }

  //make sure someone doesn't ask us to travel to future
  if(version > list->d_liveVersion){
    printf("\nError in function printPPSList(): The asked version does not exist yet, can't go to future.\n");
    return 0;
  }

  //get the head of the list which corresponds to the input version
  PPSLNode head = list->ar_heads[version];

  //curr is used to iterate over the list
  PPSLNode curr = head;

  printf("\nPrinting the singly linked list with version %d below: \n", version);

  //iterate over the list till either we find the key or curr becomes NULL
  while(curr){

    printf("%d -> ", curr->d_data);

    //to decide whether to look at the modification or the data in the fields of node
    int useMod = 0;

    //if there is a modification stored in the node
    if(curr->p_mods){
      //get the version of the modification
      int modVersion = curr->p_mods->d_version;

      //if the modification was performed in a version which is higher than what we got
      //in this case we ignore this modification
      if(modVersion > version){
        useMod = 0;
      }
      //otherwise we need to look at the modification
      else{
        useMod = 1;
      }
    }

    //if we are not looking at the mod, then it is a straightforward linked list search
    if(!useMod){
      curr = curr->p_next;
    }
    //if we have to use the modification, then the code is as follows
    else{
      //we use th modified next pointer
      curr = curr->p_mods->p_next;
    }
  }

  return 1;

}

//function to free the pp singly linked list
int freePPSList(PPSList list){

  //validating inputs
  if(!list){
    printf("\nError in function freePPSList(): Invalid input parameter.\n");
    return 0;
  }

  //variable to store different heads when iterating
  PPSLNode node;

  for(int version = 0; version <= list->d_liveVersion; version++){

    //get the head of this version
    node = list->ar_heads[version];

    if(node){

      //there might be multiple versions pointing to the same head
      //we do not want to free same nodes again
      while(node != list->ar_heads[version+1] && version < MAX_VERSIONS){
        version++;
      }

      //if there is a modification in the node, just free it
      if(node->p_mods){
        freePPModification(node->p_mods);
      }

      //free the node finally
      free(node);
      node = NULL;

      //make this head as null
      list->ar_heads[version] = NULL;
    }

  }

  return 1;
}
