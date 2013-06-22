#ifndef YANXIA_LAB10_BINARYHEAP_H_
#define YANXIA_LAB10_BINARYHEAP_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

class BinaryHeap {
 private:
    static const int CAPACITY = 1000; // default capacity
    int *pq;
    int N;  // size
    int cap; // capacity of the heap
    
    friend class AsciiTree;

    void buildHeap();
    void swim(int k); // percolate up operation
    void sink(int k); // percolate down operation
    void exch(int i, int j);

 public:
    BinaryHeap(int capacity = CAPACITY);
    BinaryHeap(int *array, int s);
    BinaryHeap(ifstream &ifs, int capacity = CAPACITY);
    ~BinaryHeap();
    bool isEmpty();
    int  getSize();
    int  findMin();
    void insert(int x);
    int  deleteMin();
    int  deleteMax();
    void print();
};

#endif
