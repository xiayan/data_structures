#ifndef NODE_H_
#define NODE_H_

struct Node {
    int value;
	Node *next;
    Node(int v = 0, Node *n = 0): value(v), next(n) { }

};

#endif
