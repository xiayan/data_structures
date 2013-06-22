#ifndef YANXIA_LAB11_TQUEUE_H_
#define YANXIA_LAB11_TQUEUE_H_

#include "BNode.h"
#include <iostream>

using namespace std;

class TQueue {	
 private:
    BNode *first;
    int s; // size of the list

 public:
	TQueue();
	~TQueue();

    bool isEmpty();
	void push(BNode *x);
    BNode * top();
    void pop();
};

#endif  // YANXIA_LAB11_TQUEUE_H_
