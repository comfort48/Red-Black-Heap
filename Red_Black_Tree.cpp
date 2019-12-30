#ifndef RED_BLACK_TREE_CPP
#define RED_BLACK_TREE_CPP
#include "Red_Black_Tree.hpp"
#include "Building.hpp"
#include <sstream>
using namespace std;

RBTree::RBTree() {
    root = NULL;
}

void RBTree::leftRotate(RBTNode *node) {
    
    RBTNode *newParent = node->rightChild;  // node's right child is the new Parent after left rotation.

    
    if (node == root)    // updates the root if given node is the root before left rotation.
      root = newParent;

    node->moveDown(newParent);

    
    node->rightChild = newParent->leftChild;      // change given nodes right child after left rotation to new parent's left child.
    
    if (newParent->leftChild != NULL)             // Connect the new parent's left child's parent to the given node as given node becomes the parent of new parent's left child after rotation.
      newParent->leftChild->parent = node;

    newParent->leftChild = node;                  // Connect new parent's left child to given node after rotation.
  }

  void RBTree::rightRotate(RBTNode *node) {

    RBTNode *newParent = node->leftChild;        // node's left child becomes the new parent after rotation.

    if (node == root)							 // If node the root, then update root to new parent.
      root = newParent;

    node->moveDown(newParent);

    node->leftChild = newParent->rightChild;     // given node's left child is the new parent's right child.

    if (newParent->rightChild != NULL)           // change new parent's right child's parent to the given node after rotation.
      newParent->rightChild->parent = node;

    newParent->rightChild = node;				 // change new parent's right child to given node. 
  }

  void RBTree::swapColors(RBTNode *node1, RBTNode *node2) {
    COLOR temp;
    temp = node1->color;
    node1->color = node2->color;
    node2->color = temp;
  }

  void RBTree::swapValues(RBTNode *node1, RBTNode *node2) {
    Building temp;
    temp = node1->value;
    node1->value = node2->value;
    node2->value = temp;
  }

  void RBTree::fixRedRed(RBTNode *node) {                    // Fix the Red-Red violation at node.
   
    if (node == root) {										 // If given node is root then, just change the color of the given node from red to black and return.
      node->color = BLACK;
      return;
    }

    RBTNode *parent = node->parent, *grandparent = parent->parent, *uncle = node->getUncleNode();         // define the parent, grandparent and uncle of a given node.

    if (parent->color != BLACK) {																		
      if (uncle != NULL && uncle->color == RED) {              // If uncle is red, recolor the parent color to black, uncle color to black, grandparent color to red.
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixRedRed(grandparent);					              // Recur on the grandparent to fix the red-red violation.
      }
      else {                                                  // If uncle is NULL or uncle's color is not red perform - {check for Left-Right, Left-Left, Right-Right, Right-Left rotations}.
        if (parent->isOnLeftSide()) {							
          if (node->isOnLeftSide()) {
            swapColors(parent, grandparent);				 // Left-Right case only.
          }
          else {
            leftRotate(parent);
            swapColors(node, grandparent);					 // Left-Left and Left-Right case.
          }
          rightRotate(grandparent);
        }
        else {
          if (node->isOnLeftSide()) {						// Right-Left case only.
            rightRotate(parent);
            swapColors(node, grandparent);
          }
          else {
            swapColors(parent, grandparent);
          }
          leftRotate(grandparent);							// Right-Right and Right-Left case.
        }
      }
    }
  }

  RBTNode* RBTree::successor(RBTNode *node) {              // returns the inorder successor of the given node.
    RBTNode *temp = node;

    while (temp->leftChild != NULL)
      temp = temp->leftChild;

    return temp;
  }

  RBTNode* RBTree::BSTreplace(RBTNode *node) {           // Returns the address of a node that replaces the given node after its deletions.
    
    if (node->leftChild != NULL && node->rightChild != NULL) // If given node has 2 children case.
      return successor(node->rightChild);

    if (node->leftChild == NULL && node->rightChild == NULL) // If given node is a leaf node.
      return NULL;

    if (node->leftChild != NULL)							 // If given node has either left or right child.	
      return node->leftChild;
    else
      return node->rightChild;
  }

  void RBTree::deleteNode(RBTNode *node) {                   // Deletes the given node from the Red-Black Tree.
    RBTNode *u = BSTreplace(node);

    bool doubleBlack = ((u == NULL || u->color == BLACK) && (node->color == BLACK));	// holds true if both u and given node are black.
    RBTNode *parent = node->parent;

    if (u == NULL) {					// If u is NULL, then node is the root.
      
      if (node == root) {				// Make root as NULL as node is the root.
        root = NULL;
      }
      else {
        if (doubleBlack) {				// If both u and given node are black.
          fixDoubleBlack(node);			// Fix double black case.
        }
        else {									// If either u or given node is red in color.
          if (node->getSiblingNode() != NULL)
            node->getSiblingNode()->color = RED;	// Make sibling red in color if there is a sibling to a given node.
        }

        if (node->isOnLeftSide()) {					// Delete node from the Red-Black Tree.
          parent->leftChild = NULL;
        }
        else {
          parent->rightChild = NULL;
        }
      }
      delete node;
      return;
    }

    if (node->leftChild == NULL || node->rightChild == NULL) {   // If given node has only one child.
      
      if (node == root) {										 // If node is root, then assign u to node and delete u.
    
        node->value = u->value;									
        node->leftChild = node->rightChild = NULL;
        delete u;
      }
      else {													// Remove connection of node from tree and move u upwards.

        if (node->isOnLeftSide()) {
          parent->leftChild = u;
        } else {
          parent->rightChild = u;
        }
        delete node;
        u->parent = parent;
        if (doubleBlack) {										// Fix double black.
          fixDoubleBlack(u);
        }
        else {
          u->color = BLACK;										// If u or node color is red then color u to black.
        }
      }
      return;
    }

    swapValues(u, node);										// Node has two children, so swap values of u and node.
    deleteNode(u);
  }

  void RBTree::fixDoubleBlack(RBTNode *node) {
    
    if (node == root)											// If node is root then double black doesn't affect anyone further, so return.
      return;

    RBTNode *sibling = node->getSiblingNode(), *parent = node->parent;
    
    if (sibling == NULL) {
      fixDoubleBlack(parent);									// If there is no sibling, then push the double black to node's parent.
    }
    else {
      
      if (sibling->color == RED) {		
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->isOnLeftSide()) {                         // If sibling is present in left side, rotate right.
          rightRotate(parent);
        }
        else {
          leftRotate(parent);								   // If sibling is present in right side, rotate left.
        }
        fixDoubleBlack(node);
      }
      else {
        if (sibling->hasRedChild()) {						   // If sibling is black
       
          if (sibling->leftChild != NULL && sibling->leftChild->color == RED) { // Has Red child
            if (sibling->isOnLeftSide()) {
              
              sibling->leftChild->color = sibling->color;						// Left-Left case
              sibling->color = parent->color;
              rightRotate(parent);
            }
            else {
       
              sibling->leftChild->color = parent->color;						// Right-Left case
              rightRotate(sibling);
              leftRotate(parent);
            }
          }
          else {
            if (sibling->isOnLeftSide()) {										// Left-Right case
              
              sibling->rightChild->color = parent->color;
              leftRotate(sibling);
              rightRotate(parent);
            }
            else {
              
              sibling->rightChild->color = sibling->color;						// Right-Right case
              sibling->color = parent->color;
              leftRotate(parent);
            }
          }
          parent->color = BLACK;
        }
        else {
          sibling->color = RED;
          if (parent->color == BLACK)
            fixDoubleBlack(parent);												// If there are 2 black children, fix double black on parent. 
          else
            parent->color = BLACK;
        }
      }
    }
  }

void RBTree::update(RBTNode *root, int buildingNumber, int executionTime) {     // updates the given execution time to the given building number's Red-Black Tree node.

    if (root == NULL || root->value.buildingNumber == buildingNumber)
        root->value.executionTime = executionTime;

    if (root->value.buildingNumber < buildingNumber)
        update(root->rightChild, buildingNumber, executionTime);

    if(root->value.buildingNumber > buildingNumber)
        update(root->leftChild, buildingNumber, executionTime);

}

void RBTree::searchAndStore(RBTNode *root, int firstBuilding, int lastBuilding, string &rangeValues) {       // Searches and returns the building's under construction in the given range.
  
  if(root == NULL)
    return;

  if(firstBuilding < root->value.buildingNumber)
    searchAndStore(root->leftChild, firstBuilding, lastBuilding, rangeValues);
  if(root->value.buildingNumber >= firstBuilding && root->value.buildingNumber <= lastBuilding) {
    stringstream ss;
    ss<<"(";
    ss<<root->value.buildingNumber;
    ss<<",";
    ss<<root->value.executionTime;
    ss<<",";
    ss<<root->value.totalTime;
    ss<<"),";
    rangeValues += ss.str();
  }
  if(lastBuilding > root->value.buildingNumber)
    searchAndStore(root->rightChild, firstBuilding, lastBuilding, rangeValues);

}

RBTNode* RBTree::search(RBTNode *root, int buildingNumber) {				// Search in Red Black Tree for the given building number.
    if (root == NULL || root->value.buildingNumber == buildingNumber)
        return root;
    if (root->value.buildingNumber < buildingNumber)
        return search(root->rightChild, buildingNumber);
    else
        return search(root->leftChild, buildingNumber);
}

RBTNode* RBTree::insertBST(RBTNode *root, RBTNode *ptr) {					// Insertion in Red-Black Tree - helper function similar to Binary Search Tree.
    if (root == NULL)
        return ptr;

    if (ptr->value.buildingNumber < root->value.buildingNumber) {
        root->leftChild = insertBST(root->leftChild, ptr);
        root->leftChild->parent = root;
    }
    else if (ptr->value.buildingNumber > root->value.buildingNumber) {
        root->rightChild = insertBST(root->rightChild, ptr);
        root->rightChild->parent = root;
    }
    return root;
}

RBTNode* RBTree::insert(Building value) {
    RBTNode *newNode = new RBTNode(value);
    root = insertBST(root, newNode);
    fixRedRed(newNode);
    return newNode;
}

void RBTree::deleteFromRBTree(int buildingNumber) {
    if (root == NULL)
        return;
    RBTNode *v = search(root, buildingNumber);
    deleteNode(v);
}


#endif // RED_BLACK_TREE_CPP


