#ifndef LIST_H_
#define LIST_H_

#include "Node.h"
#include <iostream>
using namespace std;

class HashTable {
public:
    enum Mode { PROBE, DOUBLE };
    HashTable(int c = 7, int k = 10000, Mode m = PROBE);
    ~HashTable();
    bool isfull();
    bool contains(long k);
    void insert(long k);
    void remove(long k);
    void print();
    int  get_size() { return size; }
    Mode get_mode() { return mode; }
    void set_mode(Mode m) { mode = m; }
    float load_factor() { return float(size) / float(capacity); }
    int get_probing() { return probing; }

private:
    Node *table; // dynamic array of Node objects
    int capacity; // maximun capacity
    int K; // number of probing
    int size; // current size
    Mode mode; // choose quadratic probing or double hashing
    int R; // secondary hashing number
    int h2_remainder; // remember the secondary hashing number to speed up
    int probing; // keep track of the number of probing

    long hash(long);
    long h2_qp(long, int); // h2 hash function using quadratic probing
    long h2_dh(long, int); // h2 hash function using double hashing
    long adjusted_hash(long); // adjust hashed value if it is negative
    long get_hashed_value(long, int); // caculate hashed value according to h2
    int indexOf(long x); // calculate the index of x in the table, -1 if not exist
};

#endif
