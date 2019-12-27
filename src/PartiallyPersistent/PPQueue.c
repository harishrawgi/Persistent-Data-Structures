#include "PPQueue.h"
#include <stdlib.h>
#include <stdio.h>

//function to initialize an empty Queue
PPQueue init_PPQueue(){

  //allocate memory for the new pp queue
  PPQueue queue = (PPQueue) malloc(sizeof(struct ppQueue));
  if(!queue){
    printf("\nError in function init_PPQueue(): unable to allocate memory for a new queue.\n");
    return NULL;
  }

  queue->list = init_PPCList();
  if(!queue->list){
    printf("\nError in function init_PPQueue(): unable to create an empty list for a new queue.\n");
    return NULL;
  }

  return queue;
}

//function to insert an element on to the Queue
int enqueuePPQueue(PPQueue queue, int key){

  //validating inputs
  if(!queue){
    printf("\nError in function enqueuePPQueue(): Invalid input parameter.\n");
    return 0;
  }

  //add the key to the rear of the list
  if(!insertNodeEndPPCList(queue->list, key)){
    printf("\nError in function enqueuePPQueue(): Unable to enqueue the element on to the queue.\n");
    return 0;
  }

  return 1;
}

//function to check if a specified version of the Queue is empty
int isEmptyPPQueue(PPQueue queue, int version, int *result){

  //validating inputs
  if(!queue || version < 1){
    printf("\nError in function isEmptyPPQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function isEmptyPPQueue(): Empty queue.\n");
    return 0;
  }

  //check if someone is asking for future
  if(queue->list->d_liveVersion < version){
    printf("\nError in function isEmptyPPQueue(): Can't travel to future.\n");
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
int frontPPQueue(PPQueue queue, int version, int* result){

  //validating inputs
  if(!queue || version < 1){
    printf("\nError in function frontPPQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function frontPPQueue(): Empty queue.\n");
    return 0;
  }

  //check if someone is asking for future
  if(queue->list->d_liveVersion < version){
    printf("\nError in function frontPPQueue(): Can't travel to future.\n");
    return 0;
  }

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[version]){
    printf("\nError in function frontPPQueue(): Empty queue in the version (%d).\n", version);
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
int rearPPQueue(PPQueue queue, int version, int* result){

  //validating inputs
  if(!queue || version < 1){
    printf("\nError in function rearPPQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function rearPPQueue(): Empty queue.\n");
    return 0;
  }

  //check if someone is asking for future
  if(queue->list->d_liveVersion < version){
    printf("\nError in function rearPPQueue(): Can't travel to future.\n");
    return 0;
  }

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[version]){
    printf("\nError in function rearPPQueue(): Empty queue in the version (%d).\n", version);
    return 0;
  }
  //if not, then we return the last element in the list of the specified version
  else{

    //get the last node of the specified version
    struct ppclNode* last = queue->list->ar_lasts[version];

    //get the data from this node
    *result = last->d_data;
    return 1;
  }

  //something went wrong if it came here
  return 0;

}

//function to dequeu the top element of the Queue
int dequeuePPQueue(PPQueue queue){

  //validating inputs
  if(!queue){
    printf("\nError in function dequeuePPQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function dequeuePPQueue(): Empty queue.\n");
    return 0;
  }

  int liveVersion = queue->list->d_liveVersion;

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[liveVersion]){
    printf("\nError in function dequeuePPQueue(): Empty queue in the live version (%d).\n", liveVersion);
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
      printf("\nError in function dequeuePPQueue(): Unable to dequeu (%d) from queue in the live version (%d).\n", front_key, liveVersion);
      return 0;
    }

  }

  return 1;
}

//function to print Queue of a specified version
int printPPQueue(PPQueue queue, int version){

  //validating inputs
  if(!queue){
    printf("\nError in function printPPQueue(): Invalid input parameter.\n");
    return 0;
  }
  if(!queue->list){
    printf("\nError in function printPPQueue(): Empty queue.\n");
    return 0;
  }

  int liveVersion = queue->list->d_liveVersion;

  //check if the queue of the supplied version is empty
  if(!queue->list->ar_lasts[liveVersion]){
    printf("\nError in function printPPQueue(): Empty queue in the live version (%d).\n", liveVersion);
    return 0;
  }
  //print this version of queue if not empty
  else{
    if(!printPPCList(queue->list, version)){
      printf("\nError in function printPPQueue(): Unable to print the list.\n");
      return 0;
    }
  }

  return 1;
}

//function to free the Queue
int freePPQueue(PPQueue queue){

  //validating inputs
  if(!queue){
    printf("\nError in function freePPQueue(): Invalid input parameter.\n");
    return 0;
  }

  //free the list if it is not NULL
  if(queue->list){
    if(!freePPCList(queue->list)){
      printf("\nError in function freePPQueue(): Unable to free the list.\n");
      return 0;
    }
  }

  //free the queue
  free(queue);
  queue = NULL;

  return 1;
}
