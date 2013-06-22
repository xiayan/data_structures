Implementation of Closed Hashing with Open Addressing

Node.h: definition of Node strucutre.  Each node struct contains an integer key and a pointer that points to the next Node in the linked list.  It has three status: EMPTY, DELETED, and ACTIVE. 

HashTable.h: Declaration of separate-chaining HashTable ADT.  The HashTable class has a dynamic array of Nodes, a capacity and the current size.  It has two modes: quadratic probing and double hashing.  The hash function trivially computes the modulo of key to the capacity.  It then computes the final hashed value using the h2 function chosen by users.

HashTable.cpp: Implementation of closed hashing, open addressing HashTable ADT. More more comments on the methods please check the "HashTable.cpp" file directly.

main.cpp: Simple test of the HashTable ADT.  The program creates two hash tables, one using quadratic probing, the other using double hashing.  It then reads some numbers from a text file named "data.txt", and add the numbers into HashTables one by one.  It will then test remove, insert and contains methods.  The HashTable is printed after each of these operations.
