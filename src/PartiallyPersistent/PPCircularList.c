#include "PPCircularList.h"

#include <stdio.h>
#include <stdlib.h>

//function to initialize the pp Circular linked list
PPCList init_PPCList(){

  //allocate memory for the new pp Circular linked list
  PPCList list = (PPCList) malloc(sizeof(struct ppCList));
  if(!list){
    printf("\nError in function init_PPCList(): unable to allocate memory for a new list.\n");
    return NULL;
  }

  //initialize the lasts as null for all the versions
  for(int i=0; i<MAX_VERSIONS; i++){
    list->ar_lasts[i] = NULL;
  }

  list->d_liveVersion = 0;

  //return the created list
  return list;
}

//function to insert a new node in the list (at the end)
int insertNodeEndPPCList(PPCList list, int d_data){

  //validating inputs
  if(!list){
    printf("\nError in function insertNodeEndPPCList(): Invalid input parameter.\n");
    return 0;
  }

  //storing the live version and next version for ease of writing
  int liveVersion = list->d_liveVersion;
  int nextVersion = liveVersion + 1;

  if(nextVersion == MAX_VERSIONS){
    printf("\nError in function insertNodeEndPPCList(): Cannot create more versions.\n");
    return 0;
  }

  //creating a new node with given data; the version of the node would be nextVersion
  PPCLNode newNode = createNewPPCLNode(d_data, nextVersion);
  if(!newNode){
    printf("\nError in function insertEndNodePPCList(): Unable to create a new node with data: %d, and version: %d.\n", d_data, nextVersion);
    return 0;
  }

  PPCLNode last = list->ar_lasts[liveVersion];

  //if the list is not empty
  if(liveVersion){

    //get pointer to the head of the live list
    PPCLNode head;
    if(last->p_mods){
      head = last->p_mods->p_next;
    }
    else{
      head = last->p_next;
    }

    //point the new node to the head (to make it Circular)
    newNode->p_next = head;

    //pointing the previous last to this node
    if(!modifyNodePPCList(list, last, newNode, nextVersion)){
      printf("\nError in function insertEndNodePPCList(): Unable to modfiy last node.\n");
      return 0;
    }

    //updating the inverse pointers of head and new node
    head->p_inverse = newNode;
    newNode->p_inverse = last;
  }
  //if the list is empty
  else{
    newNode->p_next = newNode;
    newNode->p_inverse = newNode;
  }

  //pointing the new version last to the node
  list->ar_lasts[nextVersion] = newNode;

  //updating the live version of the list
  list->d_liveVersion = nextVersion;

  return 1;
}

//function to insert a new node in the list (at the beginning)
int insertNodeBeginPPCList(PPCList list, int d_data){

  //validating inputs
  if(!list){
    printf("\nError in function insertNodeBeginPPCList(): Invalid input parameter.\n");
    return 0;
  }

  //storing the live version and next version for ease of writing
  int liveVersion = list->d_liveVersion;
  int nextVersion = liveVersion + 1;

  if(nextVersion == MAX_VERSIONS){
    printf("\nError in function insertNodeBeginPPCList(): Cannot create more versions.\n");
    return 0;
  }

  //creating a new node with given data; the version of the node would be nextVersion
  PPCLNode newNode = createNewPPCLNode(d_data, nextVersion);
  if(!newNode){
    printf("\nError in function insertNodeBeginPPCList(): Unable to create a new node with data: %d, and version: %d.\n", d_data, nextVersion);
    return 0;
  }

  PPCLNode last = list->ar_lasts[liveVersion];

  printf("\nMessage from function insertNodeBeginPPCList(): Adding node (%d) at the beginning of the list.\n",d_data);

  //if the list is not empty
  if(liveVersion){

    //get pointer to the head of the live list
    PPCLNode head;
    if(last->p_mods){
      head = last->p_mods->p_next;
    }
    else{
      head = last->p_next;
    }

    //point the new node to the head (to make it Circular)
    newNode->p_next = head;

    printf("\nMessage from function insertNodeBeginPPCList(): Modifying node (%d) to point to (%d).\n",last->d_data, newNode->d_data);

    //pointing the previous last to this node
    if(!modifyNodePPCList(list, last, newNode, nextVersion)){
      printf("\nError in function insertEndNodePPCList(): Unable to modfiy last node.\n");
      return 0;
    }

    //updating the inverse pointers of head and new node
    head->p_inverse = newNode;
    newNode->p_inverse = last;

    //pointing the new version last to the previous last only
    list->ar_lasts[nextVersion] = last;
  }
  //if the list is empty
  else{
    newNode->p_next = newNode;
    newNode->p_inverse = newNode;

    //pointing the new version last to the new node
    list->ar_lasts[nextVersion] = newNode;
  }

  //updating the live version of the list
  list->d_liveVersion = nextVersion;

  return 1;
}

//function to searching in a particular version of the list
int searchPPCList(PPCList list, int key, int version){

  //validating inputs
  if(!list){
    printf("\nError in function searchPPCList(): Invalid input parameter.\n");
    return 0;
  }

  //make sure someone doesn't ask us to travel to future
  if(version > list->d_liveVersion){
    printf("\nError in function searchPPCList(): The asked version does not exist yet, can't go to future.\n");
    return 0;
  }

  //get the last of the list which corresponds to the input version
  PPCLNode last = list->ar_lasts[version];

  if(!last){
    printf("\nError in function searchPPCList(): The asked version list is empty.\n");
    return 0;
  }

  //curr is used to iterate over the list
  PPCLNode curr = last;

  //itearating over the list till we come back to the last node
  do{

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
        printf("\nMessage from searchPPCList(): Key found!\n");
        return 1;
      }
      else{
        curr = curr->p_next;
      }
    }
    //if we have to use the modification, then the code is as follows
    else{
      if(curr->d_data == key){
        printf("\nMessage from searchPPCList(): Key found!\n");
        return 1;
      }
      else{
        //we use th modified next pointer
        curr = curr->p_mods->p_next;
      }
    }

  }
  while(curr != last);


  //return 0 as we didn't find the key
  return 0;
}

//function to modify a node to point to a new next node
int modifyNodePPCList(PPCList list, PPCLNode prev, PPCLNode newNext, int nextVersion){

  //validating inputs
  if(!list || !prev || nextVersion < 0){
    printf("\nError in function modifyNodePPCList(): Invalid input parameter.\n");
    return 0;
  }

  //if the modification is empty we add the new modification
  if(!prev->p_mods){

    printf("\nMessage from modifyNodePPCList(): The node (%d) has no mods, so adding a new mod!\n", prev->d_data);

    PPCMods mod = createPPCModification(newNext, nextVersion);
    if(!mod){
      printf("\nError in modifyNodePPCList(): Unable to create a new modification.\n");
      return 0;
    }
    prev->p_mods = mod;
    if(newNext){
      newNext->p_inverse = prev;
    }

  }
  //if there is already a modification present we need to create a copy node and cascade the changes
  else{

    printf("\nMessage from modifyNodePPCList(): The node (%d) already has mods, so creating a new node!\n", prev->d_data);


    PPCLNode newNode = createNewPPCLNode(prev->d_data, nextVersion);
    if(!newNode){
      printf("\nError in modifyNodePPCList(): Unable to create a new node.\n");
      return 0;
    }

    prev->p_copy = newNode;

    //update the next last to new node
    if(list->ar_lasts[list->d_liveVersion] == prev){
      printf("\nMessage from modifyNodePPCList(): Making the node (%d) as the new last for (%d) version!\n", prev->d_data, nextVersion);
      list->ar_lasts[nextVersion] = newNode;
    }

    newNode->p_next = newNext;
    if(newNext){
      newNext->p_inverse = newNode;
    }
    newNode->p_inverse = prev->p_inverse;
    if(newNode->p_inverse){
      printf("\nMessage from modifyNodePPCList(): Recursive call to point (%d) to (%d)!\n", newNode->p_inverse->d_data, newNode->d_data);
      if(!modifyNodePPCList(list, newNode->p_inverse, newNode, nextVersion)){
        printf("\nError in modifyNodePPCList(): Unable to modify the required node.\n");
        return 0;
      }
    }

  }

  return 1;
}

//function to delete a node in the list
int deleteNodePPCList(PPCList list, int key){

  //validating inputs
  if(!list){
    printf("\nError in function deleteNodePPCList(): Invalid input parameter.\n");
    return 0;
  }

  int liveVersion = list->d_liveVersion;
  int nextVersion = liveVersion + 1;

  if(nextVersion == MAX_VERSIONS){
    printf("\nError in function deleteNodePPCList(): Cannot create more versions.\n");
    return 0;
  }

  //get the last of the list which corresponds to the input version
  PPCLNode last = list->ar_lasts[liveVersion];

  if(!last){
    printf("\nError in function deleteNodePPCList(): List is empty.\n");
    return 0;
  }

  //curr is used to iterate over the list
  PPCLNode curr = last;

  //prev points to the node previous to the one we need to delete
  PPCLNode prev = curr;

  //curr now is one ahead of prev
  if(curr->p_mods){
    curr = curr->p_mods->p_next;
  }
  else{
    curr = curr->p_next;
  }

  //to decide whether to look at the modification or the data in the fields of node
  int useMod;

  //iterate over the list till it comes back to the last node
  do{

    //initialize to zero for every iteration
    useMod = 0;

    //if there is a modification stored in the node
    if(curr->p_mods){
      useMod = 1;
    }

    //if we are not looking at the mod, then it is a straightforward linked list search
    if(!useMod){

      if(curr->d_data == key){
        printf("\nMessage from deleteNodePPCList(): Key found!\n");
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
        printf("\nMessage from deleteNodePPCList(): Key found!\n");
        break;
      }
      else{
        //we use th modified next pointer
        prev = curr;
        curr = curr->p_mods->p_next;
      }
    }

  }
  while(prev != last);
  //we now have the pointer to the previous node

  //return 0 if the key to be modified is not present in the list
  if(!curr){
    printf("\nError in deleteNodePPCList(): Key to be deleted not in list!\n");
    return 0;
  }

  //the node to be deleted is the last node and it is the only node in the list
  if(prev == curr){

    //update the lasts array to point to NULL
    list->ar_lasts[nextVersion] = NULL;

    //update the liveVersion of the list
    list->d_liveVersion = nextVersion;

    return 1;
  }
  //the node to be deleted is the last node, but it is not the only node in the list
  else if(curr == last){

    PPCLNode newNext;

    printf("\nMessage from deleteNodePPCList(): Deleting node with data (%d) which is the current last node!\n", curr->d_data);

    //get the new next pointer on the basis of whether modification exist in node
    if(useMod){
      newNext = curr->p_mods->p_next;
    }else{
      newNext = curr->p_next;
    }

    printf("\nMessage from deleteNodePPCList(): Modifying so that (%d) now will point to (%d)!\n", prev->d_data, newNext->d_data);

    if(!modifyNodePPCList(list, prev, newNext, nextVersion)){
      printf("\nError in deleteNodePPCList(): Unable to perform the required modification.\n");
      return 0;
    }
    //update the lasts array for the next version
    if(!prev->p_copy){
      list->ar_lasts[nextVersion] = prev;
    }
    else{
      list->ar_lasts[nextVersion] = prev->p_copy;
    }


    //update the liveVersion of the list
    list->d_liveVersion = nextVersion;

  }
  //node to be deleted is not the last node
  else{

    printf("\nMessage from deleteNodePPCList(): Deleting node with data (%d)!\n", curr->d_data);

    PPCLNode newNext;

    //get the new next pointer on the basis of whether modification exist in node
    if(useMod){
      newNext = curr->p_mods->p_next;
    }else{
      newNext = curr->p_next;
    }

    printf("\nMessage from deleteNodePPCList(): Modifying so that (%d) now will point to (%d)!\n", prev->d_data, newNext->d_data);

    if(!modifyNodePPCList(list, prev, newNext, nextVersion)){
      printf("\nError in deleteNodePPCList(): Unable to perform the required modification.\n");
      return 0;
    }
    //update the lasts array for the next version
    if(!list->ar_lasts[nextVersion]){
      list->ar_lasts[nextVersion] = list->ar_lasts[liveVersion];
    }


    //update the liveVersion of the list
    list->d_liveVersion = nextVersion;

  }

  return 1;
}

//function to print the list of a particular version
int printPPCList(PPCList list, int version){

  //validating inputs
  if(!list){
    printf("\nError in function printPPCList(): Invalid input parameter.\n");
    return 0;
  }

  //make sure someone doesn't ask us to travel to future
  if(version > list->d_liveVersion){
    printf("\nError in function printPPCList(): The asked version does not exist yet, can't go to future.\n");
    return 0;
  }

  //get the last of the list which corresponds to the input version
  PPCLNode last = list->ar_lasts[version];

  //curr is used to iterate over the list
  PPCLNode curr = last;

  printf("\nPrinting the Circular linked list with version %d below: \n", version);

  //itearating over the list till we come back to the last node
  do{

    printf("-> %d -> ", curr->d_data);

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
  while(curr != last);

  return 1;
}

//function to free the pp Circular linked list
int freePPCList(PPCList list){

  //validating inputs
  if(!list){
    printf("\nError in function freePPCList(): Invalid input parameter.\n");
    return 0;
  }

  //variable to store different lasts when iterating
  PPCLNode curr, last, next, modNext, copy;

  for(int version = list->d_liveVersion; version >= 1 ; version--){



    //get the last of this version
    curr = list->ar_lasts[version];

    //if curr is not null we will free curr and all nodes associated with it Recursively
    if(curr){

      //there might be multiple versions pointing to the same head
      //we do not want to free same nodes again
      while(curr != list->ar_lasts[version+1] && version < MAX_VERSIONS){
        version++;
      }

      //call the recursive function on curr
      if(!freePPCListHelper(curr)){
        printf("\nError in function freePPCList(): Unable to free node (%d).\n", curr->d_data);
        return 0;
      }

      //make this last as null
      list->ar_lasts[version] = NULL;
    }

  }

  return 1;
}

//helper function to free the node and nodes next to it Recursively
int freePPCListHelper(PPCLNode node){

  //validating input
  if(!node){
    printf("\nError in freePPCListHelper(): Invalid input parameter.\n");
  }

  //pointers to nodes next to node and it's copy if it exitsts
  PPCLNode next, copy;
  next = NULL;
  copy = NULL;
  if(node->p_next && node != node->p_next){
    next = node->p_next;
  }
  if(node->p_copy){
    copy = node->p_copy;
  }

/*
  PPCLNode modNext = NULL;

  if(node->p_mods){
    modNext = node->p_mods->p_next;
    node->p_mods->p_next = NULL;
  }


  //if there is a modification in the node, just free it
  if(node->p_mods){
    freePPCModification(node->p_mods);
  }
*/

  //make sure that the inverse doesn't point to node anymore because we are about to free it
  node->p_inverse->p_next = NULL;

  //free the node finally
  free(node);
  node = NULL;

  //Recursively free the two other nodes
  if(next) freePPCListHelper(next);
  if(copy) freePPCListHelper(copy);

  return 1;
}
