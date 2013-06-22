#ifndef YANXIA_LAB8_TQUEUE_H_
#define YANXIA_LAB8_TQUEUE_H_

#include "TNode.h"
#include <iostream>

using namespace std;

class TQueue {	
 private:
    TNode* first;
    int s; // size of the list

 public:
	TQueue();
	~TQueue();

    bool isEmpty();
	void push(TNode *x);
    const TNode * top();
    void pop();
};

#endif  // YANXIA_LAB8_TQUEUE_H_
