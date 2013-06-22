#include "LeftistHeap.h"

int LeftistHeap::computeRank(TNode *h) {
    if (h == NULL) return 0;
    if (h->right == NULL) return 1;
    return h->right->rank + 1;
}


TNode * LeftistHeap::merge(TNode *h1, TNode *h2) {
    // cout << "Leftist Merge called.\n";
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;

    if (h1->value > h2->value)
        swap(h1, h2);
    h1->right = merge(h1->right, h2); // merge to right subtree
    
    // swap if leftist tree property is violated
    if (computeRank(h1->left) < computeRank(h1->right))
        swap(h1->left, h1->right);
    // recompute rank
    h1->rank = computeRank(h1->right) + 1;
    return h1;
}

