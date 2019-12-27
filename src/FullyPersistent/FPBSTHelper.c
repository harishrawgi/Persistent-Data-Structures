#include "FPBSTHelper.h"
#include <stdio.h>
#include <stdlib.h>

//function to create a node
Node createNode(int data, int version, Node inverse){

  Node node = (Node) malloc(sizeof(struct node));
  if(!node){
    printf("\nError in createNode(): Unable to allocate memory.\n");
    return NULL;
  }

  node->data = data;

  Mod mod = createMod(version, NULL, NULL, inverse);
  node->mods = mod;

  return node;
}

//function to create a mod
Mod createMod(int version, Node left, Node right, Node inverse){

  Mod mod = (Mod) malloc(sizeof(struct mod));
  if(!mod){
    printf("\nError in createMod(): Unable to allocate memory.\n");
    return NULL;
  }

  mod->version = version;
  mod->left = left;
  mod->right = right;
  mod->inverse = inverse;
  mod->next = NULL;

  return mod;
}

// function to search for the mod acc to version needed
Mod searchForMod(Mod head, int version){

  if(!head) return head;

  Mod curr = head;

  //printf("\nSearching for version (%d)\n", version);

  while(curr && curr->version > version){
    printf("\nCurrent version is (%d)\n", curr->version);
    curr = curr->next;
  }

  //printf("\nReturing version (%d)\n", curr->version);
  return curr;

}

// function used as helper in insertnode
int insertNodeFPBSTHelper(Node root, int data, int version, int nextVersion){

  Mod mod = searchForMod(root->mods, version);
  if(!mod){
    printf("\nUnable to find a valid mod for node (%d) for version (%d)\n", root->data, version);
    return 0;
  }

  //printf("\nMessage from insertNodeFPBSTHelper(): Inserting (%d) into tree with root (%d).\n", data, root->data);

  if(data < root->data){

    if(!mod->left){
      //printf("\nMessage from insertNodeFPBSTHelper(): The node (%d) has no nodes on the left, Inserting (%d) there.\n", root->data, data);
      Node newNode = createNode(data, nextVersion, root);
      //printf("\nMessage from insertNodeFPBSTHelper(): Created new node with (%d) data and version as (%d), Inverse is (%d).\n", data, nextVersion, root->data);
      Mod newMod = createMod(nextVersion, newNode, mod->right, mod->inverse);
      //printf("\nMessage from insertNodeFPBSTHelper(): Adding new mod to (%d) with version as (%d), and left child as (%d).\n", root->data, nextVersion, data);
      newMod->next = root->mods;
      root->mods = newMod;
    }
    else{
      if(!insertNodeFPBSTHelper(mod->left, data, version, nextVersion)){
        printf("\nError in insertNodeHelper(): Unable to insert node.\n");
        return 0;
      }
    }

  }
  if(data > root->data){

    if(!mod->right){
      //printf("\nMessage from insertNodeFPBSTHelper(): The node (%d) has no nodes on the right, Inserting (%d) there.\n", root->data, data);
      Node newNode = createNode(data, nextVersion, root);
      //printf("\nMessage from insertNodeFPBSTHelper(): Created new node with (%d) data and version as (%d), Inverse is (%d).\n", data, nextVersion, root->data);
      Mod newMod = createMod(nextVersion, mod->left, newNode, mod->inverse);
      //printf("\nMessage from insertNodeFPBSTHelper(): Adding new mod to (%d) with version as (%d), and right child as (%d).\n", root->data, nextVersion, data);
      newMod->next = root->mods;
      root->mods = newMod;
    }
    else{
      if(!insertNodeFPBSTHelper(mod->right, data, version, nextVersion)){
        printf("\nError in insertNodeHelper(): Unable to insert node.\n");
        return 0;
      }
    }

  }

  return 1;
}


// helper function for searchFPBST
int searchFPBSTHelper(Node root, int key, int version){

  if(!root){
    printf("\nMessage from searchFPBSTHelper(): BST is empty.\n");
    return 0;
  }

  Mod mod = searchForMod(root->mods, version);


  if(key < root->data){
    printf("\nMessage from searchFPBSTHelper(): Key (%d) is less than node's data (%d).\n", key, root->data);
    return searchFPBSTHelper(mod->left, key, version);
  }
  else if(key > root->data){
    printf("\nMessage from searchFPBSTHelper(): Key (%d) is greater than node's data (%d).\n", key, root->data);
    return searchFPBSTHelper(mod->right, key, version);
  }
  else{
    return 1;
  }

}

// helper function for printInOrderFPBST
void printInOrderFPBSTHelper(Node root, int version){

  if(!root){
    return;
  }

  Mod mod = searchForMod(root->mods, version);
  if(!mod){
    printf("\nError in printInOrderFPBST(): Unable to find a mod.\n");
    return;
  }

  printInOrderFPBSTHelper(mod->left, version);
  printf("%d ", root->data);
  printInOrderFPBSTHelper(mod->right, version);


}

// function to find the minimum node in the tree
Node findMin(Node root, int version){

  if(!root){
    return NULL;
  }

  Mod mod = searchForMod(root->mods, version);

  if(!mod->left){
    return root;
  }
  else{
    return findMin(mod->left, version);
  }

}

// function to find the maximum node in the tree
Node findMax(Node root, int version){

  if(!root){
    return NULL;
  }

  Mod mod = searchForMod(root->mods, version);

  if(!mod->right){
    return root;
  }
  else{
    return findMin(mod->right, version);
  }

}

// helper function for deleteFPBST
int deleteFPBSTHelper(Node root, int key, int version, int nextVersion){

  Mod mod = searchForMod(root->mods, version);

  if(root->data == key){

    if(mod->left && mod->right){

      Node pred = findMax(mod->left, version);

      Mod predMod = createMod(nextVersion, mod->left, mod->right, mod->inverse);
      predMod->next = pred->mods;
      pred->mods = predMod;

      Mod modOfPred = searchForMod(pred->mods, version);
      Node pred_inv = modOfPred->inverse;
      Mod modOfPredInv = searchForMod(pred_inv->mods, version);
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


      Node root_inv = mod->inverse;
      Mod modOfInv = searchForMod(root_inv->mods, version);
      if(modOfInv->left == root){
        Mod invRootMod = createMod(nextVersion, pred, modOfInv->right, modOfInv->inverse);
        invRootMod->next = root_inv->mods;
        root_inv->mods = invRootMod;
      }
      else if(modOfInv->right == root){
        Mod invRootMod = createMod(nextVersion, modOfInv->left, pred, modOfInv->inverse);
        invRootMod->next = root_inv->mods;
        root_inv->mods = invRootMod;
      }

    }
    else{

      if(!mod->left){

        Mod modOfRight = searchForMod(mod->right->mods, version);
        Mod rightMod = NULL;
        rightMod = createMod(nextVersion, modOfRight->left, modOfRight->right, mod->inverse);
        rightMod->next = mod->right->mods;
        mod->right->mods = rightMod;

        Node root_inv = mod->inverse;
        Mod modOfInv = searchForMod(root_inv->mods, version);
        if(modOfInv->left == root){
          Mod invRootMod = createMod(nextVersion, mod->right, modOfInv->right, modOfInv->inverse);
          invRootMod->next = root_inv->mods;
          root_inv->mods = invRootMod;
        }
        else if(modOfInv->right == root){
          Mod invRootMod = createMod(nextVersion, modOfInv->left, mod->right, modOfInv->inverse);
          invRootMod->next = root_inv->mods;
          root_inv->mods = invRootMod;
        }
      }
      else{

        Mod modOfLeft = searchForMod(mod->left->mods, version);
        Mod leftMod = NULL;
        leftMod = createMod(nextVersion, modOfLeft->left, modOfLeft->right, mod->inverse);
        leftMod->next = mod->left->mods;
        mod->left->mods = leftMod;

        Node root_inv = mod->inverse;
        Mod modOfInv = searchForMod(root_inv->mods, version);
        if(modOfInv->left == root){
          Mod invRootMod = createMod(nextVersion, mod->left, modOfInv->right, modOfInv->inverse);
          invRootMod->next = root_inv->mods;
          root_inv->mods = invRootMod;
        }
        else if(modOfInv->right == root){
          Mod invRootMod = createMod(nextVersion, modOfInv->left, mod->left, modOfInv->inverse);
          invRootMod->next = root_inv->mods;
          root_inv->mods = invRootMod;
        }

      }
    }
  }
  else if(key < root->data){
    if(!deleteFPBSTHelper(mod->left, key, version, nextVersion)){
      printf("\nError in deleteFPBST(): Helper method failed.\n");
      return 0;
    }
    return 1;
  }
  else{
    if(!deleteFPBSTHelper(mod->right, key, version, nextVersion)){
      printf("\nError in deleteFPBST(): Helper method failed.\n");
      return 0;
    }
    return 1;
  }

}
