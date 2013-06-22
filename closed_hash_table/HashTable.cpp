#include "HashTable.h"

HashTable::HashTable(int c, int k, Mode m) : capacity(c), K(k), size(0), mode(m), R(5), probing(0) {
    // create a dynamic array of Nodes
    // Each item in the array is Node object, not pointer to Node
    table = new Node[capacity];
}

HashTable::~HashTable() {
    delete[] table;
}

long HashTable::adjusted_hash(long h) {
    // adjust the hashed value if it is negative
    return (h < 0) ? (h + capacity) : h;
}

long HashTable::hash(long k) {
    // h1 hash function using modulo
    probing++;
    return k % capacity;
}

long HashTable::h2_qp(long x, int i) {
    // quaratic probing
    return adjusted_hash((hash(x) + i * i) % capacity);
}

long HashTable::h2_dh(long x, int i) {
    return adjusted_hash((hash(x) + i * h2_remainder) % capacity);
}

long HashTable::get_hashed_value(long x, int i) {
    // calculate hashed value according to choice of mode
    if (mode == PROBE) {
        return h2_qp(x, i);
    } else {
        if (i == 0)
            h2_remainder = R - x % R;
        return h2_dh(x, i);
    }
}

bool HashTable::isfull() {
    return (size == capacity);
}

int HashTable::indexOf(long x) {
    // return index of x, if not exist, return -1
    // probing K times
    for (int i = 0; i < K; i++) {
        int idx = get_hashed_value(x, i);
        Node &current = table[idx];
        if (current.key == x) {
            if (current.st == Node::ACTIVE) return idx;
            else                            continue;
        }
        else if (current.st == Node::EMPTY) return -1;
        else ;
    }

    return -1;
}

bool HashTable::contains(long x) {
    int idx = indexOf(x);
    return idx >= 0;
}

void HashTable::insert(long x) {
    // if the table is full, don't bother to calcualte the hashed value
    if (isfull()) {
        cout << "Hash Table is full.\n";
        return;
    }
    
    // if already contains the element, return
    if (contains(x)) {
        //cout << x << " is already in the table.\n";
        return;
    }
    
    // Try to probe K times
    for (int i = 0; i < K; i++) {
        int idx = get_hashed_value(x, i);
        Node &current = table[idx];
        // if status is deleted or empty, add the element 
        if (current.st != Node::ACTIVE) {
            current.key = x;
            current.st = Node::ACTIVE;
            size++;
            return;
        }
        // if the key is active, continue
        else ;
    }
    
    // After capacity ^ 2 probes, can't find a empty spot. Recommend rehashing
    //cout << "Cannot insert " << x << " after " << K << " tries.\n";
    //cout << "The load factor is " << load_factor() << " now.\n";
    //cout << "Rehashing is recommended.\n\n";
}

void HashTable::remove(long x) {
    // Do nothing if the table is empty
    if (size == 0) {
        cout << "Can't delete. Hash Table is empty.\n";
        return;
    }
    
    // find index of x
    int idx = indexOf(x);
    // if x not in the table, do nothing.
    if (idx < 0) { 
        cout << "Hash Table does not have " << x << endl;
        return;
    }
    
    // delete node by setting its state to DELETED
    Node &current = table[idx];
    current.st = Node::DELETED;
    size--;
    return;
}

void HashTable::print() {
    // Only print items with active status
    for (int i = 0; i < capacity; i++) {
        cout << i << ": ";
        if (table[i].st == Node::ACTIVE)
            cout << table[i].key;
        cout << endl;
    }
    cout << "Total number of Nodes: " << size << endl;
}
