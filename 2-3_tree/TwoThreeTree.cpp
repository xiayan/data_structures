/* In the comments, "O" represents nodes that are already
 * in the 2-3 tree. "X" represents nodes that need to be
 * inserted.
 *
 * "llow" is the lowest value from the left subtree.
 * "mlow" is the lowest value from the middle subtree.
 * "rlow" is the lowest value from the right subtree.
 * rlow = -1 indicates the node is a "2-node", which has no right tree.
 *
 * In the TNode objests, "side = -1" indicates it is a left child
 * "side = 0" indicates it is a middle child; "side = 1" indicates right child
*/

#include "TwoThreeTree.h"
#include "TQueue.h"
#include <stdlib.h>

TwoThreeTree::TwoThreeTree() : root(NULL) { }

TwoThreeTree::~TwoThreeTree() {
    clear(root);
}

TNode * TwoThreeTree::locate(int x) {
    // locate the leaf node that is either contain the value x
    // or to the immediate left of the new node with value x.
    TNode *p = root;
    
    while (!p->isLeaf) {
        if (p->rlow != -1 && x >= p->rlow)
            p = p->right;
        else if (x < p->mlow)
            p = p->left;
        else
            p = p->middle;
    }

    return p;
}

TNode * TwoThreeTree::find(int x) {
    // use the locate method to see if the tree contains x.
    // if no, return null.
    TNode *p = locate(x);

    if (p->key == x) return p;
    else             return NULL;
}

void TwoThreeTree::swapNodes(TNode *p, TNode *q) {
    int t = q->key;
    q->key = p->key;
    p->key = t;
    q->llow = p->llow;
    p->llow = t;

    while (p->parent) {
        if (p->side != -1) {
            cout << "ERROR!";
            cout << "Swap should happen only for smallest value in the list.\n";
            exit(1);
        }

        p->parent->llow = t;
        p = p->parent;
    }
}

void TwoThreeTree::connect(TNode *c, TNode *p, int s) {
    // connects child node "c" with parent node "p"
    // updates child and parent pointers, side values, and low values
    switch (s) {
        case -1: p->left   = c; c->side = -1; p->llow = c->llow; break;
        case  0: p->middle = c; c->side =  0; p->mlow = c->llow; break;
        case  1: p->right  = c; c->side =  1; p->rlow = c->llow; break;
        default: break;
    }

    c->parent = p;
}

void TwoThreeTree::attach(TNode *p, TNode *q) {
    // attach q to the parent of p
    if (p == root) {
        // leaf node p is the root
        root = new TNode();
        connect(p, root, -1);
        connect(q, root, 0);
    } else if (p->parent->rlow == -1) {
        // p's parent is a 2-node
        TNode *s = p->parent;
        int branch = p->side;
        // "O" is nodes on the tree, "X" is node needed to be inserted
        if (branch == 0) {
            // Insertion pattern: "O O X"
            connect(q, s, 1);
        } else if (branch == -1) {
            // Insertion pattern: "O X O"
            TNode *u = s->middle;
            connect(u, s, 1);
            connect(q, s, 0);
        }
    } else {
        // p's parent is a 3-node
        TNode *s = p->parent;
        TNode *r = new TNode(); // split the node
        int branch = p->side;

        if (branch == 1) {
            // Insertion pattern: "O O O X"
            connect(q, r, 0);
            connect(p, r, -1);
        } else {
            TNode *v = s->right;
            connect(v, r, 0);
            if (branch == 0) {
                // Insertion pattern: "O O X O"
                connect(q, r, -1);
            } else {
                // Insertion pattern: "O X O O"
                TNode *u = s->middle;
                connect(u, r, -1);
                connect(q, s, 0);
            }
        }
        s->right = NULL;
        s->rlow  = -1;
        attach(s, r);
    }
}

TNode * TwoThreeTree::createLeaf(int x) {
    // create leaf node
    TNode *q = new TNode();
    q->key = x;
    q->isLeaf = true;
    q->llow = x;
    q->mlow = -1;
    q->rlow = -1;
    return q;
}

void TwoThreeTree::insert(int x) {
    // insert x into the 2-3 tree
    if (root == NULL) {
        root = createLeaf(x);
        return;
    }

    TNode *p = locate(x);
    // duplication is allowed, but a note will be generated
    if (p->key == x) {
        cout << "Note: duplication of " << x << " is inserted.\n";
    }

    TNode *q = createLeaf(x);
    // swap the old left most node with the new node if the new node
    // is smallest. Avoid the insertion pattern "X O O O"
    if (p->key > x) {
        swapNodes(p, q);
    }

    attach(p, q);
}

void TwoThreeTree::fixLowVals(TNode *p) {
    // fix the llow, rlow, mlow fileds in the ancestor nodes of p
    TNode *r = p;
    
    while (r) {
        if (r == root) break;

        TNode *g = r->parent;
        g->llow = g->left->llow;
        g->mlow = g->middle->llow;
        if (g->rlow != -1)
            g->rlow = g->right->llow;
        
        // if r is not the left child, the value change will not 
        // be able to propagate over r's parent.
        if (r->side != -1)
            break;

        r = g;
    }
}

void TwoThreeTree::fixThreeNode(TNode *d, int s) {
    TNode *p = d->parent;

    // again, if the modified node is not a left child
    // it will not have effect on nodes beyond its parent.
    bool needFix = (d->side == -1);
    delete d;

    if (s == -1) {
        // Deletion pattern: "X O O"
        connect(p->middle, p, -1);
        connect(p->right, p, 0);

        p->right = NULL;
        p->rlow = -1;
    } else if (s == 0) {
        // Deletion pattern: "O X O"
        connect(p->right, p, 0);

        p->rlow = -1;
        p->right = NULL;
    } else {
        // Deletion pattern: "O O X"
        p->rlow = -1;
        p->right = NULL;
    }

    if (needFix)
        fixLowVals(p);
}

void TwoThreeTree::adoptChild(TNode *p, TNode *s) {
    // After deletion in a 2-node, if its sibling is a 3-node,
    // borrow one node from the sibling

    // order computes if p is on the left or right of s
    int order = p->side - s->side;
    if (order < 0) {
        // Insertion pattern: "p:O q:O O O"
        connect(p->middle, p, -1);
        connect(s->left, p, 0);
        p->right = NULL;
        connect(s->middle, s, -1);
        connect(s->right, s, 0);
        s->right = NULL;

        p->rlow = -1;
        s->rlow = -1;
    } else {
        // Insertion pattern: "q:O O O p:O"
        connect(s->right, p, -1);
        p->right = NULL;
        s->right = NULL;

        p->rlow = -1;
        s->rlow = -1;
    }
}

void TwoThreeTree::loseChild(TNode *p, TNode *s) {
    // if p's sibling s has only two child, p loses its child to p
    int order = p->side - s->side;
    if (order < 0) {
        // Insertion pattern: "p:O q:O O"
        connect(s->middle, s, 1);
        connect(s->left, s, 0);
        connect(p->middle, s, -1);
        p->middle = NULL;
    } else {
        // Insertion pattern: "q:O O p:O"
        connect(p->middle, s, 1);
        p->middle = NULL;
    }
}

void TwoThreeTree::fixTwoNode(TNode *d, int s) {
    TNode *p = d->parent;
    // get d's sibling.
    TNode *dSib = (s == -1) ? p->middle : p->left;
    delete d;
    
    // base case when d's parent is root
    if (p == root) {
        root = dSib;
        dSib->parent = NULL;
        delete p;
        return;
    }
    
    // connect d's sibling to middle to unify different cases
    connect(dSib, p, 0);
    p->left = NULL;
    p->right = NULL;

    // get p's parent, which is d's grandparent
    TNode *g = p->parent;
    TNode *pSib = NULL;
    
    // get p's sibling
    if (g->rlow == -1)
        pSib = (p->side == -1) ? g->middle : g->left;
    else
        pSib = (p->side == 0) ? g->left : g->middle;
    
    if (pSib->rlow != -1) {
        // if p's sibling is a 3-node, call adoptchild
        adoptChild(p, pSib);
        fixLowVals(p);
    } else {
        // if p's sibling is a 2-node, call lose child
        loseChild(p, pSib);
        // recursively fix p
        fixTree(p, p->side);
    }
}

void TwoThreeTree::fixTree(TNode *d, int s) {
    if (d->parent->rlow != -1)
        fixThreeNode(d, s);
    else
        fixTwoNode(d, s);
}

void TwoThreeTree::remove(int x) {
    if (root == NULL) return;

    // identify the node containing x
    TNode *d = find(x);
    if (d == NULL) {
        cout << x << " not in the tree.\n";
        return;
    }
    
    // delete the node
    remove(d);
}

void TwoThreeTree::remove(TNode *d) {
    if (root == d) {
        delete d;
        root = NULL;
        return;
    }

    fixTree(d, d->side);
}

void TwoThreeTree::deleteMin() {
    if (root == NULL) return;

    TNode *runner = root;

    // identify the left most leaf node
    while (!runner->isLeaf)
        runner = runner->left;

    remove(runner);
}

void TwoThreeTree::deleteMax() {
    if (root == NULL) return;

    TNode *runner = root;

    // identify the right most leaf node
    while (!runner->isLeaf)
        runner = (runner->rlow == -1) ? runner->middle : runner->right;

    remove(runner);
}

void TwoThreeTree::preOrder(TNode *r) {
    if (r == NULL) return;

    r->print();
    preOrder(r->left);
    preOrder(r->middle);
    preOrder(r->right);
}

void TwoThreeTree::levelOrder() {
    if (root == NULL) return;

    // Use a tree to do levelOrder Traversal
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
        if (!t->isLeaf) {
            int nextLevel = t->level + 1;
            t->left->level = nextLevel;
            queue.push(t->left);

            t->middle->level = nextLevel;
            queue.push(t->middle);

            if (t->rlow != -1) {
                t->right->level = nextLevel;
                queue.push(t->right);
            }
        }

        queue.pop();
    }
    cout << endl << endl;
}

void TwoThreeTree::clear(TNode *&r) {
    if (r == NULL) return;

    clear(r->left);
    clear(r->middle);
    clear(r->right);

    delete r;
    r = NULL;
}
