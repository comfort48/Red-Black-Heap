#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include "Building.hpp"
#include "Red_Black_Tree.cpp"
#include "Red_Black_Tree.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Min_Heap
{
    pair<Building, RBTNode*> *min_heap_array; // Elements in heap are stored as an array of pairs ----->>>>> <pair.first> holds the Building node in Min Heap, <pair.second> is the Address of the corresponding node in Red Black Tree.
    int capacityOfMinHeap;                    // Total capacity of Min Heap - In this problem its fixed to 2000, but can increase on demand.
    int min_heap_size;						  // Total size of Min Heap at any point in time.
public:

    Min_Heap(int totalSize);				  // Min Heap Constructor which assigns the capacity to Min Heap.

    int getParentNodeIndex(int i);			  // Returns the Parent node index for a given valid index.

    int getLeftNodeIndex(int i);			  // Returns the Left node index for a given valid index.

    int getRightNodeIndex(int i);             // Returns the Right node index for a given valid index.

    void push(pair<Building, RBTNode*> nodeValue);  // Inserts the given pair<Building, RBTNode*> into the Min Heap and maintains the Min Heap property after insertion - Criteria is less execution time.

    void minHeapify(int );                          // Sets the Min Heap property if there is a violation when we remove some element from the Min Heap - Criteria is less execution time.

    pair<Building, RBTNode*> top();					// Returns the First Element in the Min Heap which is the minimum of all the elements in the Min Heap.

    void pop();										// Deletes the First Element from the Min Heap and calls the minHeapify method to maintain the Heap Property after Deletion.

    unsigned int size();							// Returns the size of the Min Heap.

};

#endif // MIN_HEAP_HPP
