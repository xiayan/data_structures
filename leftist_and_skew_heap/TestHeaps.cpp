#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "BinaryHeap.h"
#include "LeftistHeap.h"
#include "SkewHeap.h"
#include "AsciiTree.h"
using namespace std;

int main() {
	// Obtain data from text file
    // int testSize = 5;  // data.txt contains 11 numbers
    int deleteTime = 1;
	int v;
    int idx = 0;
    // int data[testSize];

	// Create LeftistHeap, SkewHeap and Binary Heap
	LeftistHeap lHeap;
    SkewHeap    sHeap;
    // BinaryHeap  bHeap(data, testSize); // build by bottom up
    BinaryHeap  bHeap2; // build by insert
	AsciiTree   tree;

	ifstream dataFile ("data.txt");
	if(dataFile.is_open()) {
		while(dataFile >> v) {
            lHeap.insert(v);
            sHeap.insert(v);
            bHeap2.insert(v);
            // data[idx++] = v;
        }
    }
	dataFile.close();

    // Build Leftist heap and Skew heap using inserting
    // for (int i = 0; i < testSize; i++) {
    //     lHeap.insert(data[i]);
    //     sHeap.insert(data[i]);
    //     bHeap2.insert(data[i]);
    // }
    
    // Leftist heap tests
    cout << "Original Leftist Heap\n\n";
    tree.buildTree(lHeap);
    tree.draw();
    lHeap.print();

	// Test findMin
	 cout << "FindMin: " << lHeap.findMin() << endl;
	// Test result of deleteMins
    for (int i = 0; i < deleteTime; i++) {
        cout << "DeleteMin: " << lHeap.deleteMin() << endl << endl;
        tree.buildTree(lHeap);
        tree.draw();
        lHeap.print();
    }
	cout << endl << endl << "---" << endl << endl;
	
    // Skew heap tests
    cout << "Original Skew Heap\n\n";
    tree.buildTree(sHeap);
    tree.draw();
    sHeap.print();

    // Test findMin
    cout << "FindMin: " << sHeap.findMin() << endl;
    // Test deleteMin
    for (int i = 0; i < deleteTime; i++) {
        cout << "DeleteMin: " << sHeap.deleteMin() << endl << endl;
        tree.buildTree(sHeap);
        tree.draw();
        sHeap.print();
    }

	cout << endl << endl << "---" << endl << endl;

    // Binary heap tests
    // cout << "Binary Heap built from bottom-up heapify\n\n";
    // tree.buildTree(bHeap);
    // tree.draw();
    // bHeap.print();

    // // Test findMin
    // cout << "FindMin: " << bHeap.findMin() << endl;
    // // Test deleteMin
    // for (int i = 0; i < deleteTime; i++) {
    //     cout << "DeleteMin: " << bHeap.deleteMin() << endl << endl;
    //     tree.buildTree(bHeap);
    //     tree.draw();
    //     bHeap.print();
    // }

    // cout << endl << endl << "---" << endl << endl;


    cout << "Binary Heap built from insertion\n\n";
    tree.buildTree(bHeap2);
    tree.draw();
    bHeap2.print();

    // Test findMin
    cout << "FindMin: " << bHeap2.findMin() << endl;
    for (int i = 0; i < deleteTime; i++) {
        cout << "DeleteMin: " << bHeap2.deleteMin() << endl << endl;
        tree.buildTree(bHeap2);
        tree.draw();
        bHeap2.print();
    }

    cout << endl << endl << "---" << endl << endl;

	return 0;
}
