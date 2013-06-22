#ifndef YANXIA_LAB9_MINMAXHEAP_H_
#define YANXIA_LAB9_MINMAXHEAP_H_

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

class MinMaxHeap {
 private:	
	static const int DEFAULT_CAPACITY = 10000;
	int* array;
	int size;

    friend class AsciiTree;

	// Information Methods
	bool atMinLevel(int i);
	int  getParent(int child);
	int  getGrandParent(int child);
    int  getFirstGrandChild(int parent);
	bool hasLeftChild(int parent);
    bool hasRightChild(int parent);
	bool isGrandChild(int child, int parent);
	int  findMaxChild(int parent);
	int  findMinChild(int parent);
    bool isLeaf(int idx); //

	// Manipulation Methods
	void buildHeap();
	void percolateDown(int i);
	void percolateDownMin(int i);
	void percolateDownMax(int i);
	void swimMin();
	void swimMax();
#ifdef DEBUG
    bool check();
    unsigned long heapSum();
    void debugHeap(int c, int a = -1);
#endif

 public:
    MinMaxHeap(ifstream &is);
	MinMaxHeap(int *data, int n);
	~MinMaxHeap();
	bool isEmpty();
    bool isFull();
	void levelOrder();
	void insert(int item);
	int  findMin();
	int  findMax();
	void deleteMin();
	void deleteMax();
    int  getSize() { return size; }
};

#endif /* YANXIA_LAB9_MINMAXHEAP_H_ */
