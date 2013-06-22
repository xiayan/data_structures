Node.h: definition of Node strucutre.  Each node struct contains an integer value and a pointer that points to the next Node in the linked list.

List.h: Declaration of Linked List ADT.  The linked list uses the first node as the sentinel node.  It also keeps a data member to keep track of the size of the current list.

List.cpp: Implementation of Linked List ADT. More more comments on the methods please check the "List.cpp" file directly.

main.cpp: Simple test of the Link list ADT.  The program first read the first 11 fibonacci numbers from a text file named "data.txt", and add the numbers into the linked list one by one.  It will then delete the first 3 elements from the list and reverse it.  The list is printed after each of these operations.
