#include <iostream>
#include "HashTable.h"

HashTable::HashTable(int c) : capacity(c), size(0) {
    // create a dynamic array of Node pointers
    table = new Node *[capacity];
    for (int i = 0; i < capacity; i++)
        // initiate the sentinel pointers
        table[i] = new Node();
}

HashTable::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        Node *runner = table[i];
        while (runner != NULL) {
            Node *next = runner->next;
            delete runner;
            runner = next;
        }
    }
    
    delete[] table;
}

int HashTable::hash(int k) {
    int hashed = k % capacity;
    return (hashed < 0) ? (hashed + capacity) : hashed;
}

bool HashTable::isEmpty() {
    return (size == 0);
}

bool HashTable::contains(int k) {
    int idx = hash(k);
    Node *runner = table[idx]->next;

    while (runner != NULL) {
        if (runner->key == k) return true;
        runner = runner->next;
    }
    
    return false;
}

void HashTable::insert(int k) {
    if (contains(k)) {
        cout << k << " is already in the table.  Duplicates are not allowed!\n";
        return;
    }
    
    int idx = hash(k);
    Node *head = table[idx];
    Node *newNode = new Node(k);
    // insert in front
    newNode->next = head->next;
    head->next = newNode;
    size++;
}

void HashTable::remove(int k) {
    int idx = hash(k);
    Node *pre = table[idx];
    
    while (pre->next != NULL) {
        if (pre->next->key == k) {
            Node *to_delete = pre->next;
            // disconnect the to_delete node
            pre->next = pre->next->next;
            delete to_delete;
            size--;
            // directly break out because duplication is not allowed
            break;
        }
        pre = pre->next;
    }
}

void HashTable::print() {
    for (int i = 0; i < capacity; i++) {
        cout << i << ":";
        Node *runner = table[i]->next;
        while (runner != NULL) {
            cout << " " << runner->key;
            runner = runner->next;
        }
        cout << endl;
    }
    cout << "Total number of Nodes: " << size << endl;
}
