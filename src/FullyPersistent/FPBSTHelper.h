#ifndef FPBSTHELPER_H
#define FPBSTHELPER_H

#include "FPBST.h"

//function to create a node
Node createNode(int data, int version, Node inverse);

//function to create a mod
Mod createMod(int version, Node left, Node right, Node inverse);

// function to search for the mod acc to version needed
Mod searchForMod(Mod head, int version);

// function used as helper in insertnode
int insertNodeFPBSTHelper(Node root, int data, int version, int nextVersion);

// helper function for searchFPBST
int searchFPBSTHelper(Node root, int key, int version);

// helper function for printInOrderFPBST
void printInOrderFPBSTHelper(Node root, int version);

// function to find the minimum node in the tree
Node findMin(Node root, int version);

// function to find the maximum node in the tree
Node findMax(Node root, int version);

// helper function for deleteFPBST
int deleteFPBSTHelper(Node root, int key, int version, int nextVersion);

#endif
