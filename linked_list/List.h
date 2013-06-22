#ifndef LIST_H_
#define LIST_H_

#include "Node.h"
#include <iostream>
using namespace std;

class List {

    private:
        Node* first;
        int s; // size of the list
        void insert(int x, Node *current);
        int remove(int idx, Node *pre);
        void erase(int x, Node *pre);
        void reverse(Node *current, Node *rest, bool start);
        void concat2(Node *current, Node *first);

    public:
        List();
        ~List();
        void insert(int x);
        bool isEmpty();
        int remove(int d); // delete node at index d(1-indexing)
        void erase(int x); // delete all occurance of x
        void reverse();
        void print();
        void concat(List &l2); // if allow to use remove(int d)
        void concat2(List &l2); // if not allow to use remove(int d)
};

#endif
