#include "SkewHeap.h"
#include "TQueue.h"

SkewHeap::SkewHeap() : root(NULL) { }

void SkewHeap::swap(TNode *&h1, TNode *&h2) {
    TNode *temp = h1;
    h1 = h2;
    h2 = temp;
}

SkewHeap::~SkewHeap() {
    makeEmpty(root);
}

TNode * SkewHeap::merge(TNode *h1, TNode *h2) {
    // cout << "Skew Merge called.\n";
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    if (h1->value > h2->value)
        swap(h1, h2);    

    // always swap after merge
    TNode *temp = h1->right;
    h1->right = h1->left;
    h1->left = merge(temp, h2);
    return h1;
}

void SkewHeap::makeEmpty(TNode *&h) {
    if (h == NULL) return;

    makeEmpty(h->left);
    makeEmpty(h->right);
    // cout << "Deleting " << h->value << endl;
    delete h;
    h = NULL;
}
		
void SkewHeap::insert(int v) {
    // reduce insert to merge
    TNode *newNode = new TNode(v);
    root = merge(root, newNode);
}

void SkewHeap::merge(SkewHeap &rhs) {
    if (this == &rhs)
        return;

    root = merge(root, rhs.root);
    rhs.root = NULL;
}

int SkewHeap::findMin() {
    return root->value;
}

int SkewHeap::deleteMin() {
    if (isEmpty()) {
        cout << "Error.  DeleteMin from empty heap.\n";
        return -1;
    }

    // reduce deletMin to merge
    int min = findMin();
    TNode *toDelete = root;
    root = merge(root->left, root->right);
    delete toDelete;

    return min;
}

bool SkewHeap::isEmpty() {
    return root == NULL;
}

void SkewHeap::makeEmpty() {
    makeEmpty(root);
}

void SkewHeap::print() {
    if (root == NULL) return;

    TQueue queue;
    queue.push(root);
    root->level = 0;

    cout << "Level Order Traversal:\n";

    int currentLevel = 0;
    while (!queue.isEmpty()) {
        const TNode *t = queue.top();
        
        if (t->level != currentLevel) {
            cout << endl;
            currentLevel = t->level;
        }
        
        // push t's children on queue, set their level nubmer
        t->print();
        int nextLevel = t->level + 1;
        if (t->left) {
            t->left->level = nextLevel;
            queue.push(t->left);
        }

        if (t->right) {
            t->right->level = nextLevel;
            queue.push(t->right);
        }

        queue.pop();
    }
    cout << endl << endl;
}
