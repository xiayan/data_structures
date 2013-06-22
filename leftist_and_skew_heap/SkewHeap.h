#ifndef YANXIA_LAB10_SKEWHEAP_H_
#define YANXIA_LAB10_SKEWHEAP_H_

#include "TNode.h"

class SkewHeap {
 private:
	TNode *root;

    friend class AsciiTree;

	virtual TNode* merge(TNode *h1, TNode *h2);
	void makeEmpty(TNode *&h);

 protected:
    void swap(TNode *&h1, TNode *&h2);
		
 public:
    SkewHeap();
	~SkewHeap();
	void insert(int v);
    void merge(SkewHeap &rhs);
	int  findMin();
	int  deleteMin();
	bool isEmpty();
	void makeEmpty();
    void print();
};

#endif /* YANXIA_LAB10_SKEWHEAP_H_ */
