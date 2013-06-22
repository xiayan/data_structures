#ifndef NODE_H_
#define NODE_H_

#include <cstddef>

struct Node {
    enum Status { ACTIVE, EMPTY, DELETED };
    int key;
	Node *next;
    Status st;
    Node(int k = ~(1 << 31), Node *n = NULL, Status s = EMPTY): key(k), next(n), st(s) { }
};

#endif
