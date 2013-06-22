#ifndef LIST_H_
#define LIST_H_

#include "Node.h"
using namespace std;

class HashTable {
	
	private:
		Node **table; // dynamic array of Node pointers
        int capacity; // maximun capacity
        int size; // current size
        int hash(int k);

	public:
		HashTable(int c = 7);
		~HashTable();
        bool isEmpty();
        bool contains(int k);
		void insert(int k);
        void remove(int k);
		void print();
        int get_size() { return size; }
};

#endif
