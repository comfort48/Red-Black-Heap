#ifndef RED_BLACK_TREE_NODE_HPP
#define RED_BLACK_TREE_NODE_HPP

#include "Building.hpp"
using namespace std;

enum COLOR {              // Custom defined DataType for defining the Color of a Red Black Tree Node.
    RED,
    BLACK
};

class RBTNode {

public:
  Building value;      // The Building value that Wayne constructions get as an order to construct.
  COLOR color;         // Color of a Red Black Tree Node.
  RBTNode *leftChild, *rightChild, *parent;    // 3 pointers to store the leftChild, rightChild and parent addresses (Becomes easy to access when we change the ordering in Red Black Tree during insertion and deletion).

  RBTNode(Building val);                       // Constructor to make a Red Black Tree Node.
  RBTNode* getUncleNode();					   // Returns the uncleNode address of a given Node.
  bool isOnLeftSide();                         // return true if the given node is a left Child of a node.
  RBTNode* getSiblingNode();				   // Returns the siblingNode address of a given Node.
  void moveDown(RBTNode *newParent);           // Rearranges the node with the newly given ParentNode address.
  bool hasRedChild();                          // return true if the given node has a Red Color child.

};

#endif // RED_BLACK_TREE_NODE_HPP
