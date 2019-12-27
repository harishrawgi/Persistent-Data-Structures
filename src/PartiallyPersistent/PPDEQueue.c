#include "PPDEQueue.h"
#include <stdlib.h>
#include <stdio.h>

//function to initialize an empty Queue
PPDEQueue init_PPDEQueue(){

  //allocate memory for the new pp queue
  PPDEQueue queue = (PPDEQueue) malloc(sizeof(struct ppDeQueue));
  if(!queue){
    printf("\nError in function init_PPDEQueue(): unable to allocate memory for a new queue.\n");
    return NULL;
  }

  //initialize the circular list for the queue
  queue->list = init_PPCList();
  if(!queue->list){
    printf("\nError in function init_PPDEQueue(): unable to create an empty list for a new queue.\n");
    return NULL;
  }

  return queue;
}

//function to insert an element on the end of Queue
int insertRearPPDEQueue(PPDEQueue queue, int key){

  //validating inputs
  if(!queue){
    printf("\nError in function insertRearPPDEQueue(): Invalid input parameter.\n");
    return 0;
  }

  //add the key to the rear of the list
  if(!insertNodeEndPPCList(queue->list, key)){
    printf("\nError in function insertRearPPDEQueue(): Unable to insert the element on to the queue.\n");
    return 0;
  }

  return 1;
}

//function to insert an element on the front of Queue
int insertFrontPPDEQueue(PPDEQueue queue, int key){

  //validating inputs
  if(!queue){
    printf("\nError in function insertFrontPPDEQueue(): Invalid input parameter.\n");
    return 0;
  }

  //add the key to the front of the list
  if(!insertNodeBeginPPCList(queue->list, key)){
    printf("\nError in function insertFrontPPDEQueue(): Unable to insert the element on to the queue.\n");
    return 0;
  }

  return 1;
}

//function to check if a specified version of the Queue is empty
int isEmptyPPDEQueue(PPDEQueue queue, int version, int *result){

  //validating inputs
  if(!queue || version < 1){
    printf("\nError in function isEmptyPPDEQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function isEmptyPPDEQueue(): Empty queue.\n");
    return 0;
  }

  //check if someone is asking for future
  if(queue->list->d_liveVersion < version){
    printf("\nError in function isEmptyPPDEQueue(): Can't travel to future.\n");
    return 0;
  }

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[version]){
    *result = 1;
  }
  else{
    *result = 0;
  }

  return 1;
}

//function which returns the element at the front of the Queue of specified version
int frontPPDEQueue(PPDEQueue queue, int version, int* result){

  //validating inputs
  if(!queue || version < 1){
    printf("\nError in function frontPPDEQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function frontPPDEQueue(): Empty queue.\n");
    return 0;
  }

  //check if someone is asking for future
  if(queue->list->d_liveVersion < version){
    printf("\nError in function frontPPDEQueue(): Can't travel to future.\n");
    return 0;
  }

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[version]){
    printf("\nError in function frontPPDEQueue(): Empty queue in the version (%d).\n", version);
    return 0;
  }
  //if not, then we return the first element in the list of the specified version
  else{

    //get the last node of the specified version
    struct ppclNode* last = queue->list->ar_lasts[version];

    //if this is the only node, we return it's data
    if(last->p_next == last){
      *result = last->d_data;
      return 1;
    }
    //if there are more than one nodes, we get the next of the last in this version
    //this would be the first node in the list, we return it's data
    else{

      //to decide whether to look at the modification or the data in the fields of node
      int useMod = 0;

      //if there is a modification stored in the node
      if(last->p_mods){

        //get the version of the modification
        int modVersion = last->p_mods->d_version;

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

      //get the data of next node using the mod
      if(useMod){
        *result = last->p_mods->p_next->d_data;
        return 1;
      }
      //get the data of the next node ignoring the mod
      else{
        *result = last->p_next->d_data;
        return 1;
      }

    }
  }

  //something went wrong if it came here
  return 0;
}

//function which returns the element at the front of the Queue of specified version
int rearPPDEQueue(PPDEQueue queue, int version, int* result){

  //validating inputs
  if(!queue || version < 1){
    printf("\nError in function rearPPDEQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function rearPPDEQueue(): Empty queue.\n");
    return 0;
  }

  //check if someone is asking for future
  if(queue->list->d_liveVersion < version){
    printf("\nError in function rearPPDEQueue(): Can't travel to future.\n");
    return 0;
  }

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[version]){
    printf("\nError in function rearPPDEQueue(): Empty queue in the version (%d).\n", version);
    return 0;
  }
  //if not, then we return the last element in the list of the specified version
  else{

    //get the last node of the specified version
    struct ppclNode* last = queue->list->ar_lasts[version];

    //get the data of the last element
    *result = last->d_data;
    return 1;

  }

  //something went wrong if it came here
  return 0;
}

//function to delete the rear element of the Queue
int deleteRearPPDEQueue(PPDEQueue queue){

  //validating inputs
  if(!queue){
    printf("\nError in function deleteRearPPDEQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function deleteRearPPDEQueue(): Empty queue.\n");
    return 0;
  }

  int liveVersion = queue->list->d_liveVersion;

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[liveVersion]){
    printf("\nError in function deleteRearPPDEQueue(): Empty queue in the live version (%d).\n", liveVersion);
    return 0;
  }
  //if not, then we delete the last element in the queue
  else{

    //get the last node of the specified version
    struct ppclNode* last = queue->list->ar_lasts[liveVersion];

    int rear_key = last->d_data;

    //perform deletion
    if(!deleteNodePPCList(queue->list, rear_key)){
      printf("\nError in function deleteRearPPDEQueue(): Unable to dequeu (%d) from queue in the live version (%d).\n", rear_key, liveVersion);
      return 0;
    }

  }

  return 1;
}

//function to delete the front element of the Queue
int deleteFrontPPDEQueue(PPDEQueue queue){

  //validating inputs
  if(!queue){
    printf("\nError in function deleteFrontPPDEQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function deleteFrontPPDEQueue(): Empty queue.\n");
    return 0;
  }

  int liveVersion = queue->list->d_liveVersion;

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[liveVersion]){
    printf("\nError in function deleteFrontPPDEQueue(): Empty queue in the live version (%d).\n", liveVersion);
    return 0;
  }
  //if not, then we delete the first element in the queue
  else{

    //get the last node of the specified version
    struct ppclNode* last = queue->list->ar_lasts[liveVersion];

    int front_key;

    //if this is the only node, we return it's data
    if(last->p_next == last){
      front_key = last->d_data;
    }
    //if there are more than one nodes, we get the next of the last in this version
    //this would be the first node in the list, we delete it's data
    else{

      //get the data of next node using the mod
      if(last->p_mods){
        front_key = last->p_mods->p_next->d_data;
      }
      //get the data of the next node ignoring the mod
      else{
        front_key = last->p_next->d_data;
      }
    }

    //perform deletion
    if(!deleteNodePPCList(queue->list, front_key)){
      printf("\nError in function deleteFrontPPDEQueue(): Unable to dequeu (%d) from queue in the live version (%d).\n", front_key, liveVersion);
      return 0;
    }

  }

  return 1;
}

//function to print Queue of a specified version
int printPPDEQueue(PPDEQueue queue, int version){

  //validating inputs
  if(!queue){
    printf("\nError in function printPPDEQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function printPPDEQueue(): Empty queue.\n");
    return 0;
  }

  int liveVersion = queue->list->d_liveVersion;

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[liveVersion]){
    printf("\nError in function printPPDEQueue(): Empty queue in the live version (%d).\n", liveVersion);
    return 0;
  }
  //print this version of queue if not empty
  else{
    if(!printPPCList(queue->list, version)){
      printf("\nError in function printPPDEQueue(): Unable to print the list.\n");
      return 0;
    }
  }

  return 1;
}

//function to free the Queue
int freePPDEQueue(PPDEQueue queue){

  //validating inputs
  if(!queue){
    printf("\nError in function freePPDEQueue(): Invalid input parameter.\n");
    return 0;
  }

  //free the list if it is not NULL
  if(queue->list){
    if(!freePPCList(queue->list)){
      printf("\nError in function freePPDEQueue(): Unable to free the list.\n");
      return 0;
    }
  }

  //free the queue
  free(queue);
  queue = NULL;

  return 1;
}
