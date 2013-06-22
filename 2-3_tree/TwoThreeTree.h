#ifndef YANXIA_LAB8_TWOTHREETREE_H_
#define YANXIA_LAB8_TWOTHREETREE_H_

#include "TNode.h"

class AsciiTree;

class TwoThreeTree {
 private:
    TNode *root;

    TNode * locate(int x);
    TNode * find(int x);
    void    swapNodes(TNode *, TNode *);
    void    connect(TNode *, TNode *, int);
    void    attach(TNode *, TNode *);
    TNode * createLeaf(int x);
    void    preOrder(TNode *t);
    void    clear(TNode *&t);
    void    remove(TNode *t);
    void    fixTree(TNode *t, int x);
    void    fixThreeNode(TNode *t, int x);
    void    fixTwoNode(TNode *t, int x);
    void    adoptChild(TNode *p, TNode *q);
    void    loseChild(TNode *p, TNode *q);
    void    fixLowVals(TNode *p);

    friend class AsciiTree;

 public:
    TwoThreeTree();
    ~TwoThreeTree();
    void insert(int x);
    void remove(int x);
    void deleteMin();
    void deleteMax();
    void clear() { clear(root); }
    void preOrder() { preOrder(root); cout << endl; }
    void levelOrder();
};

#endif  // YANXIA_LAB8_TWOTHREETREE_H_
