#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include "TNode.h"
using namespace std;

class AsciiTree;

class BinarySearchTree {
private:
    TNode *root;

    void insert(TNode *&t, int v);
    int  deleteMin(TNode *&t);
    int  deleteMax(TNode *&t);
    void remove(TNode *&t, int v);

    void clear(TNode *&t);

    void inOrder(TNode *t);
    void preOrder(TNode *t);
    
    friend class AsciiTree;
    
public:
    
    BinarySearchTree();
    ~BinarySearchTree(); 
    
    void insert(int v){ insert(root, v); }
    void deleteMin() { deleteMin(root); }
    void deleteMax() { deleteMax(root); }
    void remove(int v) { remove(root, v); }

    void clear(){ clear(root); }

    void inOrder() { cout << "In: " ;  inOrder(root); cout << endl; }
    void preOrder(){ cout << "Pre: "; preOrder(root); cout << endl; }
};
#endif /* BINARYSEARCHTREE_H_ */
