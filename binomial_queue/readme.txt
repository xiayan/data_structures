Implementation of BinomialQueue

BinomialQueue.h and BinomialQueue.cpp: implementation of BinomialQueue. It uses first-child and right sibling implementation of each binomial heap and uses a doubly linked list to chain together a set of binomial heaps.

BNode.h: Simple class for heap node in binomial heaps. It has data fields that points to left sibling, right sibling and first child.  It also has additional data fields to facilitate the level order traversal.

TQueue.h and TQueue.cpp: implementation of FIFO queue of BNodes.  Used for the level order traversal.

data.txt: contains 11 numbers to test the BinomialQueue implementation

main.cpp: the testing program. It reads in numbers from "data.txt" and insert it into the BinomialQueue.  Then it performs deleteMin and insert operations.