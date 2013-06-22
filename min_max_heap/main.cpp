#include <iostream>
#include <fstream>
#include <cstdlib>
#include "MinMaxHeap.h"
#include "AsciiTree.h"

using namespace std;

void generateResults(MinMaxHeap &h, AsciiTree &t);

int main() {
	
	// Get data size
    AsciiTree tree;

	ifstream dataFile ("data.txt");
	MinMaxHeap heap(dataFile);
	dataFile.close();
    
    cout << "Initial Tree\n";
    generateResults(heap, tree);

    cout << "DeleteMin\n";
    heap.deleteMin();
    generateResults(heap, tree);

    cout << "DeleteMax\n";
    heap.deleteMax();
    generateResults(heap, tree);

    cout << "Insert 1, 20, 15, 30, 12, 13, 14\n";
    heap.insert(1);
    heap.insert(20);
    heap.insert(15);
    heap.insert(30);
    heap.insert(12);
    heap.insert(13);
    heap.insert(14);
    generateResults(heap, tree);

    cout << "DeleteMin\n";
    heap.deleteMin();
    generateResults(heap, tree);

    int c = -1;
    while (c != 0) {
        cout << "Interactive Viewer For MinMax Heap\n";
        cout << "Press 1: Test insert()\n";
        cout << "Press 2: Test deleteMin()\n";
        cout << "Press 3: Test deleteMax()\n";
        cout << "Press 4: Test findMin()\n";
        cout << "Press 5: Test findMax()\n";
        cout << "Press 0: Quit\n";
        cout << "Your choice: ";
        cin >> c;

        switch(c) {
            case 1:
                int x;
                cout << "Enter the number to insert: ";
                cin >> x;
                cout << endl << endl;
                cout << "Insert " << x << endl;
                heap.insert(x);
                generateResults(heap, tree);
                break;
            case 2:
                cout << "\n\nDeleteMin\n";
                heap.deleteMin();
                generateResults(heap, tree);
                break;
            case 3:
                cout << "\n\nDeleteMax\n";
                heap.deleteMax();
                generateResults(heap, tree);
                break;

            case 4:
                cout << "\n\nFindMin\n";
                cout << "Min Value: " << heap.findMin() << endl << endl;
                break;
            case 5:
                cout << "\n\nFindMax\n";
                cout << "Max Value: " << heap.findMax() << endl << endl;
                break;
            default:
                cout << "Bye!\n";
                c = 0;
                break;
        }
    }

	return 0;
}

void generateResults(MinMaxHeap &h, AsciiTree &t) {
    cout << "-----------------------------------------------------\n\n";
    t.buildTree(h);
    t.draw();
    h.levelOrder();

    #ifdef DEBUG
    bool valid = h.check();
    if (!valid)
        cout << "INVALID!\n";
    else
        cout << "VALID!\n";
    #endif

    cout << "Min: " << h.findMin() << endl;
    cout << "Max: " << h.findMax() << endl;
    cout << "-----------------------------------------------------\n\n\n";
}
