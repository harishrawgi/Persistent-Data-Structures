#include "FPBST.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

  FPBST bst = createEmptyFPBST();
  if(!bst){
    printf("\nError in main(): Unable to create an empty bst.\n");
    exit(0);
  }

  insertNodeFPBST(bst, 5, -1);
  insertNodeFPBST(bst, 3, -1);
  insertNodeFPBST(bst, 6, -1);
  insertNodeFPBST(bst, 2, -1);
  insertNodeFPBST(bst, 4, -1);

  printf("\n Searching 3 in version 3 : (%d)\n", searchFPBST(bst, 3, 3));
  printf("\n Searching 3 in version 1 : (%d)\n", searchFPBST(bst, 3, 1));

  printInOrderFPBST(bst, -1);

  deleteFPBST(bst, 5, -1);
  printf("\n Searching 5 in latest version : (%d)\n", searchFPBST(bst, 5, -1));

  printInOrderFPBST(bst, 6);

  return 0;
}
