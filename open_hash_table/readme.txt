Node.h: definition of Node strucutre.  Each node struct contains an integer key and a pointer that points to the next Node in the linked list.

HashTable.h: Declaration of separate-chaining HashTable ADT.  The HashTable class has a dynamic array of Node pointers, a capacity and the current size.  The hash function trivially computes the modulo of key to the capacity.

HashTable.cpp: Implementation of separate-chaining HashTable ADT. More more comments on the methods please check the "HashTable.cpp" file directly.

main.cpp: Simple test of the HashTable ADT.  The program first read the some numbers from a text file named "data.txt", and add the numbers into HashTable one by one.  It will then test deletion operation.  The HashTable is printed after each of these operations.
