#include "BinomialQueue.h"
#include "TQueue.h"
#include <climits>
#include <sstream>

BinomialQueue::BinomialQueue() : q(NULL) { }

BinomialQueue::BinomialQueue(int v) {
    // constructor for insert new items
    q = new BNode(v);
}

BinomialQueue::~BinomialQueue() { makeEmpty(); }

void BinomialQueue::merge(BinomialQueue &rhs) {
    BNode *tq = q;
    BNode *rq = rhs.q;

    q = NULL;     // set the root to null for reordering queues
    rhs.q = NULL; // get rid of the dangling pointer

    combine(tq, rq, NULL);
}

void BinomialQueue::append(BNode *a) {
    // method that appends a to the fisrt level linked list

    if (q == NULL) {
        // if this is an empty queue, set a to be the root
        q = a;
        reset(q); // reset q's pointer connections
    } else if (a != NULL) {
        // add a to the linked list pointed by q
        a->l_sib = q->l_sib;
        a->l_sib->r_sib = a;
        q->l_sib = a;
        a->r_sib = NULL;
    }
}

void BinomialQueue::reset(BNode *t) {
    if (t != NULL) {
        t->l_sib = t;
        t->r_sib = NULL;
    }
}

BNode * BinomialQueue::meld(BNode *a, BNode *b) {
    // method that connects "b" to the first child linked list of "a".

    if (a->key > b->key) {
        meld(b, a);
        return b;
    }

    if (a->order == 0) {
        a->f_child = b;
        reset(a);
        reset(b);
    } else {
        b->l_sib = a->f_child->l_sib;
        b->l_sib->r_sib = b;
        a->f_child->l_sib = b;
        b->r_sib = NULL;
    }

    a->order += 1;

    return a;
}

void BinomialQueue::combine(BNode *a, BNode *b, BNode *c) {
    // "a" and "b" are two queues to be combined. "c" is the carry queue
    // from previous rounds

    if (a == NULL and b == NULL) {
        append(c);
        return;
    }

    if (a == NULL || (b != NULL && a->order > b->order)) {
        combine(b, a, c);
        return;
    }

    int whichCase = 0;
    BNode *aRSib = a->r_sib;
    BNode *bRSib = (b) ? b->r_sib : NULL;

    if (b != NULL) whichCase += 1;
    if (c != NULL) whichCase += 2;
    if (b != NULL && a->order == b->order) whichCase += 4;
    if (c != NULL && a->order == c->order) whichCase += 8;

    switch(whichCase) {
        case 0:
            // b = null, c = null
            append(a);
            break;
        case 1:
            // b != null, c = null, a < b
            append(a);
            break;
        case 2:
            // b = null, c != null, c < a
            append(c);
            append(a);
            c = NULL;
            break;
        case 3:
            // b != null, c != null, c < a < b
            append(c);
            append(a);
            c = NULL;
            break;
        case 5:
            // b != null, c = null, a = b
            c = meld(a, b);
            b = bRSib;
            break;
        case 7:
            // b != null, c != null, c < a = b
            append(c);
            c = meld(a, b);
            b = bRSib;
            break;
        case 10:
            // b = null, c!= null, c = a
            c = meld(a, c);
            break;
        case 11:
            // b != null, c != null, c = a < b
            c = meld(a, c);
            break;
        case 15:
            // b != null, c!= null, c = a = b
            append(c);
            c = meld(a, b);
            b = bRSib;
            break;
        default:
            cout << whichCase << " Can't Happen!\n";
            return;
    }

    combine(aRSib, b, c);
}

void BinomialQueue::removeTree(BNode *v, BinomialQueue &Q) {
    // this method delete node pointed by v and attach
    // v's first child to Q

    Q.q = v->f_child;

    if (q->r_sib == NULL) {
        q = NULL;
    } else if (v == q) {
        v->r_sib->l_sib = v->l_sib;
        q = v->r_sib;
    } else {
        v->l_sib->r_sib = v->r_sib;
        if (v->r_sib)
            v->r_sib->l_sib = v->l_sib;
    }

    delete v;
}

BNode * BinomialQueue::minTree() {
    // identify the min node from the first level linked list
    BNode *min = q;
    int minVal = q->key;
    BNode *runner = q->r_sib;

    while (runner != NULL) {
        if (runner->key < minVal) {
            minVal = runner->key;
            min = runner;
        }
        runner = runner->r_sib;
    }

    return min;
}

void BinomialQueue::insert(int v) {
    // create a new binomial queue with single node and combine
    BinomialQueue *newQueue = new BinomialQueue(v);
    merge(*newQueue);
}

int BinomialQueue::findMin() {
    if (isEmpty()) {
        cout << "Error. Can't findMin from empty queue.\n";
        return INT_MAX;
    }
    return (minTree())->key;
}

int BinomialQueue::deleteMin() {
    // this method find the smallest node, delete it
    // and merge its children queue back
    if (isEmpty()) {
        cout << "Error. Can't deleteMin from empty queue.\n";
        return INT_MAX;
    }

    BNode *minNode = minTree();
    int minVal = minNode->key;

    BinomialQueue remainQueue;
    removeTree(minNode, remainQueue);
    merge(remainQueue);

    return minVal;
}

bool BinomialQueue::isEmpty() {
    return (q == NULL);
}

void BinomialQueue::makeEmpty(BNode *&t) {
    if  (t != NULL) {
        makeEmpty(t->f_child);
        makeEmpty(t->r_sib);
        cout << "Deallocating " << t->key << endl;
        delete t;
        t = NULL;
    }
}

void BinomialQueue::makeEmpty() {
    makeEmpty(q);
}

int BinomialQueue::assignX(BNode *t) {
    // this method assign the x value
    // which is the distance from node to the beginning of line

    int spacing = 0; // spacing is the full width of a tree rooted at t

    if (t->f_child) {
        // the x of first child is the same as its parent
        t->f_child->x = t->x;
        t->f_child->level = t->level + 1;
        spacing = assignX(t->f_child) - t->x;
    }

    if (t->r_sib) {
        // assign t's right sibling
        t->r_sib->level = t->level;
        int s = (t->len > spacing) ? t->len : spacing;

        // if node is at first level, set spacing to 9
        // else set spacing to 1
        if (t->level == 0)
            t->r_sib->x = t->x + s + 9;
        else
            t->r_sib->x = t->x + s + 1;
        return assignX(t->r_sib);
    } else {
        return t->x + t->len;
    }
}

string makeSpace(int n) {
    stringstream result;
    string space = " ";

    for (int i = 0; i < n; i++)
        result << space;

    return result.str();
}

void BinomialQueue::levelOrder() {
    if (isEmpty()) {
        cout << "Empty Binomial Queue.\n";
        return;
    }
    cout << endl;

    // set the first level nodes's level and x fields 
    // to faciliate the assingX method
    BNode *runner = q;
    while (runner != NULL) {
        runner->level = 0;
        runner = runner->r_sib;
    }
    q->x = 0;
    assignX(q);


    TQueue queue;
    queue.push(q);
    int currentLevel = 0;
    string line;

    // add nodes at current level to line and
    // push their first child to the queue
    while (!queue.isEmpty()) {
        BNode *t = queue.top();

        if (t->level != currentLevel) {
            cout << line << endl;
            line = "";
            currentLevel = t->level;
        }

        while (t != NULL) {
            int spacing = t->x - line.length();
            line += (makeSpace(spacing) + t->content);
            if (t->f_child != NULL) {
                queue.push(t->f_child);
            }
            t = t->r_sib;
        }

        queue.pop();
    }

    cout << line << endl << endl;
}
