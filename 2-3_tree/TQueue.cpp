#include "TQueue.h"

TQueue::TQueue() : s(0) {
    // Use the first node as sentinel node
    first = new TNode();
    first->key = -1;
    first->next = first;
}

TQueue::~TQueue() {
    TNode *runner = first;
    do {
        delete runner;
        runner = runner->next;
    } while (runner != first);
}

bool TQueue::isEmpty() {
    return (first == first->next);
}

void TQueue::push(TNode *x) {
    // circular linked list with the first node as the sentinel node.  
    // find the last node
    TNode *last = first;
    while (last->next != first)
        last = last->next;

    x->next = first;
    last->next = x;

    s++;
}

const TNode * TQueue::top() {
    if (isEmpty()) return NULL;
    return first->next;
}

void TQueue::pop() {
    if (isEmpty()) return;

    TNode *f = first->next;
    first->next = f->next;
    s--;
}
