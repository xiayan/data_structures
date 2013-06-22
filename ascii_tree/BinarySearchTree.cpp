#include "BinarySearchTree.h"
#include "limits.h"

BinarySearchTree::BinarySearchTree() : root(NULL) {
}

BinarySearchTree::~BinarySearchTree() {
    // call the clear routine to delete all the nodes post order.
    clear();
}

void BinarySearchTree::inOrder(TNode *t) {
    // Base case: if t is null, return
    if (t == NULL) return;
    
    // else, visit left node, current node and right node recursively.
    inOrder(t->left);
    t->print();
    inOrder(t->right);
}

void BinarySearchTree::preOrder(TNode *t) {
    // Base case: if t is null, return
    if (t == NULL) return;
    
    // else, visit current node, left node and right node recursively.
    t->print();
    preOrder(t->left);
    preOrder(t->right);
}

void BinarySearchTree::clear(TNode *&t) {
    // Base case: if t is null, return
    if (t == NULL) return;
    
    // clear left node, right node recursively
    clear(t->left);
    clear(t->right);
    // after the descendants are deleted, delete current node
    delete t;
    // reset dangling pointers
    t = NULL;
}

void BinarySearchTree::insert(TNode *&t, int v) {
    // if t is null, we found the place for v, insert it.
    if (t == NULL)
        t = new TNode(v);
    // find the right position according to binary search tree criterion
    else if (v < t->value)
        insert(t->left, v);
    else if (v > t->value)
        insert(t->right, v);
    else {
        cout << v << ": Duplication is not allowed.\n";
        return;
    }
}

int BinarySearchTree::deleteMin(TNode *&t) {
    if (t == NULL) {
        // return the smallest bit int to indicate error
        cout << "Error. Empty tree.\n";
        return INT_MIN;
    }

    // find the left most node
    if (t->left == NULL) {
        TNode *oldMin = t;
        int min = t->value;
        // replace t with t's right child
        t = t->right;
    
        delete oldMin;
        return min;
    }

    return deleteMin(t->left);
}

int BinarySearchTree::deleteMax(TNode *&t) {
    if (t == NULL) {
        // return the smallest int to indicate error
        cout << "Error. Emptry ree.\n";
        return INT_MIN;
    }

    if (t->right == NULL) {
        TNode *oldMax = t;
        int max = t->value;
        // replace t with t's left child
        t = t->left;

        delete oldMax;
        return max;
    }

    return deleteMax(t->right);
}

void BinarySearchTree::remove(TNode *&t, int v) {
    if (t == NULL) {
        cout << v << " is not in the search tree.\n";
        return;
    }

    if (v < t->value)
        remove(t->left, v);
    else if (v > t->value)
        remove(t->right, v);
    else if (t->left && t->right) {
        // replace the current value with right in-order descedent
        t->value = deleteMin(t->right);
    }
    else {
        TNode *toDelete = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete toDelete;
    }
}

