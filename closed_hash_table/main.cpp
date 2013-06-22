#include "HashTable.h"
#include <fstream>
#include <stdlib.h>

using namespace std;

void print_contain_message(int, HashTable &);

int main(int argc, const char *argv[]) {
    int i;
    ifstream input("data.txt");

    if (!input.good()) {
        cout << "Can't open file \"data.txt\"\n";
        exit(1);
    }

    input >> i; // size of the hash table

    // create two hash tables, one uses quadratic probing, one uses double hash
    HashTable hashTable1(i, i * i, HashTable::PROBE);
    HashTable hashTable2(i, i * i, HashTable::DOUBLE);
    
    // insert numbers to both table
    while (input >> i) {
        hashTable1.insert(i);
        hashTable2.insert(i);
    }
    input.close();
    
    cout << "------- Test for Quadratic Probing -------\n";
    hashTable1.print();
    cout << endl;

    cout << "Remove 26, Insert 36 and 42.\n";
    hashTable1.remove(26);
    hashTable1.insert(36);
    hashTable1.insert(42);
    hashTable1.print();

    // Test method "contain" for quadratic probing
    cout << endl;
    print_contain_message(26, hashTable1);
    print_contain_message(36, hashTable1);
    cout << endl;
    
    cout << "Remove 64, Insert 36.\n";
    hashTable1.remove(64);
    hashTable1.insert(36);
    cout << endl;
    cout << "Remove 36, Insert 36 again.\n";
    hashTable1.remove(36);
    hashTable1.insert(36);
    hashTable1.print();
    cout << endl;
    cout << "Insert 43.\n";
    hashTable1.insert(43);
    hashTable1.print();
    cout << endl;

    cout << "------- Test for Double Hashing -------\n";
    hashTable2.print();
    cout << endl;

    cout << "Removed 26, Insert 36 and 42.\n";
    hashTable2.remove(26);
    hashTable2.insert(36);
    hashTable2.insert(42);
    hashTable2.print();

    // Test method "contain" double hashing
    cout << endl;
    print_contain_message(26, hashTable2);
    print_contain_message(36, hashTable2);
    cout << endl;
    
    cout << "Remove 64, Insert 36.\n";
    hashTable2.remove(64);
    hashTable2.insert(36);
    cout << endl;
    cout << "Remove 36, Insert 36 again.\n";
    hashTable2.remove(36);
    hashTable2.insert(36);
    hashTable2.print();
    cout << endl;
    cout << "Insert 43.\n";
    hashTable2.insert(43);
    hashTable2.print();
    cout << endl;
    

    return 0;
}

// print whether an item is contains in the table
void print_contain_message(int x, HashTable &h) {
    string contained = (h.contains(x)) ? "" : " not";
    cout << x << " is" << contained << " in the table.\n";
}
