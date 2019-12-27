#include "FPBST.h"
#include "FPBSTHelper.h"
#include "stdio.h"
#include "stdlib.h"

// function to create an empty FPBST
FPBST createEmptyFPBST(){

  FPBST bst = (FPBST) malloc(sizeof(struct fpbst));
  if(!bst){
    printf("\nError in createEmptyFPBST(): Unable to allocate memory.\n");
    return NULL;
  }

  for(int i=0; i<MAX_VERSIONS; i++){
    bst->roots[i] = NULL;
  }

  bst->liveVersion = 0;

  return bst;
}

// function to insert a value into BST
int insertNodeFPBST(FPBST bst, int data, int version){

  if(version != -1){
    printf("\nError in insertNodeFPBST(): Program is not ready to handle fully persistence. Please enter version as -1.\n");
    return 0;
  }

  if(!bst || version >= MAX_VERSIONS){
    printf("\nError in insertNodeFPBST(): Invalid input.\n");
    return 0;
  }

  int liveVersion = bst->liveVersion;
  int nextVersion = liveVersion + 1;


  if(version == -1){
    version = liveVersion;
  }

  if(version > liveVersion){
    printf("\nError in insertNodeFPBST(): Version doesn't exist.\n");
    return 0;
  }

  Node root = bst->roots[version];

  if(!root){
    root = createNode(data, nextVersion, NULL);
    bst->roots[nextVersion] = root;
    bst->liveVersion = nextVersion;
    //printf("\nMessage from insertNodeFPBST(): The version (%d) has no nodes, so inserting (%d) as root.\n", version, data);
    return 1;
  }

  if(!insertNodeFPBSTHelper(root, data, version, nextVersion)){
    printf("\nError in insertNodeFPBST(): insertNodeHelper failed.\n");
    return 0;
  }

  bst->roots[nextVersion] = root;
  bst->liveVersion = nextVersion;
  return 1;
}

// function to search for a key in BST
int searchFPBST(FPBST bst, int key, int version){

  if(!bst || version >= MAX_VERSIONS){
    printf("\nError in searchFPBST(): Invalid input.\n");
    return 0;
  }

  int liveVersion = bst->liveVersion;

  if(version == -1){
    version = liveVersion;
  }

  if(version > liveVersion){
    printf("\nError in searchFPBST(): Version doesn't exist.\n");
    return 0;
  }

  Node root = bst->roots[version];

  printf("\nMessage from searchFPBST(): Found root (%d) of the tree with version (%d)\n", root->data, version);

  if(!searchFPBSTHelper(root, key, version)){
    printf("\nMessage from searchFPBST(): Key not found.\n");
    return 0;
  }

  return 1;

}

// fucntion to print the BST in order
int printInOrderFPBST(FPBST bst, int version){

  if(!bst || version >= MAX_VERSIONS){
    printf("\nError in printInOrderFPBST(): Invalid input.\n");
    return 0;
  }

  int liveVersion = bst->liveVersion;

  if(version == -1){
    version = liveVersion;
  }

  if(version > liveVersion){
    printf("\nError in printInOrderFPBST(): Version doesn't exist.\n");
    return 0;
  }

  Node root = bst->roots[version];

  printInOrderFPBSTHelper(root, version);

  return 1;

}

// function to delete a node in the BST
int deleteFPBST(FPBST bst, int key, int version){

  if(version != -1){
    printf("\nError in deleteFPBST(): Program is not ready to handle fully persistence. Please enter version as -1.\n");
    return 0;
  }

  if(!bst || version >= MAX_VERSIONS){
    printf("\nError in printInOrderFPBST(): Invalid input.\n");
    return 0;
  }

  int liveVersion = bst->liveVersion;
  int nextVersion = liveVersion + 1;

  if(version == -1){
    version = liveVersion;
  }

  if(version > liveVersion){
    printf("\nError in printInOrderFPBST(): Version doesn't exist.\n");
    return 0;
  }

  Node root = bst->roots[version];

  Mod mod = searchForMod(root->mods, version);
  if(!mod){
    printf("\nError in deleteFPBST(): Unable to find a mod.\n");
    return 0;
  }

  if(root->data == key){

    printf("\nMessage from deleteFPBST(): Root (%d) of version (%d) has to be deleted.\n", root->data, version);

    if(mod->left && mod->right){

      Node pred = findMax(mod->left, version);

      printf("\nMessage from deleteFPBST(): Found predecessor (%d).\n", pred->data);

      Mod predMod = createMod(nextVersion, mod->left, mod->right, NULL);
      printf("\nMessage from deleteFPBST(): Added mod to predecessor with version (%d).\n", predMod->version);
      predMod->next = pred->mods;
      pred->mods = predMod;


      Mod modOfPred = searchForMod(pred->mods, version);
      Node pred_inv = modOfPred->inverse;
      printf("\nMessage from deleteFPBST(): Found inverse of predecessor as (%d).\n", pred_inv->data);
      Mod modOfPredInv = searchForMod(pred_inv->mods, version);
      printf("\nMessage from deleteFPBST(): Found mod of inverse of predecessor with version (%d).\n", modOfPredInv->version);

      Mod inversePredMod = NULL;
      inversePredMod = createMod(nextVersion, modOfPredInv->left, NULL, modOfPredInv->inverse);
      inversePredMod->next = modOfPred->inverse->mods;
      modOfPred->inverse->mods = inversePredMod;

      Mod modOfLeft = searchForMod(mod->left->mods, version);
      Mod leftMod = NULL;
      if(modOfLeft->right == pred){
        leftMod = createMod(nextVersion, modOfLeft->left, NULL, pred);
      }
      else{
        leftMod = createMod(nextVersion, modOfLeft->left, modOfLeft->right, pred);
      }
      leftMod->next = mod->left->mods;
      mod->left->mods = leftMod;

      Mod modOfRight = searchForMod(mod->right->mods, version);
      Mod rightMod = NULL;
      rightMod = createMod(nextVersion, modOfRight->left, modOfRight->right, pred);
      rightMod->next = mod->right->mods;
      mod->right->mods = rightMod;

      bst->roots[nextVersion] = pred;
      bst->liveVersion = nextVersion;
      return 1;
    }
    else{

      if(!mod->left){

        Mod modOfRight = searchForMod(mod->right->mods, version);
        Mod rightMod = NULL;
        rightMod = createMod(nextVersion, modOfRight->left, modOfRight->right, NULL);
        rightMod->next = mod->right->mods;
        mod->right->mods = rightMod;

        bst->roots[nextVersion] = mod->right;
        bst->liveVersion = nextVersion;
        return 1;
      }
      else{

        Mod modOfLeft = searchForMod(mod->left->mods, version);
        Mod leftMod = NULL;
        leftMod = createMod(nextVersion, modOfLeft->left, modOfLeft->right, NULL);
        leftMod->next = mod->left->mods;
        mod->left->mods = leftMod;

        bst->roots[nextVersion] = mod->left;
        bst->liveVersion = nextVersion;
        return 1;
      }
    }
  }
  else if(key < root->data){
    if(!deleteFPBSTHelper(mod->left, key, version, nextVersion)){
      printf("\nError in deleteFPBST(): Helper method failed.\n");
      return 0;
    }
    bst->roots[nextVersion] = root;
    bst->liveVersion = nextVersion;
    return 1;
  }
  else{
    if(!deleteFPBSTHelper(mod->right, key, version, nextVersion)){
      printf("\nError in deleteFPBST(): Helper method failed.\n");
      return 0;
    }
    bst->roots[nextVersion] = root;
    bst->liveVersion = nextVersion;
    return 1;
  }


}
