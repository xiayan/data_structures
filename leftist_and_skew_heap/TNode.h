#ifndef YANXIA_LAB10_TNODE_H_
#define YANXIA_LAB10_TNODE_H_

#include <iostream>
using namespace std;

class TNode
{	
 public:
    int value;
    int rank;
    int level; // for level order printing
    TNode *left;
    TNode *right;

    TNode *next; // for level order printing

    TNode(int v) : value(v), rank(1), level(-1), left(NULL), right(NULL), next (NULL) { }
    void print() const { cout << value << " "; }
};

#endif /* YANXIA_LAB10_TNODE_H */
