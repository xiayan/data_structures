#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "BinomialQueue.h"
using namespace std;

int main() {
	// Create BinomialQueues
	BinomialQueue Q1;
    BinomialQueue Q2;
    
    int total = 10;
	// Build queues using insert
	int v;
	ifstream dataFile ("data.txt");
	if(dataFile.is_open()) {
		while(dataFile >> v) {
    		Q1.insert(v);
            Q2.insert(v);
        }
    }

	dataFile.close();
    cout << "Original Q1 queue:\n";
    Q1.levelOrder();
    
    cout << "Q1 deleteMin\n";
    Q1.deleteMin();
    Q1.levelOrder();
    
    cout << "Q1 insert 11 and 20:\n";
    Q1.insert(11);
    Q1.insert(20);
    Q1.levelOrder();

    cout << "Q1 deleteMin\n";
    Q1.deleteMin();
    Q1.levelOrder();
    
	// random tests of insert and deleteMin
    cout << total << " times of random insert and deleteMin on Q1\n";
    srand(time(NULL));
    for (int i = 0; i < total; i++) {
        float r = (float)rand() / (float)RAND_MAX;
        if (r < 0.5) {
            cout << "Q1 deleteMin:\n";
            Q1.deleteMin();
        } else {
            int r = rand() % (total * 3) + 1;
            cout << "Q1 insert random number: " << r << endl;
            Q1.insert(r);
        }
        Q1.levelOrder();
    }

    cout << "Original Q2 queue\n";
    Q2.levelOrder();
    
    cout << "Combining Q2 to Q1\n"; 
    Q1.merge(Q2);
    cout << "Q1 becomes\n";
    Q1.levelOrder();
    cout << "Q2 becomes\n";
    Q2.levelOrder();
    cout << endl;

	return 0;
}
