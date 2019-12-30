#ifndef RED_BLACK_TREE_NODE_CPP
#define RED_BLACK_TREE_NODE_CPP

#include "Red_Black_Tree_Node.hpp"
#include <iostream>
using namespace std;

RBTNode::RBTNode(Building val) {            // Red-Black Tree node Initialization.
    value = val;
    parent = leftChild = rightChild = NULL;
    color = RED;
}

RBTNode* RBTNode::getUncleNode() {      // Return uncle node of given node.
    if (parent == NULL || parent->parent == NULL)
        return NULL;
    if (parent->isOnLeftSide())
        return parent->parent->rightChild;
    else
        return parent->parent->leftChild;
}

bool RBTNode::isOnLeftSide() {  // Check if given node is present in left side of its parent.
    return (this == parent->leftChild);
}

RBTNode* RBTNode::getSiblingNode() {        // Returns the sibling of a given node.

    if (parent == NULL)
        return NULL;

    if (isOnLeftSide())
        return parent->rightChild;

    return parent->leftChild;

}

void RBTNode::moveDown(RBTNode *newParent) {    // Reorders the given node with respect to the newParent given as argument.
    if (parent != NULL) {
        if (isOnLeftSide()) {
            parent->leftChild = newParent;
        }
        else {
            parent->rightChild = newParent;
        }
    }
    newParent->parent = parent;
    parent = newParent;
}

bool RBTNode::hasRedChild() {   // Returns true if there is a red child for a given node.
    return (leftChild != NULL && leftChild->color == RED) ||(rightChild != NULL && rightChild->color == RED);
}

#endif // RED_BLACK_TREE_NODE_CPP
