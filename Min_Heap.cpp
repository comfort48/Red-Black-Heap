#ifndef MIN_HEAP_CPP
#define MIN_HEAP_CPP

#include "Building.hpp"
#include "Min_Heap.hpp"
#include <algorithm>

// Initializes the heap size to 0 and creates the min_heap_array with the maximum size possible at any point in time.
Min_Heap::Min_Heap(int capacityOfMinHeap) {
    min_heap_size = 0;
    capacityOfMinHeap = capacityOfMinHeap;
    min_heap_array = new pair<Building, RBTNode*>[capacityOfMinHeap];
}

int Min_Heap::getParentNodeIndex(int i) {
    return (i-1)/2;
}

int Min_Heap::getLeftNodeIndex(int i) {
    return (2*i + 1);
}

int Min_Heap::getRightNodeIndex(int i) {
    return (2*i + 2);
}

void Min_Heap::push(pair<Building, RBTNode*> nodeValue) {

    min_heap_size++;
    int i = min_heap_size - 1;
    min_heap_array[i] = nodeValue;

    while(min_heap_array[i].first.executionTime <= min_heap_array[getParentNodeIndex(i)].first.executionTime && i != 0){  // If Execution times are equal - go for building number.
        if(min_heap_array[i].first.executionTime < min_heap_array[getParentNodeIndex(i)].first.executionTime){
            min_heap_array[i].swap(min_heap_array[getParentNodeIndex(i)]);
            i = getParentNodeIndex(i);
        }
        else if(min_heap_array[i].first.executionTime == min_heap_array[getParentNodeIndex(i)].first.executionTime){    // If execution times are equal - go for building number.
            if(min_heap_array[i].first.buildingNumber < min_heap_array[getParentNodeIndex(i)].first.buildingNumber){
                min_heap_array[i].swap(min_heap_array[getParentNodeIndex(i)]);
                i = getParentNodeIndex(i);
            }
            else{
                break;
            }
        }
    }
}

void Min_Heap::minHeapify(int i) {

    int leftNodeIndex = getLeftNodeIndex(i);
    int rightNodeIndex = getRightNodeIndex(i);
    int smallestNodeIndex = i;

    if(min_heap_size > leftNodeIndex){
        if(min_heap_array[leftNodeIndex].first.executionTime < min_heap_array[i].first.executionTime)    // If execution times are equal go for building number.
            smallestNodeIndex = leftNodeIndex;
        else if(min_heap_array[leftNodeIndex].first.executionTime == min_heap_array[i].first.executionTime){
            if(min_heap_array[leftNodeIndex].first.buildingNumber < min_heap_array[i].first.buildingNumber)
                smallestNodeIndex = leftNodeIndex;
        }
    }

    if(min_heap_size > rightNodeIndex){
        if(min_heap_array[rightNodeIndex].first.executionTime < min_heap_array[smallestNodeIndex].first.executionTime)   // // If execution times are equal go for building number.
            smallestNodeIndex = rightNodeIndex;
        else if(min_heap_array[rightNodeIndex].first.executionTime == min_heap_array[smallestNodeIndex].first.executionTime){
            if(min_heap_array[rightNodeIndex].first.buildingNumber < min_heap_array[smallestNodeIndex].first.buildingNumber)
                smallestNodeIndex = rightNodeIndex;
        }
    }

    if(smallestNodeIndex != i){
        min_heap_array[i].swap(min_heap_array[smallestNodeIndex]);
        minHeapify(smallestNodeIndex);
    }
}

pair<Building, RBTNode*> Min_Heap::top() {
    return min_heap_array[0];
}

void Min_Heap::pop() {
    pair<Building, RBTNode*> root = min_heap_array[0];
    min_heap_array[0] = min_heap_array[min_heap_size-1];
    min_heap_size--;
    minHeapify(0);
}

unsigned int Min_Heap::size(){
    return min_heap_size;
}

#endif // MIN_HEAP_CPP
