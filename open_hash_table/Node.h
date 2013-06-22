#ifndef NODE_H_
#define NODE_H_

#include <cstddef>

struct Node {
    int key;
	Node *next;
    explicit Node(int k = ~(1 << 31), Node *n = NULL): key(k), next(n) { }
};

#endif
