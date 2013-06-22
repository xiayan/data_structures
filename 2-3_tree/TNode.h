#ifndef YANXIA_LAB8_TNODE_H_
#define YANXIA_LAB8_TNODE_H_

#include <iostream>
using std::cout;
using std::endl;

class TNode {
 public:
    int llow;  // To make remove() more efficient
    int mlow;
    int rlow;
    int key;
    int side;
    bool isLeaf;
    TNode *parent;
    TNode *left;
    TNode *middle;
    TNode *right;

    TNode *next;
    int   level;

    TNode(int k = -1, bool l = false) : llow(-1), mlow(-1), \
        rlow(-1), key(k), isLeaf(l), parent(NULL), left(NULL), \
        middle(NULL), right(NULL), next(NULL), level(-1) { }

    void print() const {
        if (isLeaf) {
            cout << key << " ";
        } else {
            if (rlow != -1)
                cout << "[" << mlow << ", " << rlow << "] ";
            else
                cout << "[" << mlow << ", " << "-] ";
        }
    }
};

#endif  // YANXIA_LAB8_TNODE_H_
