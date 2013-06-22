#include "TQueue.h"

TQueue::TQueue() : s(0) {
    // Use the first node as sentinel node
    first = new BNode(-1);
    first->next = first;
}

TQueue::~TQueue() {
    BNode *runner = first;
    do {
        delete runner;
        runner = runner->next;
    } while (runner != first);
}

bool TQueue::isEmpty() {
    return (first == first->next);
}

void TQueue::push(BNode *x) {
    // circular linked list with the first node as the sentinel node.  
    // find the last node
    BNode *last = first;
    while (last->next != first)
        last = last->next;

    x->next = first;
    last->next = x;

    s++;
}

BNode * TQueue::top() {
    if (isEmpty()) return NULL;
    return first->next;
}

void TQueue::pop() {
    if (isEmpty()) return;

    BNode *f = first->next;
    first->next = f->next;
    s--;
}
