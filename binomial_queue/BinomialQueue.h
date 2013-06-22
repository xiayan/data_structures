#ifndef YANXIA_LAB11_BINOMIALQUEUE_H_
#define YANXIA_LAB11_BINOMIALQUEUE_H_

#include <algorithm>
#include "BNode.h"

class BinomialQueue {
    private:
        BNode *q;

        void append(BNode *v);
        BNode * meld(BNode *a, BNode *b);
        void combine(BNode *v, BNode *w, BNode *c);

        void removeTree(BNode *v, BinomialQueue &Q);
        BNode * minTree();

        void reset(BNode *t);
        void makeEmpty(BNode *&t);

        int  assignX(BNode *t);

    public:
        BinomialQueue();
        BinomialQueue(int v);
        ~BinomialQueue();
        void insert(int v);
        int  findMin();
        int  deleteMin();
        void merge(BinomialQueue &rhs);
        bool isEmpty();
        void makeEmpty();
        void levelOrder();
};

#endif /* YANXIA_LAB11_BINOMIALQUEUE_H_ */
