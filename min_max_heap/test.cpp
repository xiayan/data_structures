#include "MinMaxHeap.h"
#include <iostream>
#include <climits>
using namespace std;

void printProgBar(int percent, int c, int total);

int main() {
    MinMaxHeap heap(NULL, 0);
    srand(time(NULL));

    int choice;
    int reps = 200000;
    
    int counter = 0;
    int insertCounts = 0, deleteMinCounts = 0, deleteMaxCounts = 0;
    int maxSize = -1;

    while (counter != reps) {
        // choose insert with probabilty 50%.
        // deleteMin and deleteMax 25% each
        // this will result in a bigger heap
        choice = rand() % 4 + 1;
        switch (choice) {
            case 1:
            case 2:
                if (!heap.isFull()) {
                    insertCounts++;
                    counter++;
                    heap.insert(rand() % INT_MAX + 1);
                }
                break;
            case 3:
                if (!heap.isEmpty()) {
                    deleteMinCounts++;
                    counter++;
                    heap.deleteMin();
                }
                break;
            case 4:
                if (!heap.isEmpty()) {
                    deleteMaxCounts++;
                    counter++;
                    heap.deleteMax();
                }
                break;
            default:
                cout << "Wrong choice number.\n";
                break;
        }
        
        printProgBar(float(counter) / float(reps) * 100, counter, reps);

        int currentSize = heap.getSize();
        if (currentSize > maxSize)
            maxSize = currentSize;
    }
    
    cout << endl;
    cout << "No error is found after " << reps << " random operations.\n";
    cout << insertCounts << " inserts\n";
    cout << deleteMinCounts << " deleteMin\n";
    cout << deleteMaxCounts << " deleteMax\n";
    cout << "Max size of the heap was " << maxSize << endl;
    
    return 0;
}

void printProgBar(int percent, int c, int total) {
    string bar;

    for (int i = 0; i < 50; i++) {
        if (i < (percent / 2)) {
            bar.replace(i, 1, "=");
        } else if( i == (percent / 2)) {
            bar.replace(i, 1, ">");
        } else {
            bar.replace(i, 1, " ");
        }
    }

    cout << "\r" "[" << bar << "] ";
    cout.width( 3 );
    //cout << percent << "%     " << std::flush;
    cout << c << "/" << total << "  " << std::flush;
}

