#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "HashTable.h"

using namespace std;

int main(int argc, const char *argv[]) {
    int i;
    ifstream input("data.txt");

    if (!input.good()) {
        cout << "Can't open file \"data.txt\"\n";
        exit(1);
    }

    input >> i;
    HashTable hashTable(i);

    while (input >> i)
        hashTable.insert(i);
    input.close();

    cout << "\n------- Test isEmpty() -------\n";
    const char *isempty = (hashTable.isEmpty()) ? "empty.\n" : "not empty.\n";
    cout << "The Hash Table is " << isempty;

    cout << "\n------- Original Hash Table -------\n";
    hashTable.print();

    // remove 17 and 14
    cout << "\n------- After Deletion of 17 and 14 -------\n";
    hashTable.remove(17);
    hashTable.remove(14);
    hashTable.print();

    // test hashing negative integers
    cout << "\n------- Insert -17, -20 and -21 -------\n";
    hashTable.insert(-17);
    hashTable.insert(-20);
    hashTable.insert(-21);
    hashTable.print();

    // test deleting negative integers
    cout << "\n------- Deleting -17, -20 and -21 -------\n";
    hashTable.remove(-17);
    hashTable.remove(-20);
    hashTable.remove(-21);
    hashTable.print();

    // remove 15 to test removing from the beginning of the list
    cout << "\n------- Remove 8, 15 -------\n";
    hashTable.remove(8);
    hashTable.remove(15);
    hashTable.print();

    // remove 12 to test removing from the end of the list
    cout << "\n------- Remove 12 -------\n";
    hashTable.remove(12);
    hashTable.print();

    // remove 4 twice to test deletion from empty list
    cout << "\n------- Delete 4 Twice -------\n";
    hashTable.remove(4);
    hashTable.remove(4);
    hashTable.print();

    // test items that does not belong to the hash table for each entry
    cout << "\n------- Delete 10, 11, 17, 13, 14 -------\n";
    hashTable.remove(10);
    hashTable.remove(11);
    hashTable.remove(17);
    hashTable.remove(13);
    hashTable.remove(14);
    hashTable.print();

    cout << "\n------- Remove the HashTable to empty -------\n";
    ifstream input2("data.txt");
    while (input2 >> i)
        hashTable.remove(i);
    hashTable.print();
    input2.close();

    cout << "\n------- Test isEmpty() -------\n";
    const char *isempty2 = (hashTable.isEmpty()) ? "empty.\n" : "not empty.\n";
    cout << "The Hash Table is " << isempty2;

    return 0;
}
