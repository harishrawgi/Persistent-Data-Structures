#ifndef FPBST_H
#define FPBST_H

#define MAX_VERSIONS 100

typedef struct node{
  int data;
  struct mod* mods;
}* Node;

typedef struct mod{
  int version;
  struct node* left;
  struct node* right;
  struct node* inverse;
  struct mod* next;
}* Mod;

typedef struct fpbst{
  struct node* roots[MAX_VERSIONS];
  int liveVersion;
}* FPBST;


// function to create an empty FPBST
FPBST createEmptyFPBST();

// function to insert a value into BST
int insertNodeFPBST(FPBST bst, int data, int version);

// function to search for a key in BST
int searchFPBST(FPBST bst, int key, int version);

// fucntion to print the BST in order
int printInOrderFPBST(FPBST bst, int version);

// function to delete a node in the BST
int deleteFPBST(FPBST bst, int key, int version);

#endif
