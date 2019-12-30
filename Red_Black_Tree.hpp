#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "Red_Black_Tree_Node.hpp"
#include "Building.hpp"
#include <string>
using namespace std;

class RBTree {
public:

  RBTNode *root;                            // The root node of the Red Black Tree.
  RBTree();                                 // Constructor for the Red Black Tree (Initiates root to NULL initially)

  void leftRotate(RBTNode *node);           // Rotates the given node towards its left side by changing the parent and child pointers respectively.
  void rightRotate(RBTNode *node);			// Rotates the given node towards its right side by changing the parent and child pointers respectively.
  void fixRedRed(RBTNode *node);			// Fixes the Red-Black Tree violation when there is a Red-Red conflict during new insertion into Red-Black Tree.
  void swapColors(RBTNode *node1, RBTNode *node2);	// Swaps the colors of 2 given Red-Black Tree nodes.
  void swapValues(RBTNode *node1, RBTNode *node2);	// Swaps the values of 2 given Red-Black Tree nodes.
  RBTNode* successor(RBTNode *node);				// returns the immediate successor (in inorder traversal) of a given node in Red-Black Tree.
  RBTNode* BSTreplace(RBTNode *node);				// Replace the given node with its immediate successor.
  void deleteNode(RBTNode *node);					// Deletes the given node from the Red-Black Tree.
  void fixDoubleBlack(RBTNode *node);				// fixes the double Black case formed during deletion of given node from the Red-Black Tree.
  void update(RBTNode *root, int buildingNumber, int executionTime);	// updates the execution time of a given Building in a Red Black Tree.
  void searchAndStore(RBTNode *root, int firstBuilding, int lastBuilding, string &rangeValues);  // Searches & stores (In a reference variable) the buildings currently under construction in the given range from firstBuilding <= building <= lastBuilding.
  RBTNode* search(RBTNode *root, int buildingNumber);	// Returns the address of a Red-Black Tree node that has the building number given as input.
  RBTNode* insertBST(RBTNode *root, RBTNode *ptr);		// Insert helper function which inserts given node into Red-Black Tree using normal Binary Search Tree insert procedure.
  RBTNode* insert(Building value);						// Insert the Building plan in to the Red-Black Tree.
  void deleteFromRBTree(int buildingNumber);			// Deletes the given node with building number same as building number which is given as input.
};


#endif // RED_BLACK_TREE_HPP
