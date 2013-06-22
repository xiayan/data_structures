#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "List.h"
using namespace std;

int main(int argc, const char *argv[]) {
	List list1;
	
	// Build list
	int i;
	ifstream input ("data.txt");
    if (!input.good()) {
        cout << "Can't open file data.txt\n";
        exit(1);
    }

    while (input >> i)
        list1.insert(i);
    input.close();
	
	// Test list
    cout << "---Basic Tests---\n";
    cout << "List1: ";
    list1.print();

    // Test erase
    list1.erase(0);
    cout << "List1 after erasing 0: ";
    list1.print();
    list1.erase(1);
    cout << "List1 after erasing 1: ";
    list1.print();

    // Test reverse
	list1.reverse();
    cout << "List1 after recursive reverse: ";
    list1.print();

    ifstream input2("data.txt");
    List list2;
    while (input2 >> i)
        list2.insert(i);
    input2.close();
    
    // Test remove
    for (int j = 0; j < 3; j++)
        list2.remove(1);
    
    // Test concat
    cout << "List2: ";
    list2.print();
    list1.concat2(list2);
    cout << "List1 after concatenation with List2: ";
    //list.concat(list2);
    list1.print();
    cout << endl;

    cout << "---Erase Test on List1---" << endl;
    list1.erase(55);
    cout << "Erase 55: ";
    list1.print();

    cout << "Testing erase from front and end\n";
    list1.insert(34);
    cout << "Insert 34: ";
    list1.print();

    list1.erase(34);
    cout << "Erase 34: ";
    list1.print();

    list1.erase(2);
    cout << "Erase 2: ";
    list1.print();

    list1.erase(5);
    cout << "Erase 5: ";
    list1.print();

    list1.erase(13);
    cout << "Erase 13: ";
    list1.print();
    
    list1.erase(100);
    cout << "Erase 100(not in list): ";
    list1.print();
    cout << endl;

    // Corner cases:
    cout << "---Test Corner Cases---\n";
    List list3;
    cout << "Empty List\n";
    cout << "List3: ";
    list3.print();
    cout << "Reverse empty list\n";
    cout << "List3: ";
    list3.reverse();
    list3.print();
    list3.erase(2);
    cout << "Erase 2 from empty list: ";
    list3.print();
    list1.concat2(list3);
    cout << "List1 concats empty list: ";
    list1.print();
    cout << endl;

    list3.insert(6);
    cout << "One-element list: ";
    list3.print();
    cout << "Reverse one-element list: ";
    list3.reverse();
    list3.print();
    cout << "List1 concats one-element list: ";
    list1.concat2(list3);
    list1.print();
    cout << "Delete from 1-element list\n";
    list3.erase(6);
    cout << "List3: ";
    list3.print();
    cout << endl;
    
    list3.insert(6);
    list3.insert(35);
    cout << "Two-element list: ";
    list3.print();
    cout << "Reverse Two-element list: ";
    list3.reverse();
    list3.print();
    cout << "List1 concat two-element list: ";
    list1.concat2(list3);
    list1.print();
    cout << "Delete from two-element list\n";
    list3.erase(42);
    cout << "Erase 42(not in list): ";
    list3.print();
    list3.erase(6);
    cout << "Erase 6: ";
    list3.print();
    list3.erase(35);
    cout << "Erase 35: ";
    list3.print();
    

	return 0;
}
