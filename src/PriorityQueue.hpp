//
//  PriorityQueue.hpp
//  A* Demo
//
//  Created by Kelvin Hu on 11/17/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp

#include <stdio.h>
#include <vector>
#include <string>

class Empty {
public:
    Empty(const std::string& msg) {}
};

template <typename T>
class PriorityQueue {
    
public:
    void add(T val);
    T removeMin();
    int size();
    bool isEmpty() const;
    void upheap(int index);
    void downHeap(int index);
    std::vector<T>& getContainer();
    
private:
    std::vector<T> heap;
    int getParent(int index) const;
    int getLeftChild(int index) const;
    int getRightChild(int index) const;
    bool hasLeftChild(int index) const;
    bool hasRightChild(int index) const;
    void swap(int a, int b);
};


template <typename T>
void PriorityQueue<T>::add(T val) {
    heap.push_back(val);
    upheap((int)heap.size()-1);
}

template <typename T>
T PriorityQueue<T>::removeMin() {
    
    swap(0, (int)heap.size()-1);
    T val = heap.back();
    heap.pop_back();
    downHeap(0);
    return val;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const { return !heap.size(); }

template <typename T>
int PriorityQueue<T>::getParent(int index) const {
    return (index-1) / 2;
}

template <typename T>
void PriorityQueue<T>::swap(int a, int b) {
    T temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

template <typename T>
void PriorityQueue<T>::upheap(int index) {
    if (index > 0) {
        int parent = getParent(index);
        if (heap[index]->FScore < heap[parent]->FScore) {
            swap(index, parent);
            upheap(parent);
        }
    }
}

template <typename T>
int PriorityQueue<T>::getLeftChild(int index) const {
    return 2 * index + 1;
}

template <typename T>
int PriorityQueue<T>::getRightChild(int index) const {
    return 2 * index + 2;
}

// Does index have a left child?
template <typename T>
bool PriorityQueue<T>::hasLeftChild(int index) const {
    return getLeftChild(index) < (int)heap.size();
}

// Does index have a right child?
template <typename T>
bool PriorityQueue<T>::hasRightChild(int index) const {
    return getRightChild(index) < (int)heap.size();
}

// Move the item at index down as far as it should go, staying on
// the smaller side.
template <typename T>
void PriorityQueue<T>::downHeap(int index) {
    // if there isn't a left child then there aren't any children
    // and we are done.
    if (hasLeftChild(index)) {
        int leftChild = getLeftChild(index);
        int minChild = leftChild;
        if (hasRightChild(index)) {
            int rightChild = getRightChild(index);
            if (heap[rightChild]->FScore < heap[leftChild]->FScore) {
                minChild = rightChild;
            }
        }
        if (heap[minChild]->FScore < heap[index]->FScore) {
            swap(index, minChild);
            downHeap(minChild);
        }
    }
}

template <typename T>
std::vector<T>& PriorityQueue<T>::getContainer() {
    return heap;
}

template <typename T>
int PriorityQueue<T>::size() {
    return (int)heap.size();
}


#endif /* PriorityQueue_hpp */
